.intel_syntax noprefix

.section .rodata

.section .bss

.section .data

.section .text
.globl main
main:
push    rbp
mov     rbp, rsp
mov     dword ptr[rbp - 4], 0
mov eax, 0
pop rbp
ret

