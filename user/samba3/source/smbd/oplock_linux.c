/* 
   Unix SMB/CIFS implementation.
   kernel oplock processing for Linux
   Copyright (C) Andrew Tridgell 2000
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define DBGC_CLASS DBGC_LOCKING
#include "includes.h"

#if HAVE_KERNEL_OPLOCKS_LINUX

static SIG_ATOMIC_T signals_received;
#define FD_PENDING_SIZE 100
static SIG_ATOMIC_T fd_pending_array[FD_PENDING_SIZE];

#ifndef F_SETLEASE
#define F_SETLEASE	1024
#endif

#ifndef F_GETLEASE
#define F_GETLEASE	1025
#endif

#ifndef CAP_LEASE
#define CAP_LEASE 28
#endif

#ifndef RT_SIGNAL_LEASE
#define RT_SIGNAL_LEASE (SIGRTMIN+1)
#endif

#ifndef F_SETSIG
#define F_SETSIG 10
#endif

/****************************************************************************
 Handle a LEASE signal, incrementing the signals_received and blocking the signal.
****************************************************************************/

static void signal_handler(int sig, siginfo_t *info, void *unused)
{
	if (signals_received < FD_PENDING_SIZE - 1) {
		fd_pending_array[signals_received] = (SIG_ATOMIC_T)info->si_fd;
		signals_received++;
	} /* Else signal is lost. */
	sys_select_signal(RT_SIGNAL_LEASE);
}

/*
 * public function to get linux lease capability. Needed by some VFS modules (eg. gpfs.c)
 */
void linux_set_lease_capability(void)
{
	set_effective_capability(LEASE_CAPABILITY);
}

/* 
 * Call to set the kernel lease signal handler
 */
int linux_set_lease_sighandler(int fd)
{
        if (fcntl(fd, F_SETSIG, RT_SIGNAL_LEASE) == -1) {
                DEBUG(3,("Failed to set signal handler for kernel lease\n"));
                return -1;
        }

	return 0;
}

/****************************************************************************
 Call SETLEASE. If we get EACCES then we try setting up the right capability and
 try again.
 Use the SMB_VFS_LINUX_SETLEASE instead of this call directly.
****************************************************************************/

int linux_setlease(int fd, int leasetype)
{
	int ret;

	ret = fcntl(fd, F_SETLEASE, leasetype);
	if (ret == -1 && errno == EACCES) {
		set_effective_capability(LEASE_CAPABILITY);
		ret = fcntl(fd, F_SETLEASE, leasetype);
	}

	return ret;
}

/****************************************************************************
 * Deal with the Linux kernel <--> smbd
 * oplock break protocol.
****************************************************************************/

static files_struct *linux_oplock_receive_message(fd_set *fds)
{
	int fd;
	files_struct *fsp;

	BlockSignals(True, RT_SIGNAL_LEASE);
	fd = fd_pending_array[0];
	fsp = file_find_fd(fd);
	fd_pending_array[0] = (SIG_ATOMIC_T)-1;
	if (signals_received > 1)
                memmove(CONST_DISCARD(void *, &fd_pending_array[0]),
                        CONST_DISCARD(void *, &fd_pending_array[1]),
			sizeof(SIG_ATOMIC_T)*(signals_received-1));
	signals_received--;
	/* now we can receive more signals */
	BlockSignals(False, RT_SIGNAL_LEASE);

	return fsp;
}

/****************************************************************************
 Attempt to set an kernel oplock on a file.
****************************************************************************/

static bool linux_set_kernel_oplock(files_struct *fsp, int oplock_type)
{
	if ( SMB_VFS_LINUX_SETLEASE(fsp, F_WRLCK) == -1) {
		DEBUG(3,("linux_set_kernel_oplock: Refused oplock on file %s, "
			 "fd = %d, file_id = %s. (%s)\n",
			 fsp->fsp_name, fsp->fh->fd, 
			 file_id_string_tos(&fsp->file_id),
			 strerror(errno)));
		return False;
	}
	
	DEBUG(3,("linux_set_kernel_oplock: got kernel oplock on file %s, "
		 "file_id = %s gen_id = %lu\n",
		 fsp->fsp_name, file_id_string_tos(&fsp->file_id),
		 fsp->fh->gen_id));

	return True;
}

/****************************************************************************
 Release a kernel oplock on a file.
****************************************************************************/

static void linux_release_kernel_oplock(files_struct *fsp)
{
	if (DEBUGLVL(10)) {
		/*
		 * Check and print out the current kernel
		 * oplock state of this file.
		 */
		int state = fcntl(fsp->fh->fd, F_GETLEASE, 0);
		dbgtext("linux_release_kernel_oplock: file %s, file_id = %s "
			"gen_id = %lu has kernel oplock state "
			"of %x.\n", fsp->fsp_name, file_id_string_tos(&fsp->file_id),
			fsp->fh->gen_id, state );
	}

	/*
	 * Remove the kernel oplock on this file.
	 */
	if ( SMB_VFS_LINUX_SETLEASE(fsp, F_UNLCK) == -1) {
		if (DEBUGLVL(0)) {
			dbgtext("linux_release_kernel_oplock: Error when "
				"removing kernel oplock on file " );
			dbgtext("%s, file_id = %s, gen_id = %lu. "
				"Error was %s\n", fsp->fsp_name,
				file_id_string_tos(&fsp->file_id),
				fsp->fh->gen_id, strerror(errno) );
		}
	}
}

/****************************************************************************
 See if a oplock message is waiting.
****************************************************************************/

static bool linux_oplock_msg_waiting(fd_set *fds)
{
	return signals_received != 0;
}

/****************************************************************************
 See if the kernel supports oplocks.
****************************************************************************/

static bool linux_oplocks_available(void)
{
	int fd, ret;
	fd = open("/dev/null", O_RDONLY);
	if (fd == -1)
		return False; /* uggh! */
	ret = fcntl(fd, F_GETLEASE, 0);
	close(fd);
	return ret == F_UNLCK;
}

/****************************************************************************
 Setup kernel oplocks.
****************************************************************************/

struct kernel_oplocks *linux_init_kernel_oplocks(void) 
{
	static struct kernel_oplocks koplocks;
        struct sigaction act;

	if (!linux_oplocks_available()) {
		DEBUG(3,("Linux kernel oplocks not available\n"));
		return NULL;
	}

	ZERO_STRUCT(act);

	act.sa_handler = NULL;
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset( &act.sa_mask );
	if (sigaction(RT_SIGNAL_LEASE, &act, NULL) != 0) {
		DEBUG(0,("Failed to setup RT_SIGNAL_LEASE handler\n"));
		return NULL;
	}

	koplocks.receive_message = linux_oplock_receive_message;
	koplocks.set_oplock = linux_set_kernel_oplock;
	koplocks.release_oplock = linux_release_kernel_oplock;
	koplocks.msg_waiting = linux_oplock_msg_waiting;
	koplocks.notification_fd = -1;

	/* the signal can start off blocked due to a bug in bash */
	BlockSignals(False, RT_SIGNAL_LEASE);

	DEBUG(3,("Linux kernel oplocks enabled\n"));

	return &koplocks;
}
#else
 void oplock_linux_dummy(void);

 void oplock_linux_dummy(void) {}
#endif /* HAVE_KERNEL_OPLOCKS_LINUX */
