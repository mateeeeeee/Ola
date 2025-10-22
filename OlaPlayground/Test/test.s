.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

f:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], 3
jmp label2
label1:
label2:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 40], 3
call f
mov r14, rax
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
sub r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 0
sete r12b
and r12b, 1
test r12b, r12b
jne label4
jmp label5
label4:
mov r12, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r14, r12
sub r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label6
label5:
mov rcx, 0
call Assert
jmp label6
label6:
mov qword ptr [rbp - 32], 0
jmp label8
label7:
label8:
mov r12, qword ptr [rbp - 32]
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
