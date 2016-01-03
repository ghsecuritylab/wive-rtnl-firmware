#! /bin/sh
# $Id: genconfig.sh,v 1.85 2015/12/12 08:18:19 nanard Exp $
# miniupnp daemon
# http://miniupnp.free.fr or http://miniupnp.tuxfamily.org/
# (c) 2006-2015 Thomas Bernard
# This software is subject to the conditions detailed in the
# LICENCE file provided within the distribution

# default to UPnP Device Architecture (UDA) v2.0
UPNP_VERSION_MAJOR=1 # orig 2 workaround for Windown 10
UPNP_VERSION_MINOR=1 # orig 0 workaround for Windown 10

for argv; do
case "$argv" in
	--ipv6) IPV6=1 ;;
	--igd2) IGD2=1 ;;
	--strict) STRICT=1 ;;
	--leasefile) LEASEFILE=1 ;;
	--vendorcfg) VENDORCFG=1 ;;
	--pcp-peer) PCP_PEER=1 ;;
	--portinuse) PORTINUSE=1 ;;
	--uda-version=*)
		UPNP_VERSION=$(echo $argv | cut -d= -f2)
		UPNP_VERSION_MAJOR=$(echo $UPNP_VERSION | cut -s -d. -f1)
		UPNP_VERSION_MINOR=$(echo $UPNP_VERSION | cut -s -d. -f2)
		echo "Setting UPnP version major=$UPNP_VERSION_MAJOR minor=$UPNP_VERSION_MINOR"
		if [ -z "$UPNP_VERSION_MAJOR" ] || [ -z "$UPNP_VERSION_MINOR" ] ; then
			echo "UPnP Version invalid in option $argv"
			exit 1
		fi ;;
	--help|-h)
		echo "Usage : $0 [options]"
		echo " --ipv6      enable IPv6"
		echo " --igd2      build an IGDv2 instead of an IGDv1"
		echo " --strict    be more strict regarding compliance with UPnP specifications"
		echo " --leasefile enable lease file"
		echo " --vendorcfg enable configuration of manufacturer info"
		echo " --pcp-peer  enable PCP PEER operation"
		echo " --portinuse enable port in use check"
		echo " --uda-version=x.x  set advertised UPnP version (default to ${UPNP_VERSION_MAJOR}.${UPNP_VERSION_MINOR})"
		exit 1
		;;
	*)
		echo "Option not recognized : $argv"
		echo "use -h option to display help"
		exit 1
		;;
esac
done

# replace defaults
LEASEFILE=1
VENDORCFG=1
PCP=1

# need move to new glibc version
#IPV6=`cat ../../linux/.config | grep "CONFIG_IPV6=y" -c`
IPV6=

RM="rm -f"
MV="mv"
CONFIGFILE=`mktemp tmp.config.h.XXXXXXXXXX`
CONFIGFILE_FINAL="config.h"
CONFIGMACRO="CONFIG_H_INCLUDED"

MINIUPNPD_DATE=`date +"%Y%m%d"`
# Facility to syslog
LOG_MINIUPNPD="LOG_DAEMON"

# detecting the OS name and version
OS_NAME=Wifi-Router
OS_VERSION=Wive-RTNL
OS_URL=http://wive-ng.sf.net

${RM} ${CONFIGFILE}

echo "/* MiniUPnP Project" >> ${CONFIGFILE}
echo " * http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/" >> ${CONFIGFILE}
echo " * (c) 2006-2015 Thomas Bernard" >> ${CONFIGFILE}
echo " * generated by $0 on `date`" >> ${CONFIGFILE}
echo " * `uname -a`" >> ${CONFIGFILE}
echo " * using command line options $* */" >> ${CONFIGFILE}
echo "#ifndef $CONFIGMACRO" >> ${CONFIGFILE}
echo "#define $CONFIGMACRO" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}
echo "#include <inttypes.h>" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}
echo "#define MINIUPNPD_VERSION \"`cat VERSION`\"" >> ${CONFIGFILE}
echo "#define MINIUPNPD_DATE	\"$MINIUPNPD_DATE\"" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

cat >> ${CONFIGFILE} <<EOF
#ifndef XSTR
#define XSTR(s) STR(s)
#define STR(s) #s
#endif /* XSTR */
EOF

echo "" >> ${CONFIGFILE}
cat >> ${CONFIGFILE} <<EOF
/* UPnP version reported in XML descriptions
 * 1.0 / 1.1 / 2.0 depending on which UDA (UPnP Device Architecture) Version */
#define UPNP_VERSION_MAJOR	${UPNP_VERSION_MAJOR}
#define UPNP_VERSION_MINOR	${UPNP_VERSION_MINOR}
#define UPNP_VERSION_MAJOR_STR	XSTR(UPNP_VERSION_MAJOR)
#define UPNP_VERSION_MINOR_STR	XSTR(UPNP_VERSION_MINOR)
EOF
echo "" >> ${CONFIGFILE}

# OS Specific stuff
case $OS_NAME in
	OpenBSD)
		MAJORVER=`echo $OS_VERSION | cut -d. -f1`
		MINORVER=`echo $OS_VERSION | cut -d. -f2`
		#echo "OpenBSD majorversion=$MAJORVER minorversion=$MINORVER"
		# rtableid was introduced in OpenBSD 4.0
		if [ $MAJORVER -ge 4 ]; then
			echo "#define PFRULE_HAS_RTABLEID" >> ${CONFIGFILE}
		fi
		# from the 3.8 version, packets and bytes counters are double : in/out
		if [ \( $MAJORVER -ge 4 \) -o \( $MAJORVER -eq 3 -a $MINORVER -ge 8 \) ]; then
			echo "#define PFRULE_INOUT_COUNTS" >> ${CONFIGFILE}
		fi
		# from the 4.7 version, new pf
		if [ \( $MAJORVER -ge 5 \) -o \( $MAJORVER -eq 4 -a $MINORVER -ge 7 \) ]; then
			echo "#define PF_NEWSTYLE" >> ${CONFIGFILE}
		fi
		# onrdomain was introduced in OpenBSD 5.0
		if [ $MAJORVER -ge 5 ]; then
			echo "#define PFRULE_HAS_ONRDOMAIN" >> ${CONFIGFILE}
		fi
		FW=pf
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		OS_URL=http://www.openbsd.org/
		V6SOCKETS_ARE_V6ONLY=`sysctl -n net.inet6.ip6.v6only`
		;;
	FreeBSD)
		VER=`grep '#define __FreeBSD_version' /usr/include/sys/param.h | awk '{print $3}'`
		if [ $VER -ge 700049 ]; then
			echo "#define PFRULE_INOUT_COUNTS" >> ${CONFIGFILE}
		fi
		HAVE_IP_MREQN=1
		# new way to see which one to use PF or IPF.
		# see http://miniupnp.tuxfamily.org/forum/viewtopic.php?p=957
		if [ -f /etc/rc.subr ] && [ -f /etc/rc.conf ] ; then
			# source file with handy subroutines like checkyesno
			. /etc/rc.subr
			# source config file so we can probe vars
			. /etc/rc.conf
			if checkyesno ipfilter_enable; then
				echo "Using ipf"
			FW=ipf
			elif checkyesno pf_enable; then
				echo "Using pf"
				FW=pf
			elif checkyesno firewall_enable; then
				echo "Using ifpw"
				FW=ipfw
			fi
		fi
		if [ -z $FW ] ; then
			echo "Could not detect usage of ipf, pf, ipfw. Compiling for pf by default"
			FW=pf
		fi
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		OS_URL=http://www.freebsd.org/
		V6SOCKETS_ARE_V6ONLY=`sysctl -n net.inet6.ip6.v6only`
		;;
	pfSense)
		# we need to detect if PFRULE_INOUT_COUNTS macro is needed
		FW=pf
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		OS_URL=http://www.pfsense.com/
		V6SOCKETS_ARE_V6ONLY=`sysctl -n net.inet6.ip6.v6only`
		;;
	NetBSD)
		if [ -f /etc/rc.subr ] && [ -f /etc/rc.conf ] ; then
			# source file with handy subroutines like checkyesno
			. /etc/rc.subr
			# source config file so we can probe vars
			. /etc/rc.conf
			if checkyesno pf; then
				FW=pf
			elif checkyesno ipfilter; then
				FW=ipf
			fi
		fi
		if [ -z $FW ] ; then
			echo "Could not detect ipf nor pf, defaulting to pf."
			FW=pf
		fi
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		OS_URL=http://www.netbsd.org/
		;;
	DragonFly)
		if [ -f /etc/rc.subr ] && [ -f /etc/rc.conf ] ; then
			# source file with handy subroutines like checkyesno
			. /etc/rc.subr
			# source config file so we can probe vars
			. /etc/rc.conf
			if checkyesno pf; then
				FW=pf
			elif checkyesno ipfilter; then
				FW=ipf
			fi
		fi
		if [ -z $FW ] ; then
			echo "Could not detect ipf nor pf, defaulting to pf."
			FW=pf
		fi
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		OS_URL=http://www.dragonflybsd.org/
		;;
	SunOS)
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		FW=ipf
		echo "#define LOG_PERROR 0" >> ${CONFIGFILE}
		echo "#define SOLARIS_KSTATS 1" >> ${CONFIGFILE}
		# solaris 10 does not define u_int64_t ?
		# but it does define uint64_t
		echo "typedef uint64_t u_int64_t;" >> ${CONFIGFILE}
		OS_URL=http://www.sun.com/solaris/
		;;
	Linux)
		OS_URL=http://www.kernel.org/
		KERNVERA=`echo $OS_VERSION | awk -F. '{print $1}'`
		KERNVERB=`echo $OS_VERSION | awk -F. '{print $2}'`
		KERNVERC=`echo $OS_VERSION | awk -F. '{print $3}'`
		KERNVERD=`echo $OS_VERSION | awk -F. '{print $4}'`
		#echo "$KERNVERA.$KERNVERB.$KERNVERC.$KERNVERD"
		# from the 2.4 version, struct ip_mreqn instead of struct ip_mreq
		if [ \( $KERNVERA -ge 3 \) -o \( $KERNVERA -eq 2 -a $KERNVERB -ge 4 \) ]; then
			HAVE_IP_MREQN=1
		fi
		# Debian GNU/Linux special case
		if [ -f /etc/debian_version ]; then
			OS_NAME=Debian
			OS_VERSION=`cat /etc/debian_version`
			OS_URL=http://www.debian.org/
		fi
		# same thing for Gentoo linux
		if  [ -f /etc/gentoo-release ]; then
			OS_NAME=Gentoo
			OS_VERSION=`cat /etc/gentoo-release`
			OS_URL=http://www.gentoo.org/
		fi
		# use lsb_release (Linux Standard Base) when available
		LSB_RELEASE=`which lsb_release`
		if [ 0 -eq $? ]; then
			OS_NAME=`${LSB_RELEASE} -i -s`
			OS_VERSION=`${LSB_RELEASE} -r -s`
			case $OS_NAME in
				Debian)
					OS_URL=http://www.debian.org/
					OS_VERSION=`${LSB_RELEASE} -c -s`
					;;
				Ubuntu)
					OS_URL=http://www.ubuntu.com/
					OS_VERSION=`${LSB_RELEASE} -c -s`
					;;
				Gentoo)
					OS_URL=http://www.gentoo.org/
					;;
				arch)
					OS_URL=http://www.archlinux.org/
					OS_VERSION=`uname -r`
					;;
			esac
		fi
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		FW=netfilter
		V6SOCKETS_ARE_V6ONLY=`/sbin/sysctl -n net.ipv6.bindv6only`
		;;
	OpenWRT)
		OS_URL=http://www.openwrt.org/
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		FW=netfilter
		;;
	AstLinux)
		OS_URL=http://www.astlinux.org/
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		FW=netfilter
		;;
	Tomato)
		OS_NAME=UPnP
		OS_URL=http://tomatousb.org/
		echo "" >> ${CONFIGFILE}
		echo "#ifndef TOMATO" >> ${CONFIGFILE}
		echo "#define TOMATO" >> ${CONFIGFILE}
		echo "#endif" >> ${CONFIGFILE}
		echo "" >> ${CONFIGFILE}
		echo "#ifdef LINUX26" >> ${CONFIGFILE}
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		echo "#endif" >> ${CONFIGFILE}
		echo "#ifdef TCONFIG_IPV6" >> ${CONFIGFILE}
		echo "#define ENABLE_IPV6" >> ${CONFIGFILE}
		echo "#endif" >> ${CONFIGFILE}
		FW=netfilter
		;;
	Darwin)
		MAJORVER=`echo $OS_VERSION | cut -d. -f1`
		echo "#define USE_IFACEWATCHER 1" >> ${CONFIGFILE}
		# OS X switched to pf since 10.7 Lion (Darwin 11.0)
		if [ $MAJORVER -ge 11 ] ; then
			FW=pf
			echo "#define PFRULE_INOUT_COUNTS" >> ${CONFIGFILE}
		else
			FW=ipfw
		fi
		OS_URL=http://developer.apple.com/macosx
		;;
	Wifi-Router)
		echo "#define USE_NETFILTER 1" >> ${CONFIGFILE}
		FW=netfilter
		OS_NAME=Wive-RTNL
		OS_VERSION=${KERNEL_VER}
		OS_URL=http://wive-ng.sf.net
		;;
	*)
		echo "Unknown OS : $OS_NAME"
		echo "Please contact the author at http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/."
		exit 1
		;;
esac

case $FW in
	pf)
		echo "#define USE_PF 1" >> ${CONFIGFILE}
		;;
	ipf)
		echo "#define USE_IPF 1" >> ${CONFIGFILE}
		;;
	ipfw)
		echo "#define USE_IPFW 1" >> ${CONFIGFILE}
		;;
	netfilter)
		echo "#define USE_NETFILTER 1" >> ${CONFIGFILE}
		;;
	*)
		echo "Unknown Firewall/packet filtering software [$FW]"
		echo "Please contact the author at http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/."
		exit 1
		;;
esac

# set V6SOCKETS_ARE_V6ONLY to 0 if it was not set above
if [ -z "$V6SOCKETS_ARE_V6ONLY" ] ; then
	V6SOCKETS_ARE_V6ONLY=0
fi

echo "Configuring compilation for [$OS_NAME] [$OS_VERSION] with [$FW] firewall software."
echo "Please edit config.h for more compilation options."

# define SUPPORT_REMOTEHOST if the FW related code really supports setting
# a RemoteHost
if [ \( "$FW" = "netfilter" \) -o \( "$FW" = "pf" \) -o \( "$FW" = "ipfw" \) ] ; then
	echo "#define SUPPORT_REMOTEHOST" >> ${CONFIGFILE}
fi

echo "" >> ${CONFIGFILE}
echo "#define OS_NAME		\"$OS_NAME\"" >> ${CONFIGFILE}
echo "#define OS_VERSION	\"$OS_NAME/$OS_VERSION\"" >> ${CONFIGFILE}
echo "#define OS_URL		\"${OS_URL}\"" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* syslog facility to be used by miniupnpd */" >> ${CONFIGFILE}
echo "#define LOG_MINIUPNPD		 ${LOG_MINIUPNPD}" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to allow miniupnpd to be" >> ${CONFIGFILE}
echo " * controlled by miniupnpdctl */" >> ${CONFIGFILE}
echo "/*#define USE_MINIUPNPDCTL*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Comment the following line to disable NAT-PMP operations */" >> ${CONFIGFILE}
echo "#define ENABLE_NATPMP" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Comment the following line to disable PCP operations */" >> ${CONFIGFILE}
echo "#define ENABLE_PCP" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "#ifdef ENABLE_PCP" >> ${CONFIGFILE}
if [ -n "$PCP_PEER" ]; then
echo "/* Comment the following line to disable PCP PEER operation */" >> ${CONFIGFILE}
echo "#define PCP_PEER" >> ${CONFIGFILE}
else
echo "/* Uncomment the following line to enable PCP PEER operation */" >> ${CONFIGFILE}
echo "/*#define PCP_PEER*/" >> ${CONFIGFILE}
fi
echo "#ifdef PCP_PEER" >> ${CONFIGFILE}
echo "/*#define PCP_FLOWP*/" >> ${CONFIGFILE}
echo "#endif /*PCP_PEER*/" >> ${CONFIGFILE}
echo "/*#define PCP_SADSCP*/" >> ${CONFIGFILE}
echo "#endif /*ENABLE_PCP*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to enable generation of" >> ${CONFIGFILE}
echo " * filter rules with pf */" >> ${CONFIGFILE}
echo "/*#define PF_ENABLE_FILTER_RULES*/">> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to enable caching of results of" >> ${CONFIGFILE}
echo " * the getifstats() function */" >> ${CONFIGFILE}
echo "#define ENABLE_GETIFSTATS_CACHING" >> ${CONFIGFILE}
echo "/* The cache duration is indicated in seconds */" >> ${CONFIGFILE}
echo "#define GETIFSTATS_CACHING_DURATION 3" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to enable multiple external ip support */" >> ${CONFIGFILE}
echo "/* note : That is EXPERIMENTAL, do not use that unless you know perfectly what you are doing */" >> ${CONFIGFILE}
echo "/* Dynamic external ip adresses are not supported when this option is enabled." >> ${CONFIGFILE}
echo " * Also note that you would need to configure your .conf file accordingly. */" >> ${CONFIGFILE}
echo "/*#define MULTIPLE_EXTERNAL_IP*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Comment the following line to use home made daemonize() func instead" >> ${CONFIGFILE}
echo " * of BSD daemon() */" >> ${CONFIGFILE}
echo "#define USE_DAEMON" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to enable lease file support */" >> ${CONFIGFILE}
if [ -n "$LEASEFILE" ] ; then
	echo "#define ENABLE_LEASEFILE" >> ${CONFIGFILE}
else
	echo "/*#define ENABLE_LEASEFILE*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to enable port in use check */" >> ${CONFIGFILE}
if [ -n "$PORTINUSE" ]; then
	echo "#define CHECK_PORTINUSE" >> ${CONFIGFILE}
else
	echo "/*#define CHECK_PORTINUSE*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* Define one or none of the two following macros in order to make some" >> ${CONFIGFILE}
echo " * clients happy. It will change the XML Root Description of the IGD." >> ${CONFIGFILE}
echo " * Enabling the Layer3Forwarding Service seems to be the more compatible" >> ${CONFIGFILE}
echo " * option. */" >> ${CONFIGFILE}
echo "/*#define HAS_DUMMY_SERVICE*/" >> ${CONFIGFILE}
echo "#define ENABLE_L3F_SERVICE" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Enable IP v6 support */" >> ${CONFIGFILE}
if [ -n "$IPV6" ]; then
	echo "#define ENABLE_IPV6" >> ${CONFIGFILE}
else
	echo "/*#define ENABLE_IPV6*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* Define V6SOCKETS_ARE_V6ONLY if AF_INET6 sockets are restricted" >> ${CONFIGFILE}
echo " * to IPv6 communications only. */" >> ${CONFIGFILE}
if [ $V6SOCKETS_ARE_V6ONLY -eq 1 ] ; then
	echo "#define V6SOCKETS_ARE_V6ONLY" >> ${CONFIGFILE}
else
	echo "/*#define V6SOCKETS_ARE_V6ONLY*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

if [ -n "$HAVE_IP_MREQN" ]; then
	echo "#define HAVE_IP_MREQN" >> ${CONFIGFILE}
	echo "" >> ${CONFIGFILE}
fi

echo "/* Enable the support of IGD v2 specification." >> ${CONFIGFILE}
echo " * This is not fully tested yet and can cause incompatibilities with some" >> ${CONFIGFILE}
echo " * control points, so enable with care. */" >> ${CONFIGFILE}
if [ -n "$IGD2" ]; then
	echo "#define IGD_V2" >> ${CONFIGFILE}
else
	echo "/*#define IGD_V2*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "#ifdef IGD_V2" >> ${CONFIGFILE}
echo "/* Enable DeviceProtection service (IGDv2) */" >> ${CONFIGFILE}
echo "#define ENABLE_DP_SERVICE" >> ${CONFIGFILE}
echo "/*#define ENABLE_HTTPS*/" >> ${CONFIGFILE}
echo "/*#define HTTPS_CERTFILE \"/path/to/certificate.pem\"*/" >> ${CONFIGFILE}
echo "/*#define HTTPS_KEYFILE \"/path/to/private.key\"*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}
echo "/* Enable WANIPv6FirewallControl service (IGDv2). needs IPv6 */" >> ${CONFIGFILE}
echo "#ifdef ENABLE_IPV6" >> ${CONFIGFILE}
echo "#define ENABLE_6FC_SERVICE" >> ${CONFIGFILE}
echo "#endif /* ENABLE_IPV6 */" >> ${CONFIGFILE}
echo "#endif /* IGD_V2 */" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* UPnP Events support. Working well enough to be enabled by default." >> ${CONFIGFILE}
echo " * It can be disabled to save a few bytes. */" >> ${CONFIGFILE}
echo "#define ENABLE_EVENTS" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* include interface name in pf and ipf rules */" >> ${CONFIGFILE}
echo "/* #define USE_IFNAME_IN_RULES */" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Experimental NFQUEUE support. */" >> ${CONFIGFILE}
echo "/*#define ENABLE_NFQUEUE*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Enable to make MiniUPnPd more strict about UPnP conformance" >> ${CONFIGFILE}
echo " * and the messages it receives from control points */" >> ${CONFIGFILE}
if [ -n "$STRICT" ] ; then
	echo "#define UPNP_STRICT" >> ${CONFIGFILE}
else
	echo "/*#define UPNP_STRICT*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* If SSDP_RESPOND_SAME_VERSION is defined, the M-SEARCH response" >> ${CONFIGFILE}
echo " * include the same device version as was contained in the search" >> ${CONFIGFILE}
echo " * request. It conforms to UPnP DA v1.1 */" >> ${CONFIGFILE}
echo "#define SSDP_RESPOND_SAME_VERSION" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Add the optional Date: header in all HTTP responses */" >> ${CONFIGFILE}
if [ -n "$STRICT" ] ; then
	echo "#define ENABLE_HTTP_DATE" >> ${CONFIGFILE}
else
	echo "/*#define ENABLE_HTTP_DATE*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* Wait a little before answering M-SEARCH request */" >> ${CONFIGFILE}
if [ -n "$STRICT" ] ; then
	echo "#define DELAY_MSEARCH_RESPONSE" >> ${CONFIGFILE}
else
	echo "/*#define DELAY_MSEARCH_RESPONSE*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

echo "/* disable reading and parsing of config file (miniupnpd.conf) */" >> ${CONFIGFILE}
echo "/*#define DISABLE_CONFIG_FILE*/" >> ${CONFIGFILE}
echo "" >> ${CONFIGFILE}

echo "/* Uncomment the following line to configure all manufacturer infos through miniupnpd.conf */" >> ${CONFIGFILE}
if [ -n "$VENDORCFG" ] ; then
	echo "#define ENABLE_MANUFACTURER_INFO_CONFIGURATION" >> ${CONFIGFILE}
else
	echo "/*#define ENABLE_MANUFACTURER_INFO_CONFIGURATION*/" >> ${CONFIGFILE}
fi
echo "" >> ${CONFIGFILE}

cat >> ${CONFIGFILE} <<EOF
#if defined(ENABLE_6FC_SERVICE) || (defined(ENABLE_PCP) && defined(ENABLE_IPV6))
#define ENABLE_UPNPPINHOLE
#endif

EOF

cat >> ${CONFIGFILE} <<EOF
/* Uncomment the following line if your device does not have a proper clock
 * BOOTID.UPNP.ORG can be set with command line */
#define USE_TIME_AS_BOOTID

EOF

cat >> ${CONFIGFILE} <<EOF
/* maximum lenght of SSDP packets we are generating
 * (reception is done in a 1500byte buffer) */
#define SSDP_PACKET_MAX_LEN 1024

EOF

echo "#endif /* ${CONFIGMACRO} */" >> ${CONFIGFILE}

${MV} ${CONFIGFILE} ${CONFIGFILE_FINAL}

exit 0
