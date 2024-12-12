.intel_syntax noprefix

.section .text

f__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, rcx
mov r14, rdx
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr [rbp - 16]
cmp r14, r15
setl r15b
and r15b, 1
test r15b, r15b
jne label1
jmp label2
label1:
mov r15, qword ptr [rbp - 8]
mov qword ptr [rbp - 32], r15
jmp label3
label2:
mov r15, qword ptr [rbp - 16]
mov qword ptr [rbp - 32], r15
jmp label3
label3:
mov r15, qword ptr [rbp - 32]
mov qword ptr [rbp - 24], r15
jmp label5
label4:
jmp label5
label5:
mov r15, qword ptr [rbp - 24]
mov rax, r15
mov rsp, rbp
pop rbp
ret

.globl main

main:
label6:
push rbp
mov rbp, rsp
sub rsp, 40
mov rdx, 4
mov rcx, 3
call f__I__I
mov r15, rax
mov qword ptr [rbp - 8], r15
jmp label8
label7:
jmp label8
label8:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

