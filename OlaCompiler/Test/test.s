.intel_syntax noprefix

.data

arr:
.quad 1
.quad 2
.quad 3


.text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
lea r15, [rip + arr]
mov r14, r15
mov r15, 0
imul r15, 24
mov r13, r14
add r13, r15
mov r15, 1
imul r15, 8
mov r14, r13
add r14, r15
mov r15, qword ptr [r14]
mov qword ptr [rbp - 8], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

