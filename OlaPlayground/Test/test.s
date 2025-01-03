.intel_syntax noprefix

.section .rodata

global_sub_1:
.quad 15


global_sub_2:
.quad 7


global_sub_3:
.quad 3


global_sub_4:
.quad 30


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 96
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r15, qword ptr global_sub_1[rip]
mov r14, qword ptr global_sub_2[rip]
mov r13, r15
sub r13, r14
cmp r13, 8
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_sub_4[rip]
mov r14, r13
sub r14, 7
cmp r14, 23
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_sub_3[rip]
mov r13, 15
sub r13, r14
cmp r13, 12
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label2
label1:
label2:
mov rax, 0
mov rsp, rbp
pop rbp
ret

