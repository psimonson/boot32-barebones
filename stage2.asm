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
	lgdt [gdt_desc]
	mov eax, cr0
	or al, 1
	mov cr0, eax

	jmp CODE_SEG:init_pm

	cli
	hlt

[bits 32]

init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov bp, 0x90000
	mov sp, bp

	jmp $

%include "common.inc"
%include "a20.inc"
%include "gdt.inc"

op_pmode db "Entering protected mode...",0
op_pmode2 db "done!",13,10,0
op_a20yes db "A20 is enabled.",13,10,0
op_a20no db "A20 is disabled.",13,10,0
