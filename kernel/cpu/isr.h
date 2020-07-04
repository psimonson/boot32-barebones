/*
 * isr.h - Header file for ISR implementation.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 **********************************************************************
 */

#ifndef _ISR_H_
#define _ISR_H_

#include "types.h"

/* ISRs reserved for CPU exceptions. */
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

/* Struct which aggregates many registers. */
typedef struct registers {
	u32_t ds;
	u32_t edi, esi, ebp, esp;
	u32_t eax, ebx, ecx, edx;
	u32_t int_no, err_code;
	u32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) registers_t;

/* Functions implemented in isr.c */
void isr_install(void);
void isr_handler(registers_t r);

#endif
