.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

sum__I__I__I__I__I__I__I__I__I__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 96
mov r14, rcx
mov r13, rdx
mov r12, r8
mov rdi, r9
mov rsi, qword ptr [rbp + 48]
mov rbx, qword ptr [rbp + 56]
mov r15, qword ptr [rbp + 64]
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp + 72]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp + 80]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp + 88]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp + 96]
mov qword ptr [rbp - 136], r15
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov qword ptr [rbp - 40], rsi
mov qword ptr [rbp - 48], rbx
mov r15, qword ptr [rbp - 104]
mov qword ptr [rbp - 56], r15
mov r15, qword ptr [rbp - 112]
mov qword ptr [rbp - 64], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [rbp - 72], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [rbp - 80], r15
mov r15, qword ptr [rbp - 136]
mov qword ptr [rbp - 88], r15
mov rbx, qword ptr [rbp - 8]
mov rsi, qword ptr [rbp - 16]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 24]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 32]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 40]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 48]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 56]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 64]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 72]
mov rbx, rdi
add rbx, rsi
mov rsi, qword ptr [rbp - 80]
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rbp - 88]
mov rbx, rdi
add rbx, rsi
mov qword ptr [rbp - 96], rbx
jmp label2
label1:
label2:
mov rbx, qword ptr [rbp - 96]
mov rax, rbx
mov rsp, rbp
pop rbp
ret
.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 104
mov qword ptr [rbp - 24], 11
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
call sum__I__I__I__I__I__I__I__I__I__I__I
mov r14, rax
mov qword ptr [rbp - 16], r14
mov r14, qword ptr [rbp - 16]
mov qword ptr [rbp - 8], r14
jmp label5
label4:
label5:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret
