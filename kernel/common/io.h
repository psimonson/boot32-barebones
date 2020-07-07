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

/* Print a string at given (column,row). */
void print_at(int col, int row, char *message);
/* Print a string at current position. */
void print(char *message);
/* Print a backspace character on the screen. */
void print_bkspc(void);
/* Print a hexadecimal value to the screen. */
void print_hex(unsigned int n);

#endif
