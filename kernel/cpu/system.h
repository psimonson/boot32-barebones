/*
 * system.h - Everything to do with CPU and other system functions.
 *
 * Author: Philip R. Simonson
 * Date: 12/09/2020
 *
 ************************************************************************
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Some CPU handling functions. */
extern void enable(void);
extern void disable(void);
extern void halt(void);

/* Other system functions. */
extern void gen_interrupt(int intno);

#ifdef __cplusplus
}
#endif

#endif
