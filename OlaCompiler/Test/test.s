.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4617878467915022336


_FP1:
.quad 4616414798036126925


.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
movsd xmm15,  [rip + _FP0]
movsd  [rbp - 16], xmm15
movsd xmm15,  [rbp - 16]
movsd xmm14, xmm15
movsd xmm15,  [rip + _FP1]
subsd xmm14, xmm15
cvttsd2si r15, xmm14
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

