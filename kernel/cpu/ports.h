/*
 * system.h - Miscellaneous system functions go here.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 *****************************************************************
 */

#ifndef _PORTS_H_
#define _PORTS_H_

/* Get byte from given port. */
extern unsigned char inb(unsigned short port);
/* Put byte to given port. */
extern void outb(unsigned short port, unsigned char value);
/* Get short from given port. */
extern unsigned short inw(unsigned short port);
/* Put short to given port. */
extern void outw(unsigned short port, unsigned short value);

#endif
