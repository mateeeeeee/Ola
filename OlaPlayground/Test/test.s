.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4613937818241073152


_FP2:
.quad 4621256167635550208


_FP3:
.quad 4619567317775286272


.data

GlobalFloatC:
.quad 4616752568008179712


GlobalFloatD:
.quad 4621256167635550208


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
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 64], xmm14
movsd xmm14, qword ptr [rbp - 56]
lea r14, [rip + GlobalFloatD]
movsd xmm13, qword ptr [r14]
movsd xmm12, qword ptr [rbp - 56]
lea r14, [rip + GlobalFloatD]
movsd xmm11, qword ptr [r14]
comisd xmm14, xmm13
seta r14b
and r14b, 1
test r14b, r14b
movsd xmm13, xmm11
je label3
movsd xmm13, xmm12
jmp label3
label1:
label2:
mov r14, qword ptr [rbp - 48]
mov rax, r14
mov r14, qword ptr [rbp - 8]
movsd xmm14, qword ptr [rbp - 16]
movsd xmm13, qword ptr [rbp - 24]
movsd xmm12, qword ptr [rbp - 32]
movsd xmm11, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
label3:
movsd qword ptr [rbp - 72], xmm13
movsd xmm13, qword ptr [rbp - 72]
comisd xmm13, qword ptr [rip + _FP2]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 80], xmm13
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, qword ptr [rip + _FP3]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 48], 0
jmp label2
