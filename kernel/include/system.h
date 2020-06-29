/*
 * system.h - Miscellaneous system functions go here.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 *****************************************************************
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/* Get value from given port. */
unsigned char inb(unsigned short port);
/* Put value to given port. */
void outb(unsigned short port, unsigned char value);

#endif
