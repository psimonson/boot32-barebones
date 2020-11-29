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
int strlen(const char *s);
int strstrip(char *s);
int strcmp(const char *s, const char *t);
void reverse(char *s);
void itoa_s(int n, unsigned base, char *s, int size);

/* Functions for kernel. */
void append(char *s, char c);
void backspace(char *s);

#ifdef __cplusplus
}
#endif

#endif
