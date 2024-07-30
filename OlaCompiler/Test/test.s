.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

global:
.quad 5


add__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov r15, rcx
mov r14, rdx
mov qword ptr [rbp-8], r15
mov qword ptr [rbp-16], r14
mov r14, qword ptr [rbp-8]
mov r15, qword ptr [rbp-16]
mov r13, r14
add r13, r15
mov qword ptr [rbp-24], r13
jmp label2
label1:
jmp label2
label2:
mov r13, qword ptr [rbp-24]
mov rax, r13
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 16
mov rdx, 2
mov rcx, 1
call add__I__I
mov r15, rax
mov qword ptr [rbp-16], r15
mov r15, qword ptr [rbp-16]
cmp r15, 3
sete r15b
mov cl, r15b
call Assert
mov r15, qword ptr [rbp-16]
mov qword ptr [rbp-8], r15
jmp label5
label4:
jmp label5
label5:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

