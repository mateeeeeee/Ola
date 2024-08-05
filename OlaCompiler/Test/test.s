.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestWhileLoopWithBreak:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp-8], 0
mov qword ptr [rbp-16], 1
jmp label1
label1:
jmp label2
label2:
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
mov r13, r15
add r13, r14
mov qword ptr [rbp-8], r13
mov r13, qword ptr [rbp-16]
mov r14, qword ptr [rbp-16]
mov qword ptr [rbp-24], r14
mov r14, r13
add r14, 1
mov qword ptr [rbp-16], r14
mov r14, qword ptr [rbp-16]
cmp r14, 5
setg r14b
test r14b, r14b
jne label4
jmp label6
label3:
mov r14, qword ptr [rbp-8]
cmp r14, 15
sete r14b
mov cl, r14b
call Assert
jmp label8
label4:
jmp label3
label5:
jmp label8
label6:
jmp label1
label7:
jmp label8
label8:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label9:
push rbp
mov rbp, rsp
sub rsp, 40
call TestWhileLoopWithBreak
mov qword ptr [rbp-8], 0
jmp label11
label10:
jmp label11
label11:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

