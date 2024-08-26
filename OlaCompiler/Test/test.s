.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
lea r15,  [rbp - 40]
mov r14, 0
imul r14, 32
mov r13, r15
add r13, r14
mov r14, 0
imul r14, 8
mov r15, r13
add r15, r14
mov qword ptr [r15], 1
lea r15,  [rbp - 40]
mov r14, 0
imul r14, 32
mov r13, r15
add r13, r14
mov r14, 1
imul r14, 8
mov r15, r13
add r15, r14
mov qword ptr [r15], 2
lea r15,  [rbp - 40]
mov r14, 0
imul r14, 32
mov r13, r15
add r13, r14
mov r14, 2
imul r14, 8
mov r15, r13
add r15, r14
mov qword ptr [r15], 3
lea r15,  [rbp - 40]
mov r14, 0
imul r14, 32
mov r13, r15
add r13, r14
mov r14, 3
imul r14, 8
mov r15, r13
add r15, r14
mov qword ptr [r15], 0
lea r15,  [rbp - 40]
mov r14, 0
imul r14, 32
mov r13, r15
add r13, r14
mov r14, 3
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

