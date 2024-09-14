.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4619004367821864960


_FP1:
.quad 4623226492472524800


_FP2:
.quad 4607182418800017408


_FP3:
.quad 4620130267728707584


.section .data

GlobalFloat1:
.quad 4615063718147915776


GlobalFloat2:
.quad 4620974692658839552


.section .text

.extern Assert

.extern AssertMsg

TestFloatIncrementDecrement:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
movsd xmm15,  [rip + _FP0]
movsd  [rbp - 8], xmm15
movsd xmm15,  [rip + _FP1]
movsd  [rbp - 16], xmm15
movsd xmm15,  [rbp - 8]
movsd qword ptr [rbp - 24], xmm15
movsd xmm14, xmm15
movsd xmm15,  [rip + _FP2]
addsd xmm14, xmm15
movsd  [rbp - 8], xmm14
mov r15, qword ptr [rbp - 24]
movsd  [rbp - 32], r15
movsd xmm14,  [rbp - 32]
comisd xmm14,  [rip + _FP0]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14,  [rbp - 8]
comisd xmm14,  [rip + _FP3]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 40
call TestFloatIncrementDecrement
mov qword ptr [rbp - 8], 0
jmp label4
label3:
jmp label4
label4:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

