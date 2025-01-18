.intel_syntax noprefix

.section .rodata

global_int_3:
.quad 7


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, qword ptr global_int_3[rip]
mov r14, r15
add r14, 5
cmp r14, 12
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label2
label1:
label2:
mov rax, 0
mov rsp, rbp
pop rbp
ret

