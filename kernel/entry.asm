; entry point for kernel

[bits 32]
extern kernel_main

global _start
_start:
	pusha
	pushf
	call kernel_main
	popf
	popa
	ret
