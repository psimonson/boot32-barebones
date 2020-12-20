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

/* Get timer ticks from kernel. */
extern u32_t get_timer_ticks(void);
/* Get timer seconds from kernel. */
extern int get_timer_seconds(void);
/* Get system registers current values. */
extern regs_t *get_current_regs(bool update);
/* Call this function to install a timer. */
extern void install_timer(u32_t freq);

#endif
