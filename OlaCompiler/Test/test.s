.intel_syntax noprefix

.text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, 3
imul r15, 5
mov qword ptr [rbp-16], r15
mov r15, qword ptr [rbp-16]
mov r14, r15
imul r14, 2
mov qword ptr [rbp-24], r14
mov r14, qword ptr [rbp-24]
mov rax, r14
cqo
mov r14, 4
idiv r14
mov r14, rax
mov qword ptr [rbp-32], r14
mov r14, qword ptr [rbp-32]
mov qword ptr [rbp-8], r14
jmp label2
label1:
jmp label2
label2:
mov r14, qword ptr [rbp-8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

