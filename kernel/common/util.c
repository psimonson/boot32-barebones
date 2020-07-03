/*
 * util.c - Common utility functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 **************************************************************
 */

#include "util.h"

/* Copies memory from source to destination, using specified number of bytes.
 */
void memcpy(void *dest, const void *src, unsigned long bytes)
{
	char *d = (char*)dest;
	char *s = (char*)src;
	while(bytes-- > 0) {
		*d = *s;
		d++, s++;
	}
}
