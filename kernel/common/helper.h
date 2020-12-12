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

#ifdef __cplusplus
extern "C" {
#endif

/* Standard NULL */

#ifdef NULL
#undef NULL
#endif

#ifdef __cplusplus
#define NULL 0
#else
#define NULL (void*)0
#endif

/* String functions */
extern int strlen(const char *s);
extern int strstrip(char *s);
extern int strcmp(const char *s, const char *t);
extern void reverse(char *s);
extern void itoa_s(int n, unsigned base, char *s, int size);

/* Functions for kernel. */
extern void delay(unsigned int ticks);
extern void sleep(unsigned int secs);
extern void append(char *s, char c);
extern void backspace(char *s);

#ifdef __cplusplus
}
#endif

#endif
