.intel_syntax noprefix

.section .text

f__I:
label0:
push rbp
mov rbp, rsp
mov r15, rcx
mov r14, r15
add r14, 5
jmp label2
label1:
label2:
mov rax, r14
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 3
call f__I
mov r15, rax
mov r14, r15
add r14, 5
jmp label5
label4:
label5:
mov rax, r14
mov rsp, rbp
pop rbp
ret

