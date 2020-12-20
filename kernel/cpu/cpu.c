/*
 * cpu.c - Source file for CPU.
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 ************************************************************************
 */

#include "cpu.h"
#include "gdt.h"
#include "idt.h"

/* Initialize the CPU's resources.
 */
void i86_cpu_init(void)
{
	i86_gdt_init();
	i86_idt_init(0x8);
}
/* Deinitialize CPU resources.
 */
void i86_cpu_shutdown(void)
{
}
