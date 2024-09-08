.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4615063718147915776


_FP1:
.quad 4612811918334230528


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 25
movsd xmm15,  [rip + _FP0]
movsd  [rbp - 16], xmm15
movsd xmm15,  [rip + _FP1]
movsd  [rbp - 24], xmm15
movsd xmm15,  [rbp - 24]
movsd xmm14,  [rbp - 16]
comisd xmm15, xmm14
setg r15b
mov byte ptr [rbp - 25], r15b
mov r15b, byte ptr [rbp - 25]
movzx r14, r15b
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

