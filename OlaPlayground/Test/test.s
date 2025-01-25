.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestIfElse:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 24], 6
mov r15, qword ptr [rbp - 24]
cmp r15, 5
setg r15b
and r15b, 1
test r15b, r15b
jne label1
jmp label3
label1:
mov qword ptr [rbp - 16], 10
jmp label6
label2:
label3:
mov qword ptr [rbp - 16], 0
jmp label6
label4:
label5:
label6:
mov r15, qword ptr [rbp - 16]
mov rax, r15
mov r15, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
TestWhile:
label7:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 32], 0
jmp label8
label8:
mov r15, qword ptr [rbp - 32]
cmp r15, 10
setl r15b
and r15b, 1
test r15b, r15b
jne label9
jmp label10
label9:
mov r15, qword ptr [rbp - 32]
cmp r15, 5
sete r15b
and r15b, 1
test r15b, r15b
jne label12
jmp label15
label10:
mov qword ptr [rbp - 24], 0
jmp label16
label11:
label12:
mov r14, qword ptr [rbp - 32]
mov r15, r14
imul r15, 2
mov qword ptr [rbp - 24], r15
jmp label16
label13:
label14:
label15:
mov r15, qword ptr [rbp - 32]
mov r14, r15
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label8
label16:
mov r15, qword ptr [rbp - 24]
mov rax, r15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label17:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 8], r15
call TestIfElse
mov r15, rax
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
cmp r15, 10
sete r15b
and r15b, 1
mov cl, r15b
call Assert
call TestWhile
mov r15, rax
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
cmp r15, 10
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 16], 0
jmp label19
label18:
label19:
mov r15, qword ptr [rbp - 16]
mov rax, r15
mov r15, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
