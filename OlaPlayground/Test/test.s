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
mov r15, 1
mov r14, 0
jmp label2
label1:
mov r13, r14
add r13, r15
jmp label3
label2:
cmp r15, 5
setle r13b
and r13b, 1
test r13b, r13b
jne label1
jmp label4
label3:
mov r12, r15
add r12, 1
mov r15, r12
mov r14, r13
jmp label2
label4:
cmp r13, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label6
label5:
jmp label6
label6:
mov rax, 0
mov rsp, rbp
pop rbp
ret

