.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 65
mov byte ptr [rbp - 9], 1
mov qword ptr [rbp - 17], 5
mov qword ptr [rbp - 25], 10
mov r15b, byte ptr [rbp - 9]
mov r14, qword ptr [rbp - 17]
mov r13, qword ptr [rbp - 25]
mov r12, r13
test r15b, r15b
cmovne r12, r14
mov qword ptr [rbp - 33], r12
mov r12, qword ptr [rbp - 33]
cmp r12, 5
sete r12b
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 33]
mov qword ptr [rbp - 8], r12
jmp label2
label1:
jmp label2
label2:
mov r12, qword ptr [rbp - 8]
mov rax, r12
mov rsp, rbp
pop rbp
ret

