.intel_syntax noprefix

.section .data

x:
.quad 10


.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 16], 5
mov qword ptr x[rip], 5
mov r15, qword ptr x[rip]
mov r14, qword ptr [rbp - 16]
mov r13, r15
add r13, r14
mov qword ptr [rbp - 8], r13
jmp label2
label1:
jmp label2
label2:
mov r13, qword ptr [rbp - 8]
mov rax, r13
mov rsp, rbp
pop rbp
ret

