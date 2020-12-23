/*
 * hal.h - Hardware Abstraction Layer (HAL) interface header file.
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 *********************************************************************
 */

#ifndef _HAL_H_
#define _HAL_H_

#include "isr.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize HAL interface. */
extern void hal_init(void);
/* Shutdown HAL interface. */
extern void hal_shutdown(void);

/* Generate an interrupt. */
extern void gen_interrupt(int intno);
/* Send EOI to PIC. */
extern void interrupt_done(unsigned int intno);
/* Set new interrupt vector. */
extern void set_vect(int intno, void (*vect)());
/* Get current interrupt vector. */
extern isr_handler_t get_vect(int intno);

#ifdef __cplusplus
}
#endif

#endif
