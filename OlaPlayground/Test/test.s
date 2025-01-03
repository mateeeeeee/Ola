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
mov r15, 0
jmp label1
label1:
mov r14, r15
jmp label5
label2:
mov r15, 
jmp label1
label3:
mov rcx, 0
call Assert
cmp , 4
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label8
label4:
jmp label8
label5:
mov r13, r14
add r13, 1
jmp label6
label6:
cmp r13, 2
setl r12b
and r12b, 1
test r12b, r12b
mov r14, r13
jne label5
jmp label7
label7:
jmp label2
label8:
mov rax, 0
mov rsp, rbp
pop rbp
ret

