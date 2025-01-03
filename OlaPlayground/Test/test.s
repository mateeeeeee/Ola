.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 16], 0
mov qword ptr [rbp - 24], 0
jmp label1
label1:
jmp label5
label2:
mov r15, qword ptr [rbp - 16]
cmp r15, 3
setl r15b
and r15b, 1
test r15b, r15b
jne label1
jmp label3
label3:
mov r15, qword ptr [rbp - 16]
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 24]
cmp r15, 4
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 0
jmp label8
label4:
label5:
mov r15, qword ptr [rbp - 24]
mov qword ptr [rbp - 32], r15
mov r14, r15
add r14, 1
mov qword ptr [rbp - 24], r14
jmp label6
label6:
mov r14, qword ptr [rbp - 24]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label5
jmp label7
label7:
mov r14, qword ptr [rbp - 16]
mov qword ptr [rbp - 40], r14
mov r15, r14
add r15, 1
mov qword ptr [rbp - 16], r15
jmp label2
label8:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

