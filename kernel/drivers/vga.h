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

#define REG_VGA_CTRL 0x3d4
#define REG_VGA_DATA 0x3d5

#define YELLOW_ON_BLUE 0x1b
#define WHITE_ON_BLACK 0x0f
#define RED_ON_BLUE    0x14

/* Initialize the terminal (Text Video Mode). */
void term_init(const char attr);
/* Print a string on screen at given (x, y). */
void kprint_at(int x, int y, const char *s, const char color);
/* Print a string on screen at current position. */
void kprint(const char *s, const char color);
/* Clear the screen. */
void clear_screen(const char attr);

#endif
