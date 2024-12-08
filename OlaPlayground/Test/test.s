.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 16], 5
mov r15, qword ptr [rbp - 16]
mov r14, r15
add r14, 6
mov qword ptr [rbp - 24], r14
mov r14, qword ptr [rbp - 24]
cmp r14, 10
setg r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label2
label1:
mov r14, qword ptr [rbp - 16]
mov qword ptr [rbp - 32], r14
mov r15, r14
add r15, 1
mov qword ptr [rbp - 16], r15
jmp label4
label2:
mov qword ptr [rbp - 8], 2
jmp label6
label3:
jmp label6
label4:
mov r15, qword ptr [rbp - 16]
mov qword ptr [rbp - 8], r15
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

