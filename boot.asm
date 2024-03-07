[bits 16]
[org 0x7c00]

main:
    mov si, boot_msg
    call print
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, [0x7c00]
    call check_pci
    call check_cpuid
    jmp $

check_pci:
    mov ax, 0xb101
    int 0x1a
    jc error_handling
    cmp al, 0x80
    jne no_pci
    xor bx, bx
    pci_loop:
        mov ax, 0xb108
        mov cx, bx
        xor dx, dx
        int 0x1a
        jc error_handling
        test ax, ax
        jnz no_pci
        mov si, pci_msg
        call print
        inc bx
        jmp pci_loop
    ret

no_pci:
    mov si, no_pci_msg
    call print
    ret

check_cpuid:
    xor eax, eax
    cpuid
    cmp eax, 1
    jl no_cpuid

no_cpuid:
    mov si, no_cpuid_msg
    call print
    ret

error_handling:
    mov si, error_msg
    call print
    jmp $

print:
    mov ah, 0x0e
    mov al, [si]
    pb_loop:
        int 0x10
        inc si
        mov al, [si]
        cmp al, 0
        jne pb_loop
    ret

boot_msg db "Booting System...", 13, 10, 0
pci_msg db "PCI device found..." 13, 10, 0
no_pci_msg db "ERROR: No PCI devices found", 13, 10, 0
no_cpuid_msg db "ERROR: No CPUID support", 13, 10, 0
error_msg db "ERROR: An error occurred", 13, 10, 0

times 510 - ($-$$) db 0
dw 0xaa55