#ifndef __ARCH_IA32_SYSCALLS_INCLUDED__
#define __ARCH_IA32_SYSCALLS_INCLUDED__

#include <arch/syscall-numbers.h>

#define _SYS_ARG0		0
#define _SYS_ARG1		1
#define _SYS_ARG2		2
#define _SYS_ARG3		3

#ifndef __ASM__
typedef uint32_t (*sys0_t)(void);
typedef uint32_t (*sys1_t)(uint32_t);
typedef uint32_t (*sys2_t)(uint32_t, uint32_t);
typedef uint32_t (*sys3_t)(uint32_t, uint32_t, uint32_t);

static inline uint32_t syscall1(uint32_t nr, uint32_t arg)
{
	uint32_t ret;
	asm volatile ("movl %1,%%eax\n"
			"movl %2, %%ebx\n"
			"int $0xff\n"
			"movl %%eax, %0\n"
			: "=r" (ret) : "r" (nr), "r" (arg)
			: "%eax", "%ebx");
	return ret;
}
#endif /* __ASM__ */

#endif /* __ARCH_IA32_SYSCALLS_INCLUDED__ */
