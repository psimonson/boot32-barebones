; Defined in isr.c
[extern isr_handler]

; Common ISR code
isr_common_stub:
	; Save CPU state
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; Call C handler
	call isr_handler

	; Restore state
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8	; Cleans up the pushed error code and ISR number
	sti					; Restore interrupts
	iret 				; pops 5 things at once: CS, EIP, EFLAGS, SS and ESP

; Below are the interrupts
; ========================

; Make interrupts global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Divide by zero exception
isr0:
	cli
	push byte 0
	push byte 0
	jmp isr_common_stub

; 1: Debug exception
isr1:
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub

; 2: Non maskable interrupt exception
isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub

; 3: Int 3 exception
isr3:
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub

; 4: INTO exception
isr4:
	cli
	push byte 0
	push byte 4
	jmp isr_common_stub

; 5: Out of bounds exception
isr5:
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub

; 6: Invalid opcode exception
isr6:
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub

; 7: Coprocessor not available
isr7:
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub

; 8: Double fault exception
isr8:
	cli
	push byte 8
	jmp isr_common_stub

; 9: Coprocessor segment overrun exception
isr9:
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub

; 10: Bad TSS exception (with error code!)
isr10:
	cli
	push byte 10
	jmp isr_common_stub

; 11: Segment not present exception (with error code!)
isr11:
	cli
	push byte 11
	jmp isr_common_stub

; 12: Stack fault exception (with error code!)
isr12:
	cli
	push byte 12
	jmp isr_common_stub

; 13: General protection fault exception (with error code!)
isr13:
	cli
	push byte 13
	jmp isr_common_stub

; 14: Page fault exception (with error code!)
isr14:
	cli
	push byte 14
	jmp isr_common_stub

; 15: Reserved exception
isr15:
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub

; 16: Floating point exception
isr16:
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub

; 17: Alignment check exception
isr17:
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub

; 18: Machine check exception
isr18:
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub

; 19: Reserved
isr19:
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub

; 20: Reserved
isr20:
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub

; 21: Reserved
isr21:
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub

; 22: Reserved
isr22:
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub

; 23: Reserved
isr23:
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub

; 24: Reserved
isr24:
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub

; 25: Reserved
isr25:
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub

; 26: Reserved
isr26:
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub

; 27: Reserved
isr27:
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub

; 28: Reserved
isr28:
	cli
	push byte 0
	push byte 28
	jmp isr_common_stub

; 29: Reserved
isr29:
	cli
	push byte 0
	push byte 29
	jmp isr_common_stub

; 30: Reserved
isr30:
	cli
	push byte 0
	push byte 30
	jmp isr_common_stub

; 31: Reserved
isr31:
	cli
	push byte 0
	push byte 31
	jmp isr_common_stub

