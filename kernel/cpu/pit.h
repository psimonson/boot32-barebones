/*
 * timer.h - Header file for the PIT implementation.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 *********************************************************************
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>

#include "types.h"
#include "regs.h"

// Operational command bit masks.
#define I86_PIT_OCW_MASK_BINCOUNT 1
#define I86_PIT_OCW_MASK_MODE 0xE
#define I86_PIT_OCW_MASK_RL 0x30
#define I86_PIT_OCW_MASK_COUNTER 0xC0

// Operational command control bits.
#define I86_PIT_OCW_BINCOUNT_BINARY 0
#define I86_PIT_OCW_BINCOUNT_BCD 1

// Used when setting counter mode.
#define I86_PIT_OCW_MODE_TERMINALCOUNT 0
#define I86_PIT_OCW_MODE_ONESHOT 0x2
#define I86_PIT_OCW_MODE_RATEGEN 0x4
#define I86_PIT_OCW_MODE_SQUAREWAVEGEN 0x6
#define I86_PIT_OCW_MODE_SOFTWARETRIG 0x8
#define I86_PIT_OCW_MODE_HARDWARETRIG 0xA

// Used when setting data transfer.
#define I86_PIT_OCW_RL_LATCH 0
#define I86_PIT_OCW_RL_LSBONLY 0x10
#define I86_PIT_OCW_RL_MSBONLY 0x20
#define I86_PIT_OCW_RL_DATA 0x30

// Used when setting the counter.
#define I86_PIT_OCW_COUNTER_0 0
#define I86_PIT_OCW_COUNTER_1 0x40
#define I86_PIT_OCW_COUNTER_2 0x80

/* Get timer ticks from kernel. */
extern u32_t get_timer_ticks(void);
/* Get timer seconds from kernel. */
extern int get_timer_seconds(void);
/* Get system registers current values. */
extern regs_t *get_current_regs(bool update);

/* Send operational command to PIT. */
extern void i86_pit_send_command(u8_t cmd);
/* Write data byte to a counter. */
extern void i86_pit_send_data(u16_t data, u8_t cmd);
/* Read data from a counter. */
extern u8_t i86_pit_read_data(u16_t counter);
/* Sets new PIT tick count and return previous value. */
extern u32_t i86_pit_set_tick_count(u32_t ticks);
/* Starts a counter. Counter continues until another call to this routine. */
extern void i86_pit_start_counter(u32_t freq, u8_t counter, u8_t mode);
/* Initialize minidriver. */
extern void i86_pit_initialize(void);
/* Call this function to initialize the PIT. */
extern void i86_pit_init(void);

#endif
