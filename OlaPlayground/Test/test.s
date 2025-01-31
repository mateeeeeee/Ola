.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4547007122018943789


_FP1:
.quad 4620974636363844210


_FP2:
.quad 4620974748953834894


_FP3:
.quad 4620130155138716900


_FP4:
.quad 4620130380318698268


_FP5:
.quad 4612811918334230528


_FP6:
.quad 4623226436177529458


_FP7:
.quad 4623226548767520142


_INT0:
.quad 10


_FP8:
.quad 4622494601238081752


_FP9:
.quad 4622494713828072437


_FP10:
.quad 4615063718147915776


_FP11:
.quad 4622100536270686834


_FP12:
.quad 4622100648860677518


_FP13:
.quad 4609434218613702656


_FP14:
.quad 4619004255231874276


_FP15:
.quad 4619004480411855644


_FP16:
.quad 4611686243607369273


_FP17:
.quad -9223372036854775808


_FP18:
.quad 4611685568067425167


_FP19:
.quad 4617315517961601024


_FP20:
.quad 4617315630551591708


_FP21:
.quad 4617315405371610340


_FP22:
.quad 4602679719892572386


_FP23:
.quad 4602677017732795964


_FP24:
.quad 4620130267728707584


_FP25:
.quad 4612811693154249159


_FP26:
.quad 4612812143514211897


_INT1:
.quad 2


_FP27:
.quad 4609433768253739919


_FP28:
.quad 4609434668973665393


_FP29:
.quad 4613937593061091783


_FP30:
.quad 4613938043421054521


.section .data

global_int_1:
.quad 5


global_int_2:
.quad 10


global_int_3:
.quad 7


global_int_4:
.quad 20


global_sub_1:
.quad 15


global_sub_2:
.quad 7


global_sub_3:
.quad 3


global_sub_4:
.quad 30


global_float_1:
.quad 4615063718147915776


global_float_2:
.quad 4612811918334230528


global_float_3:
.quad 4608083138725491507


global_float_4:
.quad 4617315517961601024


.section .text

.extern Assert

.extern AssertMsg

TestMixedTypeAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm14
mov r14, qword ptr global_int_1[rip]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr global_float_1[rip]
movsd xmm12, xmm14
addsd xmm12, xmm13
movsd qword ptr [rbp - 64], xmm12
movsd xmm12, qword ptr [rbp - 64]
comisd xmm12, qword ptr [rip + _FP1]
seta r14b
and r14b, 1
movsd xmm12, qword ptr [rbp - 64]
comisd xmm12, qword ptr [rip + _FP2]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 72], 5
mov r12, qword ptr [rbp - 72]
cvtsi2sd xmm12, r12
movsd xmm13, qword ptr global_float_2[rip]
movsd xmm14, xmm12
addsd xmm14, xmm13
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP3]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, qword ptr [rip + _FP4]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 88], xmm14
mov r14, qword ptr global_int_2[rip]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr [rbp - 88]
movsd xmm12, xmm14
addsd xmm12, xmm13
movsd qword ptr [rbp - 96], xmm12
movsd xmm12, qword ptr [rbp - 96]
comisd xmm12, qword ptr [rip + _FP6]
seta r14b
and r14b, 1
movsd xmm12, qword ptr [rbp - 96]
comisd xmm12, qword ptr [rip + _FP7]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
cvtsi2sd xmm12, qword ptr [rip + _INT0]
movsd xmm13, qword ptr global_float_3[rip]
movsd xmm14, xmm12
addsd xmm14, xmm13
movsd qword ptr [rbp - 104], xmm14
movsd xmm14, qword ptr [rbp - 104]
comisd xmm14, qword ptr [rip + _FP8]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 104]
comisd xmm14, qword ptr [rip + _FP9]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_int_3[rip]
cvtsi2sd xmm14, r14
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP10]
addsd xmm13, xmm14
movsd qword ptr [rbp - 112], xmm13
movsd xmm13, qword ptr [rbp - 112]
comisd xmm13, qword ptr [rip + _FP11]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 112]
comisd xmm13, qword ptr [rip + _FP12]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 72]
cvtsi2sd xmm13, r12
movsd xmm14, xmm13
movsd xmm13, qword ptr [rip + _FP13]
addsd xmm14, xmm13
movsd qword ptr [rbp - 120], xmm14
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP14]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP15]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
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
TestMixedTypeSubtraction:
label2:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm14
mov r14, qword ptr global_int_3[rip]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr global_float_4[rip]
movsd xmm12, xmm13
subsd xmm12, xmm14
movsd qword ptr [rbp - 64], xmm12
movsd xmm12, qword ptr [rip + _FP16]
movsd xmm14, qword ptr [rip + _FP17]
xorpd xmm12, xmm14
movsd xmm14, qword ptr [rbp - 64]
comisd xmm14, xmm12
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rip + _FP18]
movsd xmm12, qword ptr [rip + _FP17]
xorpd xmm14, xmm12
movsd xmm12, qword ptr [rbp - 64]
comisd xmm12, xmm14
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm12, qword ptr [rip + _FP19]
movsd qword ptr [rbp - 72], xmm12
mov r12, qword ptr global_int_2[rip]
cvtsi2sd xmm12, r12
movsd xmm14, qword ptr [rbp - 72]
movsd xmm13, xmm14
subsd xmm13, xmm12
movsd qword ptr [rbp - 80], xmm13
movsd xmm13, qword ptr [rip + _FP20]
movsd xmm12, qword ptr [rip + _FP17]
xorpd xmm13, xmm12
movsd xmm12, qword ptr [rbp - 80]
comisd xmm12, xmm13
seta r12b
and r12b, 1
movsd xmm12, qword ptr [rip + _FP21]
movsd xmm13, qword ptr [rip + _FP17]
xorpd xmm12, xmm13
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, xmm12
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 88], 3
mov r14, qword ptr [rbp - 88]
cvtsi2sd xmm13, r14
movsd xmm12, qword ptr global_float_2[rip]
movsd xmm14, xmm12
subsd xmm14, xmm13
movsd qword ptr [rbp - 96], xmm14
movsd xmm14, qword ptr [rip + _FP22]
movsd xmm13, qword ptr [rip + _FP17]
xorpd xmm14, xmm13
movsd xmm13, qword ptr [rbp - 96]
comisd xmm13, xmm14
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rip + _FP23]
movsd xmm14, qword ptr [rip + _FP17]
xorpd xmm13, xmm14
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, xmm13
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr global_int_1[rip]
cvtsi2sd xmm14, r12
movsd xmm13, qword ptr [rip + _FP24]
subsd xmm13, xmm14
movsd qword ptr [rbp - 104], xmm13
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP25]
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP26]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
cvtsi2sd xmm13, qword ptr [rip + _INT1]
movsd xmm14, qword ptr global_float_1[rip]
movsd xmm12, xmm14
subsd xmm12, xmm13
movsd qword ptr [rbp - 112], xmm12
movsd xmm12, qword ptr [rbp - 112]
comisd xmm12, qword ptr [rip + _FP27]
seta r14b
and r14b, 1
movsd xmm12, qword ptr [rbp - 112]
comisd xmm12, qword ptr [rip + _FP28]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
cvtsi2sd xmm12, qword ptr [rip + _INT1]
movsd xmm13, qword ptr [rbp - 72]
movsd xmm14, xmm13
subsd xmm14, xmm12
movsd qword ptr [rbp - 120], xmm14
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP29]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP30]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label3
label3:
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
label4:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestMixedTypeAddition
call TestMixedTypeSubtraction
mov qword ptr [rbp - 16], 0
jmp label6
label5:
label6:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
