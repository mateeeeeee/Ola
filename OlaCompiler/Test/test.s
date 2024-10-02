.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 16], 5
mov r15, qword ptr [rbp - 16]
mov r14, r15
sar r14, 2
mov qword ptr [rbp - 24], r14
mov qword ptr [rbp - 32], 123
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 8], r14
jmp label2
label1:
jmp label2
label2:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

