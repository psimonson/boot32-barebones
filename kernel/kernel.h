/*
 * kernel.h - Header file for kernel.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 *************************************************************************
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

#define WELCOME_MESSAGE \
"Welcome to my bare bones example 32 bit operating system.\n" \
"\n  I have designed this because I would like to teach beginners\n" \
"the proper way of doing things. As far as a beginning operating\n" \
"system goes. Please feel free to clone and use it. If you are\n" \
"are wondering about what license. It has an MIT license so\n" \
"basically don't say you wrote it and you'll be fine. Other than\n" \
"that, you can use it for whatever you want. Also this software\n" \
"comes WITHOUT ANY WARRANTY of any kind. I will not be held\n" \
"accountable for any damage this software may cause. Please use\n" \
"it at your own risk.\n\n" \
"Cheers,\nPhilip R. Simonson (aka 5n4k3)\n\n" \
"Welcome to a bare bones kernel! Please login to the system.\n\nLOGIN? " \

/* Get user input and process it. */
void user_input(char *input);

#endif
