; ================================================
; Interrupt handler and interrupt server routines.
; Written by Philip R. Simonson
; ================================================

[section .text]
[bits 32]

%macro isr_return 1
	[global isr%1]
	isr%1:
		push byte %1
		jmp isr_common_stub
%endmacro

%macro isr_noret 1
	[global isr%1]
	isr%1:
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro

%macro irq_stub 2
	[global irq%1]
	irq%1:
		push byte %1
		push byte %2
		jmp irq_common_stub
%endmacro

[extern isr_handler]
[extern irq_handler]

; Common ISR code
isr_common_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp
	cld
	call isr_handler
	pop eax
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	iret

; Common IRQ code
irq_common_stub:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp
	cld
	call irq_handler
	pop ebx
	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	popa
	add esp, 8
	iret

; =========================
; ISRs Below
; =========================

isr_noret 0
isr_noret 1
isr_noret 2
isr_noret 3
isr_noret 4
isr_noret 5
isr_noret 6
isr_noret 7
isr_return 8
isr_noret 9
isr_return 10
isr_return 11
isr_return 12
isr_return 13
isr_return 14
isr_noret 15
isr_noret 16
isr_noret 17
isr_noret 18
isr_noret 19
isr_noret 20
isr_noret 21
isr_noret 22
isr_noret 23
isr_noret 24
isr_noret 25
isr_noret 26
isr_noret 27
isr_noret 28
isr_noret 29
isr_noret 30
isr_noret 31

; =========================
; IRQs Below
; =========================

irq_stub 0, 32
irq_stub 1, 33
irq_stub 2, 34
irq_stub 3, 35
irq_stub 4, 36
irq_stub 5, 37
irq_stub 6, 38
irq_stub 7, 39
irq_stub 8, 40
irq_stub 9, 41
irq_stub 10, 42
irq_stub 11, 43
irq_stub 12, 44
irq_stub 13, 45
irq_stub 14, 46
irq_stub 15, 47
