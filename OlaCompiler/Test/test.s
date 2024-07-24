.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

f:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp-16], 3
mov qword ptr [rbp-24], 5
mov r15, qword ptr [rbp-16]
mov r14, qword ptr [rbp-24]
mov r13, r15
add r13, r14
mov qword ptr [rbp-32], r13
mov r13, qword ptr [rbp-32]
mov qword ptr [rbp-8], r13
jmp label2
label1:
jmp label2
label2:
mov r13, qword ptr [rbp-8]
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
call f
mov r15, rax
mov qword ptr [rbp-16], r15
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

