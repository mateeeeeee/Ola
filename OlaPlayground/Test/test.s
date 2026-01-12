.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4613937818241073152


_FP2:
.quad 4617315517961601024


_FP3:
.quad 4619567317775286272


_FP4:
.quad 4621256167635550208


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
sub rsp, 128
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
label4:
movsd qword ptr [rbp - 80], xmm12
movsd xmm12, qword ptr [rbp - 80]
comisd r14b, xmm12
mov cl, r14b
call Assert
lea r14, [rip + GlobalFloatC]
movsd xmm12, qword ptr [r14]
lea r14, [rip + GlobalFloatC]
movsd xmm11, qword ptr [r14]
comisd r14b, xmm12
test r14b, r14b
movsd xmm12, qword ptr [rip + _FP2]
cmovne xmm12, xmm11
movsd qword ptr [rbp - 88], xmm12
movsd xmm12, qword ptr [rbp - 88]
comisd r14b, xmm12
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm15
movsd xmm12, qword ptr [rbp - 96]
comisd r14b, xmm12
mov cl, r14b
call Assert
mov qword ptr [rbp - 48], 0
jmp label2
label3:
movsd qword ptr [rbp - 72], xmm13
movsd xmm13, qword ptr [rbp - 72]
comisd xmm13, qword ptr [rip + _FP4]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalFloatC]
movsd xmm13, qword ptr [r14]
lea r14, [rip + GlobalFloatD]
movsd xmm12, qword ptr [r14]
lea r14, [rip + GlobalFloatC]
movsd xmm11, qword ptr [r14]
lea r14, [rip + GlobalFloatD]
movsd xmm14, qword ptr [r14]
comisd xmm13, xmm12
seta r14b
and r14b, 1
test r14b, r14b
movsd xmm12, xmm14
je label4
movsd xmm12, xmm11
jmp label4
