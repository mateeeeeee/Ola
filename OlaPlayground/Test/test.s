.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 1
call Assert
jmp label2
label1:
label2:
mov rax, 0
mov rsp, rbp
pop rbp
ret

