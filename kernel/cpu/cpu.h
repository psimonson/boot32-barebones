/*
 * cpu.h - Header file for CPU.
 *
 * Author: Philip R. Simonson
 * Date: 12/20/2020
 *
 ************************************************************************
 */

#ifndef _CPU_H_
#define _CPU_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize the CPU's resources. */
void i86_cpu_init(void);
/* Deinitialize CPU resources. */
void i86_cpu_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif
