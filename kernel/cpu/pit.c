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
#include "hal.h"

#define I86_PIT_REG_COUNTER0 0x40
#define I86_PIT_REG_COUNTER1 0x41
#define I86_PIT_REG_COUNTER2 0x42
#define I86_PIT_REG_COMMAND 0x43

static volatile u32_t _kernel_ticks = 0;
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

	interrupt_done(IRQ0);
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
/* Sets new PIT tick counter and returns previous.
 */
u32_t i86_pit_set_tick_count(u32_t ticks)
{
	u32_t ret = _kernel_ticks;
	_kernel_ticks = ticks;
	return ret;
}
/* Send command to PIT.
 */
void i86_pit_send_command(u8_t cmd)
{
	outb(I86_PIT_REG_COMMAND, cmd);
}
/* Send data to a counter.
 */
void i86_pit_send_data(u16_t data, u8_t cmd)
{
	u8_t port = (cmd == I86_PIT_OCW_COUNTER_0) ? I86_PIT_REG_COUNTER0 :
		((cmd == I86_PIT_OCW_COUNTER_1) ? I86_PIT_REG_COUNTER1 :
		I86_PIT_REG_COUNTER2);

	outb(port, data);
}
/* Read data from a counter.
 */
u8_t i86_pit_read_data(u16_t counter)
{
	u8_t port = (counter == I86_PIT_OCW_COUNTER_0) ? I86_PIT_REG_COUNTER0 :
		((counter == I86_PIT_OCW_COUNTER_1) ? I86_PIT_REG_COUNTER1 :
		I86_PIT_REG_COUNTER2);

	return inb(port);
}
/* Initialize the system timer.
 */
void i86_pit_start_counter(u32_t freq, u8_t counter, u8_t mode)
{
	if(freq == 0) return;

	// Get the PIT value: hardware clock at 1193180 Hz.
	u32_t divisor = 1193180 / freq;

	// Send the command.
	u8_t ocw = 0;
	ocw = (ocw & ~I86_PIT_OCW_MASK_MODE) | mode;
	ocw = (ocw & ~I86_PIT_OCW_MASK_RL) | I86_PIT_OCW_RL_DATA;
	ocw = (ocw & ~I86_PIT_OCW_MASK_COUNTER) | counter;
	i86_pit_send_command(ocw);

	// Set frequency rate.
	u8_t low = (u8_t)(divisor & 0xFF);
	u8_t high = (u8_t)((divisor >> 8) & 0xFF);
	i86_pit_send_data(low, counter);
	i86_pit_send_data(high, counter);

	// Set register update state.
	regs_update = true;
}
/* Initialize the system PIT.
 */
void i86_pit_init(void)
{
	// Install the timer callback.
	register_interrupt_handler(IRQ0, timer_callback);

	_kernel_ticks = 0;
}
