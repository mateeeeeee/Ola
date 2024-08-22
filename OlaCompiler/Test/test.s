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
lea r9, [rip + Array]
mov r15, r9
mov r14, 0
imul r14, 24
mov r13, r15
add r13, r14
mov r12, 2
imul r12, 8
mov r11, r13
add r11, r12
mov r11, 10
mov qword ptr [rbp - 8], 0
jmp label2
label1:
jmp label2
label2:
mov r10, qword ptr [rbp - 8]
mov rax, r10
mov rsp, rbp
pop rbp
ret

