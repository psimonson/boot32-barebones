/*
 * vga.h - Header file for a very simple VGA graphics driver.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 **********************************************************************
 */

#ifndef _VGA_H_
#define _VGA_H_

/* Initialize the terminal (Text Video Mode). */
void terminal_initialize(void);
/* Put a character on screen at given (x, y). */
void terminal_putentryat(int x, int y, char ch, unsigned char color);
/* Put a character on screen. */
void terminal_putc(char ch, unsigned char color);
/* Print a string on screen. */
void terminal_print(const char *s, unsigned char color);
/* Enable the terminal cursor. */
void terminal_cursor_on(void);
/* Disable the terminal cursor. */
void terminal_cursor_off(void);

#endif
