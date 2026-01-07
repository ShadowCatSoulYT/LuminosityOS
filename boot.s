; boot.s - super tiny bootloader
[bits 16]        ; start in 16-bit real mode
[org 0x7c00]     ; BIOS loads boot sector here

; setup stack
cli
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7C00
sti

; Reset disk system
mov ah, 0
int 0x13

; --- Switch to VGA Graphics Mode 13h (320x200, 256 colors) ---
mov ax, 0x0013
int 0x10

; Load kernel from disk
; We assume kernel is in sector 2 onwards
mov ax, 0x0000
mov es, ax
mov bx, 0x1000    ; destination address 0x0000:0x1000

; Try reading with retry
mov di, 5          ; 5 retries
.retry:
    mov ah, 0x02      ; BIOS read sectors
    mov al, 10        ; Read 10 sectors
    mov ch, 0         ; cylinder 0
    mov dh, 0         ; head 0
    mov cl, 2         ; starting sector
    int 0x13
    jnc .success      ; If no error, continue
    
    ; Reset disk system on error
    xor ax, ax
    int 0x13
    dec di
    jnz .retry
    jmp disk_error

.success:
; --- Switch to 32-bit Protected Mode ---
cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp 0x08:init_pm

[bits 32]
init_pm:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    call 0x1000
    jmp $

; GDT
gdt_start:
    dq 0x0
gdt_code:
    dw 0xffff, 0x0
    db 0x0, 0b10011010, 0b11001111, 0x0
gdt_data:
    dw 0xffff, 0x0
    db 0x0, 0b10010010, 0b11001111, 0x0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[bits 16]
disk_error:
    mov si, err_msg
    mov ah, 0x0E
.loop:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    hlt

err_msg db "Disk Error!", 0

; fill rest of boot sector with zeros
times 510-($-$$) db 0

; boot signature (required)
dw 0xAA55
