.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
jmp label3
label1:
jmp label4
label2:
jmp label1
label3:
jmp label2
label4:
mov rax, 8
mov rsp, rbp
pop rbp
ret

