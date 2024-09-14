.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4617315517961601024


_FP2:
.quad 4620130267728707584


_FP3:
.quad 4624633867356078080


_FP4:
.quad 4611686018427387904


_FP5:
.quad 4609434218613702656


_FP6:
.quad 4621819117588971520


.section .data

GlobalIntX:
.quad 15


GlobalIntY:
.quad 20


GlobalFloatX:
.quad 4620130267728707584


GlobalFloatY:
.quad 4623226492472524800


.section .text

.extern Assert

.extern AssertMsg

TestLessThanOperators:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
cmp r15, r14
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
comisd xmm15, xmm14
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr GlobalIntY[rip]
cmp r14, r15
setl r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr [rbp - 24]
movsd xmm15, qword ptr GlobalFloatY[rip]
comisd xmm14, xmm15
setb r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
cmp r15, 20
setl r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 24]
comisd xmm15, qword ptr [rip + _FP2]
setb r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
cmp r15, r14
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm15, xmm14
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 30
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm14, qword ptr [rip + _FP3]
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4609434218613702656, qword ptr [rip + _FP4]
setb r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

TestLessThanOrEqualOperators:
label2:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
cmp r15, r14
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
comisd xmm15, xmm14
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr GlobalIntY[rip]
cmp r14, r15
setle r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr [rbp - 24]
movsd xmm15, qword ptr GlobalFloatY[rip]
comisd xmm14, xmm15
setbe r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
cmp r15, 20
setle r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 24]
comisd xmm15, qword ptr [rip + _FP2]
setbe r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
cmp r15, r14
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm15, xmm14
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 15
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm14, qword ptr [rip + _FP2]
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4609434218613702656, qword ptr [rip + _FP5]
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label3
label3:
mov rsp, rbp
pop rbp
ret

TestGreaterThanOperators:
label4:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 8]
cmp r15, r14
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 24]
comisd xmm15, xmm14
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r15, qword ptr [rbp - 16]
cmp r14, r15
setg r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm15, qword ptr [rbp - 32]
comisd xmm14, xmm15
seta r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 16]
cmp r15, 5
setg r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 32]
comisd xmm15, qword ptr [rip + _FP0]
seta r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntY[rip]
mov r14, qword ptr GlobalIntX[rip]
cmp r15, r14
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm15, xmm14
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
cmp r14, 10
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm14, qword ptr [rip + _FP1]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4611686018427387904, qword ptr [rip + _FP5]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label5
label5:
mov rsp, rbp
pop rbp
ret

TestGreaterThanOrEqualOperators:
label6:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 8]
cmp r15, r14
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 24]
comisd xmm15, xmm14
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r15, qword ptr [rbp - 16]
cmp r14, r15
setge r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm15, qword ptr [rbp - 32]
comisd xmm14, xmm15
setae r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 16]
cmp r15, 5
setge r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 32]
comisd xmm15, qword ptr [rip + _FP0]
setae r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntY[rip]
mov r14, qword ptr GlobalIntX[rip]
cmp r15, r14
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm15, xmm14
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
cmp r14, 15
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm14, qword ptr [rip + _FP2]
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4611686018427387904, qword ptr [rip + _FP5]
setae r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label7
label7:
mov rsp, rbp
pop rbp
ret

TestEqualOperators:
label8:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
cmp r15, r14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
comisd xmm15, xmm14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr GlobalIntX[rip]
cmp r14, r15
sete r15b
and r15b, 1
cmp r15b, 0
sete r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr [rbp - 24]
movsd xmm15, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm15
sete r15b
and r15b, 1
cmp r15b, 0
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
cmp r15, 5
sete r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 24]
comisd xmm15, qword ptr [rip + _FP0]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntX[rip]
cmp r15, r14
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm15, xmm14
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm14, qword ptr [rip + _FP2]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4609434218613702656, qword ptr [rip + _FP5]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label9
label9:
mov rsp, rbp
pop rbp
ret

TestNotEqualOperators:
label10:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 10
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 24], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 32], xmm15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
cmp r15, r14
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
comisd xmm15, xmm14
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr GlobalIntX[rip]
cmp r14, r15
setne r15b
and r15b, 1
cmp r15b, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr [rbp - 24]
movsd xmm15, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm15
setne r15b
and r15b, 1
cmp r15b, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
cmp r15, 10
setne r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr [rbp - 24]
comisd xmm15, qword ptr [rip + _FP1]
setne r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
cmp r15, r14
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm15, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm15, xmm14
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 20
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm14, qword ptr [rip + _FP6]
setne r14b
and r14b, 1
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
comisd 4609434218613702656, qword ptr [rip + _FP4]
setne r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label11
label11:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label12:
push rbp
mov rbp, rsp
sub rsp, 40
call TestLessThanOperators
call TestLessThanOrEqualOperators
call TestGreaterThanOperators
call TestGreaterThanOrEqualOperators
call TestEqualOperators
call TestNotEqualOperators
mov qword ptr [rbp - 8], 0
jmp label14
label13:
jmp label14
label14:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

