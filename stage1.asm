[org 0x7c00]
[bits 16]

[section .text]

global _start
_start:
	jmp 0:main
	nop

; put BPB here

main:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00
	cld

	mov [iBootDrive], dl
	call reset_disk

	mov si, op_loading
	call print

	mov ax, 1
	mov cl, 2
	xor bx, bx
	mov es, bx
	mov bx, load_segment
	call read_disk

	jmp 0:load_segment

%include "common.inc"
%include "disk.inc"

op_loading db "Loading stage 2, please wait",0
op_ferror db 10,13,"Disk error!",13,10,0
op_fdone db "success!",13,10,0
op_progress db 0x2e,0
iBootDrive db 0
load_segment dw 0x07e0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55
