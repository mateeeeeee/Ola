.intel_syntax noprefix

.section .text

f__I__I__I__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov r15, rcx
mov r14, rdx
mov r13, r8
mov r12, r9
mov r11, qword ptr [rbp + 40]
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], r11
mov r11, qword ptr [rbp - 8]
mov r12, qword ptr [rbp - 16]
mov r13, r11
add r13, r12
mov r12, qword ptr [rbp - 24]
mov r11, r13
add r11, r12
mov r12, qword ptr [rbp - 32]
mov r13, r11
add r13, r12
mov r12, qword ptr [rbp - 40]
mov r11, r13
add r11, r12
mov qword ptr [rbp - 48], r11
jmp label2
label1:
label2:
mov r11, qword ptr [rbp - 48]
mov rax, r11
mov rsp, rbp
pop rbp
ret
.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 16], 5
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call f__I__I__I__I__I
mov r15, rax
mov qword ptr [rbp - 16], r15
mov r15, qword ptr [rbp - 16]
mov qword ptr [rbp - 8], r15
jmp label5
label4:
label5:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret
