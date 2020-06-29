; entry point for kernel

[bits 32]
extern kernel_main

global _start
_start:
	pusha
	pushf
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	call kernel_main
	popf
	popa
	ret
