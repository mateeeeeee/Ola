.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov qword ptr [rbp-16], 10
mov qword ptr [rbp-24], 0
mov r15, qword ptr [rbp-16]
cmp r15, 11
setg r15b
test r15b, r15b
jne label1
jmp label2
label1:
mov r15, qword ptr [rbp-24]
mov r14, r15
add r14, 10
mov qword ptr [rbp-24], r14
jmp label3
label2:
mov r14, qword ptr [rbp-24]
mov r15, r14
sub r15, 10
mov qword ptr [rbp-24], r15
jmp label3
label3:
mov r15, qword ptr [rbp-24]
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

