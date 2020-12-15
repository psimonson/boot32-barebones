; ================================================
; entry.asm - Boot32-Barebones Kernel Entrypoint.
; ================================================
; Author: Philip R. Simonson
; Date: 12/14/2020
; ================================================

[bits 32]

[extern kernel_main]
[global _start]

_start:
	pusha	;push all registers
	pushf	;push all flags

	; call main kernel function
	call kernel_main

	popf	; pop all flags
	popa	; pop all registers
	ret		; return to calling function
