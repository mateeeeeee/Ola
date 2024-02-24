.intel_syntax noprefix

.section .rodata

.section .bss

.section .data

.section .text
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 8
and rsp, -16
entry:
mov qword ptr [rbp - 0], 17
exit:
mov rax, qword ptr [rbp - 0]
mov rsp, rbp
pop rbp
ret

