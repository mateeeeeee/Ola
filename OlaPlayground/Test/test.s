.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4613937818241073152


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 16], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
comisd xmm15, xmm14
seta r15b
and r15b, 1
movsd xmm14, qword ptr [rbp - 16]
movsd xmm15, qword ptr [rbp - 24]
movsd xmm13, xmm15
test r15b, r15b
je label3
movsd xmm13, xmm14
label3:
movsd qword ptr [rbp - 32], xmm13
movsd xmm13, qword ptr [rbp - 32]
comisd xmm13, qword ptr [rip + _FP1]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 0
jmp label2
label1:
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret
