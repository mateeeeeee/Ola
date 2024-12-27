.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
mov r15, 0
mov r14, 1
jmp label2
label1:
mov r13, r15
add r13, r14
jmp label3
label2:
cmp r14, 5
setle r15b
and r15b, 1
test r15b, r15b
jne label1
jmp label4
label3:
mov r15, r14
add r15, 1
mov r15, r13
mov r14, r15
jmp label2
label4:
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label6
label5:
jmp label6
label6:
mov rax, 0
mov rsp, rbp
pop rbp
ret

