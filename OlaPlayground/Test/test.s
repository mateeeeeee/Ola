.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4613937818241073152


.text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r14
movsd qword ptr [rbp - 16], xmm14
movsd qword ptr [rbp - 24], xmm13
movsd qword ptr [rbp - 32], xmm12
movsd qword ptr [rbp - 40], xmm11
movsd qword ptr [rbp - 48], xmm10
movsd xmm14, xmm13
test r14b, r14b
je label3
movsd xmm14, xmm12
label3:
movsd xmm11, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 64], xmm11
movsd xmm11, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 72], xmm11
movsd xmm11, qword ptr [rbp - 64]
movsd xmm10, qword ptr [rbp - 72]
comisd xmm11, xmm10
seta r14b
and r14b, 1
movsd xmm12, qword ptr [rbp - 64]
movsd xmm13, qword ptr [rbp - 72]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP0]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 56], 0
jmp label2
label1:
label2:
mov r14, qword ptr [rbp - 56]
mov rax, r14
mov r14, qword ptr [rbp - 8]
movsd xmm14, qword ptr [rbp - 16]
movsd xmm13, qword ptr [rbp - 24]
movsd xmm12, qword ptr [rbp - 32]
movsd xmm11, qword ptr [rbp - 40]
movsd xmm10, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
