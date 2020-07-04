/*
 * types.h - Various data types shortened.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 ***********************************************************
 */

#ifndef _TYPES_H_
#define _TYPES_H_

/* Unsigned data types. */
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long u64_t;

/* Signed data types. */
typedef signed char s8_t;
typedef signed short s16_t;
typedef signed int s32_t;
typedef signed long s64_t;

#define low_16(addr) (u16_t)((addr) & 0xFFFF)
#define high_16(addr) (u16_t)(((addr) >> 16) & 0xFFFF)

#endif
