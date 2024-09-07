.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4620130267728707584


_FP1:
.quad 4614162998222441677


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
divsd xmm14, xmm15
cvttsd2si r15, xmm14
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
mov qword ptr [rbp - 8], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

