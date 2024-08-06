.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestIntAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, r15
add r13, r14
mov qword ptr [rbp - 24], r13
mov r13, qword ptr [rbp - 24]
cmp r13, 15
sete r13b
mov cl, r13b
call Assert
mov qword ptr [rbp - 32], 7
mov r13, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 32]
mov r15, r13
add r15, r14
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
cmp r15, 12
sete r15b
mov cl, r15b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

TestIntSubtraction:
label2:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 15
mov qword ptr [rbp - 16], 7
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, r15
sub r13, r14
mov qword ptr [rbp - 24], r13
mov r13, qword ptr [rbp - 24]
cmp r13, 8
sete r13b
mov cl, r13b
call Assert
mov qword ptr [rbp - 32], 3
mov r13, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 32]
mov r15, r13
sub r15, r14
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
cmp r15, 12
sete r15b
mov cl, r15b
call Assert
jmp label3
label3:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 40
call TestIntAddition
call TestIntSubtraction
mov qword ptr [rbp - 8], 0
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

