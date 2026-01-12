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
sub rsp, 160
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd qword ptr [rbp - 56], xmm11
movsd qword ptr [rbp - 64], xmm10
movsd qword ptr [rbp - 72], xmm9
movsd qword ptr [rbp - 80], xmm8
movsd qword ptr [rbp - 88], xmm7
label3:
movsd xmm13, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 112], xmm13
movsd xmm12, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 120], xmm12
movsd xmm11, qword ptr [rbp - 112]
movsd xmm14, qword ptr [rbp - 120]
comisd xmm11, xmm14
seta r14b
and r14b, 1
movsd xmm10, qword ptr [rbp - 112]
movsd xmm9, qword ptr [rbp - 120]
movsd xmm8, xmm9
test r14b, r14b
je label3
movsd xmm8, xmm10
movsd qword ptr [rbp - 128], xmm8
movsd xmm7, qword ptr [rbp - 128]
comisd xmm7, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 104], 0
jmp label2
label1:
label2:
mov r12, qword ptr [rbp - 104]
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
movsd xmm13, qword ptr [rbp - 40]
movsd xmm12, qword ptr [rbp - 48]
movsd xmm11, qword ptr [rbp - 56]
movsd xmm10, qword ptr [rbp - 64]
movsd xmm9, qword ptr [rbp - 72]
movsd xmm8, qword ptr [rbp - 80]
movsd xmm7, qword ptr [rbp - 88]
mov rsp, rbp
pop rbp
ret
