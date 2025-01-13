.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
mov r15, 0
mov r14, 0
jmp label2
label1:
mov r13, r14
add r13, 6
jmp label3
label2:
cmp r15, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label1
jmp label4
label3:
mov r12, r15
add r12, 1
mov r11, 6
mov r15, r12
mov r14, r13
jmp label2
label4:
jmp label6
label5:
label6:
mov rax, r14
mov rsp, rbp
pop rbp
ret

