#include <linux/module.h>
#include <linux/smp.h>
#include <linux/user.h>
#include <linux/elfcore.h>
#include <linux/sched.h>
#include <linux/in6.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>
#include <linux/pci.h>
#include <linux/irq.h>

#include <asm/semaphore.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <asm/tlbflush.h>
#include <asm/cacheflush.h>

extern int dump_fpu(struct pt_regs *, elf_fpregset_t *);
extern struct hw_interrupt_type no_irq_type;

EXPORT_SYMBOL(sh_mv);

/* platform dependent support */
EXPORT_SYMBOL(dump_fpu);
EXPORT_SYMBOL(kernel_thread);
EXPORT_SYMBOL(irq_desc);
EXPORT_SYMBOL(no_irq_type);

EXPORT_SYMBOL(strlen);

/* PCI exports */
#ifdef CONFIG_PCI
EXPORT_SYMBOL(pci_alloc_consistent);
EXPORT_SYMBOL(pci_free_consistent);
#endif

/* mem exports */
EXPORT_SYMBOL(memchr);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memmove);
EXPORT_SYMBOL(__copy_user);
EXPORT_SYMBOL(boot_cpu_data);

#ifdef CONFIG_MMU
EXPORT_SYMBOL(get_vm_area);
#endif

/* semaphore exports */
EXPORT_SYMBOL(__up);
EXPORT_SYMBOL(__down);
EXPORT_SYMBOL(__down_interruptible);

EXPORT_SYMBOL(__udelay);
EXPORT_SYMBOL(__ndelay);
EXPORT_SYMBOL(__const_udelay);

EXPORT_SYMBOL(__div64_32);

#define DECLARE_EXPORT(name) extern void name(void);EXPORT_SYMBOL(name)

/* These symbols are generated by the compiler itself */
DECLARE_EXPORT(__udivsi3);
DECLARE_EXPORT(__udivdi3);
DECLARE_EXPORT(__sdivsi3);
DECLARE_EXPORT(__ashrdi3);
DECLARE_EXPORT(__ashldi3);
DECLARE_EXPORT(__lshrdi3);
DECLARE_EXPORT(__movstrSI16);
#if __GNUC__ == 4
DECLARE_EXPORT(__movmem);
#else
DECLARE_EXPORT(__movstr);
#endif

#ifdef CONFIG_CPU_SH4
#if __GNUC__ == 4
DECLARE_EXPORT(__movmem_i4_even);
DECLARE_EXPORT(__movmem_i4_odd);
DECLARE_EXPORT(__movmemSI12_i4);
#else /* GCC 3.x */
DECLARE_EXPORT(__movstr_i4_even);
DECLARE_EXPORT(__movstr_i4_odd);
DECLARE_EXPORT(__movstrSI12_i4);
#endif /* __GNUC__ == 4 */
#endif

#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
/* needed by some modules */
EXPORT_SYMBOL(flush_cache_all);
EXPORT_SYMBOL(flush_cache_range);
EXPORT_SYMBOL(flush_dcache_page);
EXPORT_SYMBOL(__flush_purge_region);
#endif

#if defined(CONFIG_MMU) && (defined(CONFIG_CPU_SH4) || \
	defined(CONFIG_SH7705_CACHE_32KB))
EXPORT_SYMBOL(clear_user_page);
#endif

EXPORT_SYMBOL(__down_trylock);

#ifdef CONFIG_SMP
EXPORT_SYMBOL(synchronize_irq);
#endif

EXPORT_SYMBOL(csum_partial);
#ifdef CONFIG_IPV6
EXPORT_SYMBOL(csum_ipv6_magic);
#endif
EXPORT_SYMBOL(clear_page);
