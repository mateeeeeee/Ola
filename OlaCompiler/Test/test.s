.intel_syntax noprefix

.bss

arr:
.zero 24
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
mov r15, 2
imul r15, 8
mov r14, r13
add r14, r15
mov qword ptr [r14], 5
lea r14, [rip + arr]
mov r15, r14
mov r14, 0
imul r14, 24
mov r13, r15
add r13, r14
mov r14, 2
imul r14, 8
mov r15, r13
add r15, r14
mov r14, qword ptr [r15]
mov qword ptr [rbp - 8], r14
jmp label2
label1:
jmp label2
label2:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

