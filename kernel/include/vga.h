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
/* Put a character on the screen. */
void terminal_putentryat(int x, int y, char ch, unsigned char color);
/* Print a string on screen. */
void terminal_print(int x, int y, const char *s, unsigned char color);
/* Enable the terminal cursor. */
void terminal_cursor_on(void);
/* Disable the terminal cursor. */
void terminal_cursor_off(void);

#endif
