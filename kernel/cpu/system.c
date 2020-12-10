/*
 * system.h - Everything to do with CPU and other system functions.
 *
 * Author: Philip R. Simonson
 * Date: 12/09/2020
 *
 ************************************************************************
 */

#include "system.h"


/* ------------------------- CPU Functions ----------------------- */


/* Enable CPU interrupts.
 */
void enable(void)
{
	__asm__ __volatile__("sti");
}
/* Disable CPU interrupts.
 */
void disable(void)
{
	__asm__ __volatile__("cli");
}
/* Halt CPU instructions.
 */
void halt(void)
{
	__asm__ __volatile__("cli; hlt");
}


/* -------------------- Other System Functions ------------------- */


