.section .data
gdtr:
    .word 0
    .long 0

.section .text
.global setGdt
setGdt:
    movl 4(%esp), %eax
    movw %ax, gdtr
    movl 8(%esp), %eax
    movl %eax, gdtr+2
    lgdt gdtr
    ret

.global reloadSegments
reloadSegments:
    jmp $0x08, $reload_CS_label

reload_CS_label:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ret
