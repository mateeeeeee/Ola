.intel_syntax noprefix

.text

add__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov r15, rcx
mov r14, rdx
mov qword ptr [rbp-8], r15
mov qword ptr [rbp-16], r14
mov r14, qword ptr [rbp-8]
mov r15, qword ptr [rbp-16]
mov r13, r14
add r13, r15
mov qword ptr [rbp-24], r13
jmp label2
label1:
jmp label2
label2:
mov r13, qword ptr [rbp-24]
mov rax, r13
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 48
mov rdx, 7
mov rcx, 5
call add__I__I
mov r15, rax
mov qword ptr [rbp-48], r15
mov r15, qword ptr [rbp-48]
mov r14, r15
add r14, 10
mov qword ptr [rbp-40], r14
jmp label5
label4:
jmp label5
label5:
mov r14, qword ptr [rbp-40]
mov rax, r14
mov rsp, rbp
pop rbp
ret

