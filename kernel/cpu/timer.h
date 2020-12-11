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

#include "types.h"

/* Get timer ticks from kernel. */
extern u32_t get_timer_ticks(void);
/* Get timer seconds from kernel. */
extern int get_timer_seconds(void);
/* Call this function to install a timer. */
extern void install_timer(u32_t freq);

#endif
