/*
 * io.h - Header file for standard output functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/01/2020
 *
 ******************************************************************
 */

#ifndef _IO_H_
#define _IO_H_

/* Print character to console */
void kputc(char c);
/* Print string to console */
int kputs(const char *s);
/* Print formatted string to console */
int kprintf(const char *formatted, ...);

#endif
