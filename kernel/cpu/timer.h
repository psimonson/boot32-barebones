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

/* Call this function to install a timer. */
void install_timer(u32_t freq);

#endif
