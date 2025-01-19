.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
jmp label1
label1:
mov rax, 8
mov rsp, rbp
pop rbp
ret

