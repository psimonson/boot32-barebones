/*
 * timer.c - Source file for system timer.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 ******************************************************************
 */

#include "timer.h"
#include "ports.h"
#include "isr.h"

u32_t _kernel_ticks = 0;

/* Count ticks for timer.
 */
static void timer_callback(registers_t *regs)
{
	_kernel_ticks++;
	(void)regs;
}
/* Get timer ticks from kernel.
 */
u32_t get_timer_ticks(void)
{
	return _kernel_ticks;
}
/* Initialize the system timer.
 */
void install_timer(u32_t freq)
{
	// Install the timer callback.
	register_interrupt_handler(IRQ0, timer_callback);

	// Get the PIT value: hardware clock at 1193180 Hz.
	u32_t divisor = 1193180 / freq;
	u8_t low = (u8_t)(divisor & 0xFF);
	u8_t high = (u8_t)((divisor >> 8) & 0xFF);

	// Send the command.
	outb(0x43, 0x36); // Command port
	outb(0x40, low);
	outb(0x40, high);
}
