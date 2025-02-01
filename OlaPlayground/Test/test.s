.intel_syntax noprefix

.section .text

TestNestedForLoopsReset:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
jmp label2
label1:
mov qword ptr [rbp - 40], 0
jmp label6
label2:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label4
label3:
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 24], r13
jmp label2
label4:
jmp label9
label5:
mov r13, qword ptr [rbp - 32]
mov qword ptr [rbp - 56], r13
mov r14, r13
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label7
label6:
mov r14, qword ptr [rbp - 40]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label5
jmp label8
label7:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 64], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label6
label8:
jmp label3
label9:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label10:
push rbp
mov rbp, rsp
sub rsp, 32
call TestNestedForLoopsReset
jmp label11
label11:
mov rax, 0
mov rsp, rbp
pop rbp
ret
