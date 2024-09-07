.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4627589354611539968


_FP1:
.quad -9223372036854775808


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
movsd xmm15,  [rip + _FP0]
movsd  [rbp - 16], xmm15
movsd xmm15,  [rbp - 16]
movsd xmm14, xmm15
movsd xmm15,  [rip + _FP1]
xorpd xmm14, xmm15
cvttsd2si r15, xmm14
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
mov r14, r15
neg r14
mov qword ptr [rbp - 8], r14
jmp label2
label1:
jmp label2
label2:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

