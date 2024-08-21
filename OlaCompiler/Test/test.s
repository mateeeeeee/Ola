.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

Array:
.zero 24
.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
lea r15, [rip + Array]
mov r14, r15
mov r15, 2
imul r15, 8
mov r14, r14
add r14, r15
mov r15, r14
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

