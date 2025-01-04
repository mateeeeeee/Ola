.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestGotoErrorHandling:
label0:
push rbp
mov rbp, rsp
jmp label3
label1:
mov r15, -1
mov r14, -1
jmp label8
label2:
label3:
jmp label1
label4:
label5:
mov r15, 42
mov r14, 42
jmp label8
label6:
label7:
label8:
mov rax, r14
mov rsp, rbp
pop rbp
ret

.globl main

main:
label9:
push rbp
mov rbp, rsp
sub rsp, 32
call TestGotoErrorHandling
mov r15, rax
cmp r15, -1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label11
label10:
label11:
mov rax, 0
mov rsp, rbp
pop rbp
ret

