.intel_syntax noprefix

.section .rodata

global_int_1:
.quad 5


global_int_2:
.quad 10


global_int_3:
.quad 7


global_float_1:
.quad 4615063718147915776


global_float_2:
.quad 4612811918334230528


global_float_3:
.quad 4608083138725491507


_FP0:
.quad 4620974636363844210


_FP1:
.quad 4620974748953834894


_INT0:
.quad 5


_FP2:
.quad 4620130155138716900


_FP3:
.quad 4620130380318698268


_FP4:
.quad 4612811918334230528


_FP5:
.quad 4623226436177529458


_FP6:
.quad 4623226548767520142


_INT1:
.quad 10


_FP7:
.quad 4622494601238081752


_FP8:
.quad 4622494713828072437


_FP9:
.quad 4615063718147915776


_FP10:
.quad 4622100536270686834


_FP11:
.quad 4622100648860677518


_FP12:
.quad 4609434218613702656


_FP13:
.quad 4619004255231874276


_FP14:
.quad 4619004480411855644


_FP15:
.quad 4623789386130950770


_FP16:
.quad 4623789498720941454


.data

global_composite_mix_add_int:
.quad 5


global_composite_mix_add_float:
.quad 4615063718147915776


.text

.extern Assert

.extern AssertMsg

TestMixedTypeAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
movsd qword ptr [rbp - 40], xmm14
movsd qword ptr [rbp - 48], xmm13
movsd qword ptr [rbp - 56], xmm12
movsd qword ptr [rbp - 64], xmm11
lea r14, [rip + global_int_1]
mov r13, qword ptr [r14]
lea r14, [rip + global_float_1]
movsd xmm14, qword ptr [r14]
cvtsi2sd xmm13, r13
movsd xmm12, xmm13
addsd xmm12, xmm14
comisd xmm12, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
comisd xmm12, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r12b, r13b
and r12b, r14b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
cvtsi2sd xmm12, qword ptr [rip + _INT0]
lea r12, [rip + global_float_2]
movsd xmm14, qword ptr [r12]
movsd xmm13, xmm12
addsd xmm13, xmm14
comisd xmm13, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
comisd xmm13, qword ptr [rip + _FP3]
setb r14b
and r14b, 1
mov r13b, r12b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + global_int_2]
mov r14, qword ptr [r13]
cvtsi2sd xmm13, r14
movsd xmm14, xmm13
movsd xmm13, qword ptr [rip + _FP4]
addsd xmm14, xmm13
comisd xmm14, qword ptr [rip + _FP5]
seta r14b
and r14b, 1
comisd xmm14, qword ptr [rip + _FP6]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, [rip + global_float_3]
movsd xmm14, qword ptr [r12]
cvtsi2sd xmm13, qword ptr [rip + _INT1]
movsd xmm11, xmm13
addsd xmm11, xmm14
comisd xmm11, qword ptr [rip + _FP7]
seta r12b
and r12b, 1
comisd xmm11, qword ptr [rip + _FP8]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + global_int_3]
mov r13, qword ptr [r14]
cvtsi2sd xmm11, r13
movsd xmm14, xmm11
movsd xmm11, qword ptr [rip + _FP9]
addsd xmm14, xmm11
comisd xmm14, qword ptr [rip + _FP10]
seta r13b
and r13b, 1
comisd xmm14, qword ptr [rip + _FP11]
setb r14b
and r14b, 1
mov r12b, r13b
and r12b, r14b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm14, xmm12
movsd xmm11, qword ptr [rip + _FP12]
addsd xmm14, xmm11
comisd xmm14, qword ptr [rip + _FP13]
seta r12b
and r12b, 1
comisd xmm14, qword ptr [rip + _FP14]
setb r14b
and r14b, 1
mov r13b, r12b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm14, xmm12
movsd xmm11, qword ptr [rip + _FP9]
addsd xmm14, xmm11
comisd xmm14, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
comisd xmm14, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r12b, r13b
and r12b, r14b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
movsd xmm14, xmm12
movsd xmm11, qword ptr [rip + _FP4]
addsd xmm14, xmm11
cvttsd2si r12, xmm14
cmp r12, 7
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, [rip + global_composite_mix_add_float]
movsd xmm14, qword ptr [r12]
lea r12, [rip + global_composite_mix_add_float]
movsd xmm11, xmm14
addsd xmm11, xmm12
movsd qword ptr [r12], xmm11
lea r12, [rip + global_composite_mix_add_float]
movsd xmm11, qword ptr [r12]
comisd xmm11, qword ptr [rip + _FP0]
seta r12b
and r12b, 1
comisd xmm11, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r13b, r12b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + global_composite_mix_add_int]
mov r14, qword ptr [r13]
lea r13, [rip + global_composite_mix_add_int]
cvtsi2sd xmm14, r14
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP4]
addsd xmm13, xmm14
cvttsd2si r14, xmm13
mov qword ptr [r13], r14
lea r14, [rip + global_composite_mix_add_int]
mov r13, qword ptr [r14]
cmp r13, 7
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + global_composite_mix_add_float]
movsd xmm13, xmm11
addsd xmm13, xmm12
movsd qword ptr [r14], xmm13
lea r14, [rip + global_composite_mix_add_float]
movsd xmm13, qword ptr [r14]
comisd xmm13, qword ptr [rip + _FP15]
seta r14b
and r14b, 1
comisd xmm13, qword ptr [rip + _FP16]
setb r12b
and r12b, 1
mov dil, r14b
and dil, r12b
cmp dil, 0
setne dil
and dil, 1
mov cl, dil
call Assert
lea rdi, [rip + global_composite_mix_add_int]
cvtsi2sd xmm13, r13
movsd xmm12, xmm13
movsd xmm13, qword ptr [rip + _FP4]
addsd xmm12, xmm13
cvttsd2si r13, xmm12
mov qword ptr [rdi], r13
lea r13, [rip + global_composite_mix_add_int]
mov rdi, qword ptr [r13]
cmp rdi, 9
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 40]
movsd xmm13, qword ptr [rbp - 48]
movsd xmm12, qword ptr [rbp - 56]
movsd xmm11, qword ptr [rbp - 64]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 32
call TestMixedTypeAddition
jmp label3
label3:
mov rax, 0
mov rsp, rbp
pop rbp
ret
