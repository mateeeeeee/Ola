.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4612811918334230528


_FP1:
.quad 4617315517961601024


_FP2:
.quad 4625619029774565376


_FP3:
.quad 4626322717216342016


_FP4:
.quad 4620130267728707584


_FP5:
.quad 4621819117588971520


_FP6:
.quad 4624633867356078080


_INT0:
.quad 5


_INT1:
.quad 10


_INT2:
.quad 12


_INT3:
.quad 4


_FP7:
.quad 4615063718147915776


_FP8:
.quad 4617878467915022336


_FP9:
.quad 4626041242239631360


_FP10:
.quad 4627730092099895296


_INT4:
.quad 30


_FP11:
.quad 4628433779541671936


_INT5:
.quad 15


_FP12:
.quad 4616752568008179712


_INT6:
.quad 6


_INT7:
.quad 3


_INT8:
.quad 8


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
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
cmp r14, r13
setl r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
mov r14, qword ptr [rbp - 64]
cmp r13, r14
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm14, xmm13
setb r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 88]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setl r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
setb r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 80]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 56]
cmp r14, r13
setl r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 64]
cmp r13, r14
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 88]
comisd xmm14, xmm13
setb r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 48]
cmp r14, 20
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP4]
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 15
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP5]
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
cmp r14, r13
setl r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm14, xmm13
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 30
setl r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP6]
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 5
setge r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, qword ptr [rip + _FP4]
setae r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr [rbp - 96]
comisd xmm14, xmm13
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, xmm13
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
setb r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP0]
setae r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT2]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
setae r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT3]
comisd xmm13, qword ptr [rip + _FP7]
setae r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
comisd xmm13, qword ptr [rip + _FP8]
setb r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestLessThanOrEqualOperators:
label2:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
cmp r14, r13
setle r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
mov r14, qword ptr [rbp - 64]
cmp r13, r14
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm14, xmm13
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 88]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setle r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 80]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 56]
cmp r14, r13
setle r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 64]
cmp r13, r14
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 88]
comisd xmm14, xmm13
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 48]
cmp r14, 20
setle r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 25
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP4]
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP3]
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 15
setg r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 64]
cmp r14, 29
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP5]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP9]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
cmp r14, r13
setle r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm14, xmm13
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 30
setle r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP6]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 5
setg r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, qword ptr [rip + _FP4]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr [rbp - 96]
comisd xmm14, xmm13
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, xmm13
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP3]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT2]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT3]
comisd xmm13, qword ptr [rip + _FP7]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
comisd xmm13, qword ptr [rip + _FP8]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label3
label3:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestGreaterThanOperators:
label4:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
setg r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
mov r14, qword ptr [rbp - 56]
cmp r13, r14
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
seta r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 96]
movsd xmm14, qword ptr [rbp - 88]
comisd xmm13, xmm14
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setg r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 88]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
seta r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 96]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
setg r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 48]
cmp r13, r14
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
seta r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 80]
comisd xmm13, xmm14
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 64]
cmp r14, 20
setg r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP4]
seta r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 30
setle r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP10]
setbe r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setg r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatY[rip]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cmp r13, 10
setg r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, qword ptr [rip + _FP1]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 20
setle r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP6]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 64]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, xmm13
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT4]
movsd xmm14, qword ptr [rbp - 72]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr [rbp - 96]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP11]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT5]
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT0]
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
seta r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP6]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT3]
comisd xmm13, qword ptr [rip + _FP12]
setbe r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT6]
comisd xmm13, qword ptr [rip + _FP8]
seta r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestGreaterThanOrEqualOperators:
label6:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
setge r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
mov r14, qword ptr [rbp - 56]
cmp r13, r14
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
setae r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 96]
movsd xmm14, qword ptr [rbp - 88]
comisd xmm13, xmm14
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setge r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 88]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
setae r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 96]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
setge r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 48]
cmp r13, r14
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
setae r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 80]
comisd xmm13, xmm14
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 64]
cmp r14, 20
setge r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP4]
setae r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 30
setl r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP10]
setb r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setge r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatY[rip]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
setae r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cmp r13, 10
setge r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, qword ptr [rip + _FP1]
setae r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 20
setl r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP6]
setb r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
jmp label8
label7:
label8:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestEqualOperators:
label9:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
mov r14, qword ptr [rbp - 56]
cmp r13, r14
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 96]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 80]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 48]
cmp r13, r14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 80]
comisd xmm13, xmm14
sete r14b
and r14b, 1
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, qword ptr [rip + _FP0]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 25
sete r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP3]
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP4]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP4]
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr [rbp - 80]
comisd xmm14, xmm13
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, xmm13
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP1]
sete r13b
and r13b, 1
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
movsd xmm14, qword ptr [rbp - 80]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT7]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP0]
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP6]
sete r13b
and r13b, 1
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT2]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT8]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT3]
comisd xmm13, qword ptr [rip + _FP7]
sete r13b
and r13b, 1
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
comisd xmm13, qword ptr [rip + _FP1]
sete r13b
and r13b, 1
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label10
label10:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestNotEqualOperators:
label11:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
movsd qword ptr [rbp - 32], xmm13
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov qword ptr [rbp - 56], 25
mov qword ptr [rbp - 64], 30
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 72], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP2]
movsd qword ptr [rbp - 88], xmm14
movsd xmm14, qword ptr [rip + _FP3]
movsd qword ptr [rbp - 96], xmm14
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
cmp r14, r13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
mov r14, qword ptr [rbp - 64]
cmp r13, r14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm14, xmm13
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 88]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr GlobalIntX[rip]
cmp r14, r13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 48]
mov r14, qword ptr GlobalIntY[rip]
cmp r13, r14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm14, xmm13
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [rbp - 80]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
cmp r14, r13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, qword ptr [rbp - 48]
cmp r13, r14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr [rbp - 72]
comisd xmm14, xmm13
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
movsd xmm14, qword ptr [rbp - 80]
comisd xmm13, xmm14
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
cmp r14, 10
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, qword ptr [rip + _FP1]
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 56]
cmp r14, 30
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, qword ptr [rip + _FP10]
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
cmp r14, r13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, qword ptr GlobalFloatX[rip]
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm14, xmm13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 20
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, qword ptr [rip + _FP5]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 10
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr GlobalFloatY[rip]
comisd xmm13, qword ptr [rip + _FP1]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr [rbp - 96]
comisd xmm14, xmm13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
cvtsi2sd xmm13, r13
movsd xmm14, qword ptr [rbp - 72]
comisd xmm14, xmm13
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 64]
cvtsi2sd xmm14, r13
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
movsd xmm14, qword ptr [rbp - 96]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 56]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP0]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP3]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT2]
movsd xmm14, qword ptr GlobalFloatY[rip]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm14, qword ptr [rip + _INT1]
movsd xmm13, qword ptr GlobalFloatX[rip]
comisd xmm13, xmm14
setne r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
cvtsi2sd xmm13, r13
comisd xmm13, qword ptr [rip + _FP4]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT3]
comisd xmm13, qword ptr [rip + _FP7]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
comisd xmm13, qword ptr [rip + _FP8]
setne r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label12
label12:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label13:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestLessThanOperators
call TestLessThanOrEqualOperators
call TestGreaterThanOperators
call TestGreaterThanOrEqualOperators
call TestEqualOperators
call TestNotEqualOperators
mov qword ptr [rbp - 16], 0
jmp label15
label14:
label15:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
