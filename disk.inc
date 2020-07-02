; simple BIOS disk services

; ======================================
; reset disk drive
; ======================================
reset_disk:
	push ax
	xor ax, ax
	mov dl, [iBootDrive]
	int 0x13
	pop ax
	ret

; ==================================================
; Description: Load a file from my file table.
; No parameters.
; ==================================================
load_file:
	mov bx, root_segment
	mov es, bx
	mov bx, root_offset
.loop:
	mov al, [bx]
	cmp al, 0x0
	je .error
	mov cx, 11
	mov di, bx
	mov si, op_filename
	rep cmpsb
	je .found
	add bx, 16
	jmp short .loop
.found:
	mov ax, word [es:bx+0x0c]
	mov cx, word [es:bx+0x0e]
	mov bx, load_segment
	mov es, bx
	mov bx, load_offset
	call read_disk
	ret
.error:
	mov si, op_ferror
	call print
	ret

; ==================================================
; Description: Calculate and store the LBA address.
; ax - LBA (Logical Block Address)
; ==================================================
lbachs:
	push ax
	push bx
	push dx
	; calculate sector
	xor dx, dx
	mov bx, word [iTrackSect]
	div bx
	inc dx
	mov [abs_sector], dl
	; calculate track/head
	mov bx, word [iHeadCnt]
	xor dx, dx
	div bx
	mov [abs_track], al
	xchg [abs_head], dl
	pop dx
	pop bx
	pop ax
	ret

; ==================================================
; Description: Load file from disk using LBA.
; ax - LBA (Logical Block Address)
; cx - Number of sectors to read.
; [es:bx] - Location to store at (in memory).
; ==================================================
read_disk:
	mov di, 5
.loop:
	push ax
	push cx
	call lbachs
	mov ax, 0x0201
	mov ch, [abs_track]
	mov cl, [abs_sector]
	mov dh, [abs_head]
	mov dl, [iBootDrive]
	int 0x13
	jnc .success
	call reset_disk
	dec di
	pop cx
	pop ax
	cmp di, 0
	jne .loop
	mov si, op_ferror
	call print
	jmp $
.success:
	mov si, op_progress
	call print
	pop cx
	pop ax
	inc ax
	add bx, word [iSectSize]
	loop read_disk
	mov si, op_done
	call print
	ret

abs_sector db 0x00
abs_track db 0x00
abs_head db 0x00

