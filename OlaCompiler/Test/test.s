.intel_syntax noprefix

.section .rodata

.section .bss

.section .data

.section .text
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 16
and rsp, -16
entry:
mov qword ptr [rbp - 0], 14
mov r12, qword ptr [rbp - 0]
imul r12, 3
mov qword ptr [rbp - 8], r12
exit:
mov rax, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret

