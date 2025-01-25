.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], 0
jmp label2
label1:
label2:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
