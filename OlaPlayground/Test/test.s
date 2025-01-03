.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 16], 10
mov qword ptr [rbp - 24], 20
mov r15, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
cmp r15, r14
setl r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label2
label1:
mov rcx, 1
call Assert
jmp label3
label2:
mov rcx, 0
call Assert
jmp label3
label3:
mov qword ptr [rbp - 8], 0
jmp label5
label4:
label5:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

