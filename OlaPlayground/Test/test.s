.intel_syntax noprefix

.section .text

.extern add__I__I

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
mov rdx, 2
mov rcx, 1
call add__I__I
mov r14, rax
jmp label1
label1:
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
