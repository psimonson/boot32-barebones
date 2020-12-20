/*
 * timer.c - Source file for system timer.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 ******************************************************************
 */

#include "regs.h"
#include "pit.h"
#include "ports.h"
#include "isr.h"

static u32_t _kernel_ticks = 0;
static regs_t _regs;

extern bool regs_update;

/* Count ticks for timer.
 */
static void timer_callback(registers_t *regs)
{
	_kernel_ticks++;

	if(regs_update) { // Update registers
		__asm__ __volatile__(
			""
			: "=a"(_regs.eax), "=b"(_regs.ebx), "=c"(_regs.ecx), "=d"(_regs.edx),
			"=S"(_regs.esi), "=D"(_regs.edi)
		);
		regs_update = false;
	}

	(void)regs;
}
/* Get timer ticks from kernel.
 */
u32_t get_timer_ticks(void)
{
	return _kernel_ticks;
}
/* Get timer seconds from kernel.
 */
int get_timer_seconds(void)
{
	return (_kernel_ticks % 18) == 0 ? (_kernel_ticks / 18) : 0;
}
/* Get system registers current values.
 */
regs_t *get_current_regs(bool update)
{
	regs_update = update;
	return &_regs;
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

	// Set register update state.
	regs_update = true;
}
