.intel_syntax noprefix

.text

add__I__I__I__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov r14, rcx
mov r13, rdx
mov r12, r8
mov r11, r9
mov qword ptr [rbp-8], r14
mov qword ptr [rbp-16], r13
mov qword ptr [rbp-24], r12
mov qword ptr [rbp-32], r11
mov qword ptr [rbp-40], r15
mov r15, qword ptr [rbp-8]
mov r11, qword ptr [rbp-16]
mov r12, r15
add r12, r11
mov r11, qword ptr [rbp-24]
mov r15, r12
add r15, r11
mov r11, qword ptr [rbp-32]
mov r12, r15
add r12, r11
mov r11, qword ptr [rbp-40]
mov r15, r12
add r15, r11
mov qword ptr [rbp-48], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp-48]
mov rax, r15
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp-56], 5
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call add__I__I__I__I__I
mov r15, rax
mov qword ptr [rbp-16], r15
mov r15, qword ptr [rbp-16]
mov qword ptr [rbp-8], r15
jmp label5
label4:
jmp label5
label5:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

