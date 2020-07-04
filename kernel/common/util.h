/*
 * util.h - Common utility functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 **********************************************************
 */

#ifndef _UTIL_H_
#define _UTIL_H_

/* Functions implemented in util.c */
void memcpy(void *dest, const void *src, unsigned long nbytes);
void itoa(int n, char *s, int size);

#endif
