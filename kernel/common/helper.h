/*
 * helper.h - Header file for miscellaneous functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 *********************************************************************
 */

#ifndef _HELPER_H_
#define _HELPER_H_

/* String functions */
int strlen(const char *s);
int strstrip(char *s);
int strcmp(const char *s, const char *t);
void reverse(char *s, int len);
void itoa(int n, char *s, int size);

/* Functions for kernel. */
void append(char *s, char c);
void backspace(char *s);

#endif
