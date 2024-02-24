.intel_syntax noprefix

.section .rodata

.section .bss

.section .data

.section .text
.globl main
main:
mov rax, 12
jmp main_End
main_End:
ret

