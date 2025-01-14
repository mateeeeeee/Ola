.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

f:
label0:
push rbp
mov rbp, rsp
jmp label2
label1:
label2:
mov rax, 24
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 32
call f
mov r15, rax
mov r14, r15
sar r14, 3
jmp label5
label4:
label5:
mov rax, r14
mov rsp, rbp
pop rbp
ret

