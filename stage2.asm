; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x0]
[bits 16]

start:
	call a20_bios
	call check_a20

	mov si, op_pmode
	call print

	; switch on protected mode
	cli
	lgdt [gdt.pointer]
	mov eax, cr0
	or eax, 1
	mov cr0, eax

;	hlt ; uncomment to test before jump instruction
	jmp dword 0x08:INIT_PM

%include "common.inc"
%include "a20.inc"
%include "gdt.inc"

[bits 32]

INIT_PM:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM
	hlt

BEGIN_PM:
	ret


op_pmode db "Entering protected mode...",0
op_pmode2 db "done!",13,10,0
op_a20yes db "A20 is enabled.",13,10,0
op_a20no db "A20 is disabled.",13,10,0
