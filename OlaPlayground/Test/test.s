.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4608083138725491507


_FP2:
.quad 4613937818241073152


_FP3:
.quad 4618722892845154304


_FP4:
.quad 4611686018427387904


_FP5:
.quad 4617315517961601024


_FP6:
.quad 4625970873495453696


_FP7:
.quad 4624633867356078080


_FP8:
.quad 4609434218613702656


_FP9:
.quad 4615626668101337088


_FP10:
.quad 4621819117588971520


_FP11:
.quad 4608308318706860032


_FP12:
.quad 4620130267728707584


_FP13:
.quad 4547007122018943789


_FP14:
.quad 4624633811061082738


_FP15:
.quad 4624633923651073422


_FP16:
.quad 4621819061293976178


_FP17:
.quad 4621819173883966862


_FP18:
.quad 4611685568067425167


_FP19:
.quad 4611686243607369273


_FP20:
.quad 4612811693154249159


_FP21:
.quad 4612812143514211897


_FP22:
.quad 4620130155138716900


_FP23:
.quad 4620130380318698268


.section .data

GlobalIntX:
.quad 20


GlobalIntY:
.quad 4


GlobalFloatX:
.quad 4620130267728707584


GlobalFloatY:
.quad 4612811918334230528


.section .text

.extern Assert

.extern AssertMsg

TestMultiplication:
label0:
push rbp
mov rbp, rsp
sub rsp, 208
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
mov qword ptr [rbp - 56], 5
mov qword ptr [rbp - 64], 3
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
mov r14, qword ptr [rbp - 56]
mov r13, qword ptr [rbp - 64]
mov r12, r14
imul r12, r13
mov qword ptr [rbp - 88], r12
mov r12, qword ptr [rbp - 88]
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr [rbp - 80]
movsd xmm12, xmm14
mulsd xmm12, xmm13
movsd qword ptr [rbp - 96], xmm12
movsd xmm12, qword ptr [rbp - 96]
comisd xmm12, qword ptr [rip + _FP2]
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 56]
mov r13, qword ptr GlobalIntY[rip]
mov r14, r12
imul r14, r13
mov qword ptr [rbp - 104], r14
mov r14, qword ptr [rbp - 104]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm12, qword ptr [rbp - 72]
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, xmm12
mulsd xmm14, xmm13
movsd qword ptr [rbp - 112], xmm14
movsd xmm14, qword ptr [rbp - 112]
comisd xmm14, qword ptr [rip + _FP3]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
mov r13, r14
imul r13, 2
mov qword ptr [rbp - 120], r13
mov r13, qword ptr [rbp - 120]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP4]
mulsd xmm13, xmm14
movsd qword ptr [rbp - 128], xmm13
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP5]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
mov r12, r13
imul r12, r14
mov qword ptr [rbp - 136], r12
mov r12, qword ptr [rbp - 136]
cmp r12, 80
sete r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatY[rip]
movsd xmm12, xmm13
mulsd xmm12, xmm14
movsd qword ptr [rbp - 144], xmm12
movsd xmm12, qword ptr [rbp - 144]
comisd xmm12, qword ptr [rip + _FP6]
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr GlobalIntX[rip]
mov r14, r12
imul r14, 2
mov qword ptr [rbp - 152], r14
mov r14, qword ptr [rbp - 152]
cmp r14, 40
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm12, qword ptr GlobalFloatX[rip]
movsd xmm14, xmm12
movsd xmm12, qword ptr [rip + _FP4]
mulsd xmm14, xmm12
movsd qword ptr [rbp - 160], xmm14
movsd xmm14, qword ptr [rbp - 160]
comisd xmm14, qword ptr [rip + _FP7]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r14, qword ptr [rbp - 56]
mov r12, r14
imul r12, 2
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm12, xmm14
movsd xmm14, qword ptr [rip + _FP8]
mulsd xmm12, xmm14
movsd qword ptr [rbp - 72], xmm12
movsd xmm12, qword ptr [rbp - 72]
comisd xmm12, qword ptr [rip + _FP9]
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 168], 2
mov r12, qword ptr [rbp - 168]
mov r14, r12
imul r14, 3
mov qword ptr [rbp - 168], r14
mov r14, qword ptr [rbp - 168]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r12, qword ptr GlobalIntY[rip]
mov r13, r14
imul r13, r12
mov qword ptr GlobalIntX[rip], r13
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 80
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 176], 2
mov r13, qword ptr GlobalIntY[rip]
mov r12, qword ptr [rbp - 176]
mov r14, r13
imul r14, r12
mov qword ptr GlobalIntY[rip], r14
mov r14, qword ptr GlobalIntY[rip]
cmp r14, 8
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr GlobalIntX[rip], 20
mov qword ptr GlobalIntY[rip], 4
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
movsd xmm13, qword ptr [rbp - 40]
movsd xmm12, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestDivision:
label2:
push rbp
mov rbp, rsp
sub rsp, 200
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
movsd qword ptr [rbp - 40], xmm12
mov qword ptr [rbp - 48], 15
mov qword ptr [rbp - 56], 3
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 64], xmm14
movsd xmm14, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 72], xmm14
mov r14, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 56]
mov rax, r14
cqo
idiv r13
mov r13, rax
mov qword ptr [rbp - 80], r13
mov r13, qword ptr [rbp - 80]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr [rbp - 64]
movsd xmm13, qword ptr [rbp - 72]
movsd xmm12, xmm14
divsd xmm12, xmm13
movsd qword ptr [rbp - 88], xmm12
movsd xmm12, qword ptr [rbp - 88]
comisd xmm12, qword ptr [rip + _FP0]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
mov r14, qword ptr GlobalIntY[rip]
mov rax, r13
cqo
idiv r14
mov r14, rax
mov qword ptr [rbp - 96], r14
mov r14, qword ptr [rbp - 96]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm12, qword ptr [rbp - 64]
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, xmm12
divsd xmm14, xmm13
movsd qword ptr [rbp - 104], xmm14
movsd xmm14, qword ptr [rbp - 104]
comisd xmm14, qword ptr [rip + _FP4]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 48]
mov rax, r14
cqo
mov r14, 3
idiv r14
mov r14, rax
mov qword ptr [rbp - 112], r14
mov r14, qword ptr [rbp - 112]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 64]
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP4]
divsd xmm13, xmm14
movsd qword ptr [rbp - 120], xmm13
movsd xmm13, qword ptr [rbp - 120]
comisd xmm13, qword ptr [rip + _FP0]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov rax, r14
cqo
idiv r13
mov r13, rax
mov qword ptr [rbp - 128], r13
mov r13, qword ptr [rbp - 128]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
movsd xmm14, qword ptr GlobalFloatY[rip]
movsd xmm12, xmm13
divsd xmm12, xmm14
movsd qword ptr [rbp - 136], xmm12
movsd xmm12, qword ptr [rbp - 136]
comisd xmm12, qword ptr [rip + _FP2]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
mov rax, r13
cqo
mov r13, 5
idiv r13
mov r13, rax
mov qword ptr [rbp - 144], r13
mov r13, qword ptr [rbp - 144]
cmp r13, 4
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm12, qword ptr GlobalFloatX[rip]
movsd xmm14, xmm12
movsd xmm12, qword ptr [rip + _FP0]
divsd xmm14, xmm12
movsd qword ptr [rbp - 152], xmm14
movsd xmm14, qword ptr [rbp - 152]
comisd xmm14, qword ptr [rip + _FP2]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 48]
mov rax, r13
cqo
mov r13, 2
idiv r13
mov r13, rax
mov qword ptr [rbp - 48], r13
mov r13, qword ptr [rbp - 48]
cmp r13, 7
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr [rbp - 64]
movsd xmm12, xmm14
movsd xmm14, qword ptr [rip + _FP4]
divsd xmm12, xmm14
movsd qword ptr [rbp - 64], xmm12
movsd xmm12, qword ptr [rbp - 64]
comisd xmm12, qword ptr [rip + _FP0]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm12, qword ptr [rip + _FP10]
movsd qword ptr [rbp - 160], xmm12
movsd xmm12, qword ptr [rbp - 160]
movsd xmm14, xmm12
movsd xmm12, qword ptr [rip + _FP4]
divsd xmm14, xmm12
movsd qword ptr [rbp - 160], xmm14
movsd xmm14, qword ptr [rbp - 160]
comisd xmm14, qword ptr [rip + _FP5]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm12, qword ptr GlobalFloatY[rip]
movsd xmm13, xmm14
divsd xmm13, xmm12
movsd qword ptr GlobalFloatX[rip], xmm13
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP2]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 168], xmm13
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm12, qword ptr [rbp - 168]
movsd xmm14, xmm13
divsd xmm14, xmm12
movsd qword ptr GlobalFloatY[rip], xmm14
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm14, qword ptr [rip + _FP11]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr [rip + _FP12]
movsd qword ptr GlobalFloatX[rip], xmm14
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr GlobalFloatY[rip], xmm14
jmp label3
label3:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
movsd xmm12, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestModulo:
label4:
push rbp
mov rbp, rsp
sub rsp, 104
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 17
mov qword ptr [rbp - 32], 4
mov r14, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov rax, r14
cqo
idiv r13
mov r13, rdx
mov qword ptr [rbp - 40], r13
mov r13, qword ptr [rbp - 40]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 24]
mov r14, qword ptr GlobalIntY[rip]
mov rax, r13
cqo
idiv r14
mov r14, rdx
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 48]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 24]
mov rax, r14
cqo
mov r14, 3
idiv r14
mov r14, rdx
mov qword ptr [rbp - 56], r14
mov r14, qword ptr [rbp - 56]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov rax, r14
cqo
idiv r13
mov r13, rdx
mov qword ptr [rbp - 64], r13
mov r13, qword ptr [rbp - 64]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
mov rax, r13
cqo
mov r13, 3
idiv r13
mov r13, rdx
mov qword ptr [rbp - 72], r13
mov r13, qword ptr [rbp - 72]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov rax, 10
cqo
mov r13, 3
idiv r13
mov r13, rdx
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 24]
mov rax, r13
cqo
mov r13, 3
idiv r13
mov r13, rdx
mov qword ptr [rbp - 24], r13
mov r13, qword ptr [rbp - 24]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestMixedTypeMultiplicationAndDivision:
label6:
push rbp
mov rbp, rsp
sub rsp, 168
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd xmm14, qword ptr [rip + _FP13]
movsd qword ptr [rbp - 56], xmm14
mov qword ptr [rbp - 64], 2
mov r14, qword ptr [rbp - 64]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr GlobalFloatX[rip]
movsd xmm12, xmm14
mulsd xmm12, xmm13
movsd qword ptr [rbp - 72], xmm12
movsd xmm12, qword ptr [rbp - 72]
comisd xmm12, qword ptr [rip + _FP14]
seta r14b
and r14b, 1
movsd xmm12, qword ptr [rbp - 72]
comisd xmm12, qword ptr [rip + _FP15]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm12, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 80], xmm12
mov r12, qword ptr GlobalIntY[rip]
cvtsi2sd xmm12, r12
movsd xmm13, qword ptr [rbp - 80]
movsd xmm14, xmm13
mulsd xmm14, xmm12
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rbp - 88]
comisd xmm14, qword ptr [rip + _FP16]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 88]
comisd xmm14, qword ptr [rip + _FP17]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 96], 5
mov r14, qword ptr [rbp - 96]
cvtsi2sd xmm14, r14
movsd xmm12, qword ptr GlobalFloatY[rip]
movsd xmm13, xmm14
divsd xmm13, xmm12
movsd qword ptr [rbp - 104], xmm13
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP18]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP19]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm13, qword ptr [rip + _FP10]
movsd qword ptr [rbp - 112], xmm13
mov r12, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r12
movsd xmm12, qword ptr [rbp - 112]
movsd xmm14, xmm12
divsd xmm14, xmm13
movsd qword ptr [rbp - 120], xmm14
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP20]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP21]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 128], 2
mov r14, qword ptr [rbp - 128]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr GlobalFloatX[rip]
movsd xmm12, xmm14
mulsd xmm12, xmm13
cvttsd2si r14, xmm12
mov qword ptr [rbp - 128], r14
mov r14, qword ptr [rbp - 128]
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm12, qword ptr [rip + _FP7]
movsd qword ptr [rbp - 136], xmm12
mov r14, qword ptr [rbp - 64]
cvtsi2sd xmm12, r14
movsd xmm13, qword ptr [rbp - 136]
movsd xmm14, xmm13
divsd xmm14, xmm12
movsd qword ptr [rbp - 136], xmm14
movsd xmm14, qword ptr [rbp - 136]
comisd xmm14, qword ptr [rip + _FP22]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rbp - 136]
comisd xmm14, qword ptr [rip + _FP23]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label7
label7:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
movsd xmm13, qword ptr [rbp - 40]
movsd xmm12, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label8:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestMultiplication
call TestDivision
call TestModulo
call TestMixedTypeMultiplicationAndDivision
mov qword ptr [rbp - 16], 0
jmp label10
label9:
label10:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
