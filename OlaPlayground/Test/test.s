.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

sum__I__I__I__I__I__I__I__I__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], rdi
mov qword ptr [rbp - 16], r15
mov qword ptr [rbp - 24], rsi
mov qword ptr [rbp - 32], r14
mov qword ptr [rbp - 40], rbx
mov qword ptr [rbp - 48], r13
mov qword ptr [rbp - 56], r12
mov r15, rcx
mov r14, rdx
mov r13, r8
mov r12, r9
mov rdi, qword ptr [rbp + 48]
mov rsi, qword ptr [rbp + 56]
mov rbx, qword ptr [rbp + 64]
mov qword ptr [rbp - 152], qword ptr [rbp + 72]
mov qword ptr [rbp - 160], qword ptr [rbp + 80]
mov qword ptr [rbp - 168], qword ptr [rbp + 88]
mov qword ptr [rbp - 64], r15
mov qword ptr [rbp - 72], r14
mov qword ptr [rbp - 80], r13
mov qword ptr [rbp - 88], r12
mov qword ptr [rbp - 96], rdi
mov qword ptr [rbp - 104], rsi
mov qword ptr [rbp - 112], rbx
mov qword ptr [rbp - 120], qword ptr [rbp - 120]
mov qword ptr [rbp - 128], qword ptr [rbp - 128]
mov qword ptr [rbp - 136], qword ptr [rbp - 136]
mov rbx, qword ptr [rbp - 64]
mov rsi, qword ptr [rbp - 72]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 80]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 88]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 96]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 104]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 112]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 120]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 128]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 136]
mov rdi, rbx
add rdi, rsi
mov qword ptr [rbp - 144], rdi
jmp label2
label1:
label2:
mov rdi, qword ptr [rbp - 144]
mov rax, rdi
mov rdi, qword ptr [rbp - 8]
mov r15, qword ptr [rbp - 16]
mov rsi, qword ptr [rbp - 24]
mov r14, qword ptr [rbp - 32]
mov rbx, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, qword ptr [rbp - 56]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 104
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 32], 10
mov qword ptr [rbp - 40], 9
mov qword ptr [rbp - 48], 8
mov qword ptr [rbp - 56], 7
mov qword ptr [rbp - 64], 6
mov qword ptr [rbp - 72], 5
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call sum__I__I__I__I__I__I__I__I__I__I
mov r15, rax
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
mov qword ptr [rbp - 16], r15
jmp label5
label4:
label5:
mov r15, qword ptr [rbp - 16]
mov rax, r15
mov r15, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
