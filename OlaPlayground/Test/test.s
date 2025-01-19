.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestIfElse:
label0:
push rbp
mov rbp, rsp
jmp label1
label1:
mov rax, r15
mov rsp, rbp
pop rbp
ret

.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 32
call TestIfElse
mov r15, rax
cmp r15, 10
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label3
label3:
mov rax, 0
mov rsp, rbp
pop rbp
ret

