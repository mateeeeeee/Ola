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
mov rax, 5
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
add r14, r15
mov r13, r15
add r13, r15
mov r15, r14
imul r15, r13
jmp label5
label4:
label5:
mov rax, r15
mov rsp, rbp
pop rbp
ret

