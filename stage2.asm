; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x0]

start:
	mov si, hello
	call print

	cli
	hlt

%include "common.inc"

hello db "This is stage 2 of this boot loader.",13,10,0
