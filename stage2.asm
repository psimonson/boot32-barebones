; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x7e00]
[bits 16]

start:
	mov [iBootDrive], dl
	mov si, op_loading
	call print
	call reset_disk
	mov ax, 2
	mov cx, 3
	xor bx, bx
	mov es, bx
	mov bx, load_segment
	call read_disk

	call a20_bios
	call check_a20

	; switch on protected mode
	cli
	lgdt [gdt.pointer]
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp dword 0x08:INIT_PM

%include "common.inc"
%include "disk.inc"
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

	call load_segment
	cli

%include "common32.inc"

op_loading db "Loading kernel, please wait",0
op_done db "done!",10,13,0
op_a20yes db "A20 is enabled.",10,13,0
op_a20no db "A20 is disabled.",10,13,0
op_progress db 0x2e,0
op_failed db 10,13,"File not found!",10,13,0
load_segment equ 0x1000

%include "bs.inc"
