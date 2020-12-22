/*
 * pic.h - Header file for the Programmable Interrupt Controller (PIC).
 *
 * Author: Philip R. Simonson
 * Date: 12/22/2020
 *
 **************************************************************************
 */

#ifndef _PIC_H_
#define _PIC_H_

#include "types.h"

// The following devices use PIC 1 to generate interrupts.
#define I86_PIC_IRQ_TIMER 0
#define I86_PIC_IRQ_KEYBOARD 1
#define I86_PIC_IRQ_SERIAL2 3
#define I86_PIC_IRQ_SERIAL1 4
#define I86_PIC_IRQ_PARALLEL2 5
#define I86_PIC_IRQ_DISKETTE 6
#define I86_PIC_IRQ_PARALLEL1 7

// The following devices use PIC 2 to generate interrupts.
#define I86_PIC_IRQ_CMOSTIMER 0
#define I86_PIC_IRQ_CGARETRACE 1
#define I86_PIC_IRQ_AUXILIARY 4
#define I86_PIC_IRQ_FPU 5
#define I86_PIC_IRQ_HDC 6

// Command word 2 bit masks.
#define I86_PIC_OCW2_MASK_L1 1
#define I86_PIC_OCW2_MASK_L2 2
#define I86_PIC_OCW2_MASK_L3 4
#define I86_PIC_OCW2_MASK_EOI 0x20
#define I86_PIC_OCW2_MASK_SL 0x40
#define I86_PIC_OCW2_MASK_ROTATE 0x80

// Command word 3 bit masks.
#define I86_PIC_OCW3_MASK_RIS 1
#define I86_PIC_OCW3_MASK_RIR 2
#define I86_PIC_OCW3_MASK_MODE 4
#define I86_PIC_OCW3_MASK_SMM 0x20
#define I86_PIC_OCW3_MASK_ESMM 0x40
#define I86_PIC_OCW3_MASK_D7 0x80

#ifdef __cplusplus
extern "C" {
#endif

/* Read data byte from PIC. */
extern u8_t i86_pic_read_data(u8_t picno);
/* Send data byte to PIC. */
extern void i86_pic_send_data(u8_t data, u8_t picno);
/* Send operational command to PIC. */
extern void i86_pic_send_command(u8_t cmd, u8_t picno);
/* Initialize PIC. */
extern void i86_pic_init(u8_t base0, u8_t base1);

#ifdef __cplusplus
}
#endif

#endif
