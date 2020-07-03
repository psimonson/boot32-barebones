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
	push bx
	push ax
	; calculate sector
	xor dx, dx
	div word [iTrackSect]
	inc dl
	mov [abs_sector], dl
	; calculate head
	xor dx, dx
	div word [iHeadCnt]
	mov [abs_head], dl
	; finally track
	mov ax, word [iHeadCnt]
	mul word [iTrackSect]
	xor dx, dx
	xchg bx, ax
	pop ax
	div bx
	mov byte [abs_track], al
	xor dx, dx
	pop bx
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
	push bx
	push cx
	call lbachs
	mov ax, 0x0201
	mov ch, byte [abs_track]
	mov cl, byte [abs_sector]
	mov dh, byte [abs_head]
	mov dl, byte [iBootDrive]
	int 0x13
	jnc .success
	call reset_disk
	dec di
	pop cx
	pop bx
	pop ax
	jnz .loop
	mov si, op_ferror
	call print
	jmp $
.success:
	mov si, op_progress
	call print
	pop cx
	pop bx
	pop ax
	add bx, word [iSectSize]
	inc ax
	loop read_disk
	mov si, op_done
	call print
	ret

abs_sector resb 1
abs_track resb 1
abs_head resb 1

