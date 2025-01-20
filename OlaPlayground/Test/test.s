.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 16], 5
mov r15, qword ptr [rbp - 16]
mov r14, r15
not r14
mov qword ptr [rbp - 24], r14
mov r14, qword ptr [rbp - 24]
cmp r14, -6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 8], 0
jmp label2
label1:
label2:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret
