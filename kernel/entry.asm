; entry point for kernel

[bits 32]

section .text

extern kernel_main

global _start
_start:
	call kernel_main
	hlt
