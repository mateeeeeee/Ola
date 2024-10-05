.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 16], 2
mov r15, qword ptr [rbp - 16]
mov qword ptr [rbp - 8], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

