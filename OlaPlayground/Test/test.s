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
mov r14, 1
mov r14, 0
jmp label1
label1:
mov r15, r14
add r15, r14
mov r13, r14
add r13, 1
jmp label2
label2:
mov r14, r15
mov r14, r13
cmp r13, 5
setle r13b
and r13b, 1
test r13b, r13b
jne label1
jmp label3
label3:
cmp r15, 15
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label5
label4:
jmp label5
label5:
mov rax, 0
mov rsp, rbp
pop rbp
ret

