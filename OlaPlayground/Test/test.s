.intel_syntax noprefix

.section .text

g:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 40], 110
mov qword ptr [rbp - 48], 107
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
sub r12, r13
mov qword ptr [rbp - 32], r12
jmp label2
label1:
label2:
mov r12, qword ptr [rbp - 32]
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
jmp label5
label4:
mov rax, r13
cqo
mov r13, 3
idiv r13
mov r13, rax
jmp label6
label5:
call g
mov r14, rax
mov r13, 30
add r13, r14
jmp label4
label6:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
