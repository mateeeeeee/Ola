.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
jmp label1
label1:
mov rax, 20
ret

