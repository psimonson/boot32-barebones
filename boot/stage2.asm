; stage 2 boot loader.
; by Philip Simonson.
; =======================

[org 0x7e00]
[bits 16]

start:
	mov [iBootDrive], dl
	call reset_disk

	; set text mode (80x25)
	mov ax, 0x0003
	int 0x10

	call a20_bios
	call check_a20

	mov si, op_loading
	call print
	call load_file

	; load kernel from sectors
	mov bx, load_segment
	mov es, bx
	xor bx, bx
	call read_disk

	; switch on protected mode
	cli
	lgdt [gdt.pointer]
	lidt [idt.pointer]
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp dword 0x08:INIT_PM

%include "common.inc"
%include "disk.inc"
%include "a20.inc"
%include "gdt.inc"
%include "idt.inc"
%include "boot.inc"

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

	call run_offset
	jmp $

%include "common32.inc"

; data
op_loading db "Loading kernel, please wait",0
op_done db "done!",10,13,0
op_a20yes db "A20 is enabled.",10,13,0
op_a20no db "A20 is disabled.",10,13,0
op_progress db 0x2e,0
op_ferror db 10,13,"File not found!",10,13,0
op_filename db "kernel  bin",0

; constants
root_segment equ 0x0ee0
load_segment equ 0x1000
run_offset equ 0x00010000
