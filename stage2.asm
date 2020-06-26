; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x0]

start:
	call a20_bios
	call check_a20

	mov si, op_pmode
	call print

	cli
	lgdt [gdt.pointer]
	mov eax, cr0
	or al, 1
	mov cr0, eax
	sti

	mov si, op_pmode2
	call print

	cli
	hlt

%include "common.inc"
%include "a20.inc"

op_pmode db "Entering protected mode...",0
op_pmode2 db "done!",13,10,0
op_a20yes db "A20 is enabled.",13,10,0
op_a20no db "A20 is disabled.",13,10,0

; gdt stuff below
gdt:
.null: equ $-gdt
	dw 0
	dw 0
	db 0
	db 0
	db 0
	db 0
.code: equ $-gdt
	dw 0xffff
	dw 0
	db 0
	db 0x9a
	db 11001111b
	db 0
.data: equ $-gdt
	dw 0xffff
	dw 0
	db 0
	db 0x92
	db 11001111b
	db 0
.pointer:
	dw $-gdt-1
	dd gdt
