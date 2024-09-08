.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 0


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
comisd xmm15,  [rip + _FP1]
setne r15b
and r15b, 1
test r15b, r15b
jne label1
jmp label4
label1:
mov qword ptr [rbp - 8], 10
jmp label6
label2:
jmp label6
label3:
jmp label6
label4:
mov qword ptr [rbp - 8], 10000
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

