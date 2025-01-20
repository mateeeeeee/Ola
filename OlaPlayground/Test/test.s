.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

fact__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, rcx
cmp r15, 1
sete r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label2
label1:
mov r14, 5
jmp label3
label2:
mov r14, r15
sub r14, 1
mov rcx, r14
call fact__I
mov r14, rax
mov r13, r15
imul r13, r14
mov r14, r13
jmp label3
label3:
mov rax, r14
mov rsp, rbp
pop rbp
ret
.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 5
call fact__I
mov r15, rax
jmp label5
label5:
mov rax, r15
mov rsp, rbp
pop rbp
ret
