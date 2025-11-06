.intel_syntax noprefix

.section __TEXT,__const

_FP0:
.quad 4547007122018943789


_FP1:
.quad 4618441417868443648


_FP2:
.quad 4618441305278452964


_FP3:
.quad 4618441530458434332


_FP4:
.quad 4615063718147915776


_FP5:
.quad 4612811918334230528


_FP6:
.quad 4616977635399557553


_FP7:
.quad 4616977860579538921


_FP8:
.quad 4620974636363844210


_FP9:
.quad 4620974748953834894


_FP10:
.quad 4612811693154249159


_FP11:
.quad 4612812143514211897


_FP12:
.quad 4617315517961601024


_FP13:
.quad 4615739032912039982


_FP14:
.quad 4615739483272002719


_FP15:
.quad -9223372036854775808


_FP16:
.quad 4620130155138716900


_FP17:
.quad 4620130380318698268


_FP18:
.quad 4623226436177529458


_FP19:
.quad 4623226548767520142


_INT0:
.quad 10


_FP20:
.quad 4622494601238081752


_FP21:
.quad 4622494713828072437


_FP22:
.quad 4622100536270686834


_FP23:
.quad 4622100648860677518


_FP24:
.quad 4609434218613702656


_FP25:
.quad 4619004255231874276


_FP26:
.quad 4619004480411855644


_INT1:
.quad 5


_FP27:
.quad 4623789386130950770


_FP28:
.quad 4623789498720941454


_FP29:
.quad 4611686243607369273


_FP30:
.quad 4611685568067425167


_FP31:
.quad 4617315630551591708


_FP32:
.quad 4617315405371610340


_FP33:
.quad 4602679719892572386


_FP34:
.quad 4602677017732795964


_FP35:
.quad 4620130267728707584


_INT2:
.quad 2


_FP36:
.quad 4609433768253739919


_FP37:
.quad 4609434668973665393


_FP38:
.quad 4613937593061091783


_FP39:
.quad 4613938043421054521


_INT3:
.quad 3


.data

_global_int_1:
.quad 5


_global_int_2:
.quad 10


_global_int_3:
.quad 7


_global_int_4:
.quad 20


_global_sub_1:
.quad 15


_global_sub_2:
.quad 7


_global_sub_3:
.quad 3


_global_sub_4:
.quad 30


_global_float_1:
.quad 4615063718147915776


_global_float_2:
.quad 4612811918334230528


_global_float_3:
.quad 4608083138725491507


_global_float_4:
.quad 4617315517961601024


_global_composite_add_a:
.quad 5


_global_composite_add_b:
.quad 10


_global_composite_sub_a:
.quad 15


_global_composite_sub_b:
.quad 7


_global_composite_fadd_a:
.quad 4615063718147915776


_global_composite_fadd_b:
.quad 4612811918334230528


_global_composite_fsub_a:
.quad 4617315517961601024


_global_composite_fsub_b:
.quad 4612811918334230528


_global_composite_mix_add_int:
.quad 5


_global_composite_mix_add_float:
.quad 4615063718147915776


_global_composite_mix_sub_int:
.quad 15


_global_composite_mix_sub_float:
.quad 4617315517961601024


.text

.extern _Assert

.extern _AssertMsg

_TestIntAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
mov qword ptr [rbp - 32], 15
mov r14, qword ptr [rbp - 32]
cmp r14, 15
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 10
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 15
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_int_1[rip]
mov r13, qword ptr _global_int_2[rip]
mov r14, r12
add r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 15
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov r14, qword ptr _global_int_1[rip]
mov r13, qword ptr [rbp - 48]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 72], r12
mov r12, qword ptr [rbp - 72]
cmp r12, 15
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr [rbp - 40]
mov r13, qword ptr _global_int_3[rip]
mov r14, r12
add r14, r13
mov qword ptr [rbp - 80], r14
mov r14, qword ptr [rbp - 80]
cmp r14, 12
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 88], 5
mov r14, qword ptr [rbp - 88]
mov r13, r14
add r13, 10
mov qword ptr [rbp - 88], r13
mov r13, qword ptr [rbp - 88]
cmp r13, 15
sete r13b
and r13b, 1
mov dil, r13b
call _Assert
mov qword ptr [rbp - 96], 5
mov qword ptr [rbp - 104], 10
mov r13, qword ptr [rbp - 96]
mov r14, qword ptr [rbp - 104]
mov r12, r13
add r12, r14
mov qword ptr [rbp - 96], r12
mov r12, qword ptr [rbp - 96]
cmp r12, 15
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_composite_add_a[rip]
mov r14, qword ptr _global_composite_add_b[rip]
mov r13, r12
add r13, r14
mov qword ptr _global_composite_add_a[rip], r13
mov r13, qword ptr _global_composite_add_a[rip]
cmp r13, 15
sete r13b
and r13b, 1
mov dil, r13b
call _Assert
mov r13, qword ptr _global_composite_add_b[rip]
mov r14, r13
add r14, 5
mov qword ptr _global_composite_add_b[rip], r14
mov r14, qword ptr _global_composite_add_b[rip]
cmp r14, 15
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 112], 5
mov r14, qword ptr _global_composite_add_a[rip]
mov r13, qword ptr [rbp - 112]
mov r12, r14
add r12, r13
mov qword ptr _global_composite_add_a[rip], r12
mov r12, qword ptr _global_composite_add_a[rip]
cmp r12, 20
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
jmp label1
label1:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
_TestIntSubtraction:
label2:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
mov qword ptr [rbp - 32], 8
mov r14, qword ptr [rbp - 32]
cmp r14, 8
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 40], 15
mov qword ptr [rbp - 48], 7
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
sub r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 8
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_sub_1[rip]
mov r13, qword ptr _global_sub_2[rip]
mov r14, r12
sub r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 8
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov r14, qword ptr _global_sub_4[rip]
mov r13, qword ptr [rbp - 48]
mov r12, r14
sub r12, r13
mov qword ptr [rbp - 72], r12
mov r12, qword ptr [rbp - 72]
cmp r12, 23
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr [rbp - 40]
mov r13, qword ptr _global_sub_3[rip]
mov r14, r12
sub r14, r13
mov qword ptr [rbp - 80], r14
mov r14, qword ptr [rbp - 80]
cmp r14, 12
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 88], 15
mov r14, qword ptr [rbp - 88]
mov r13, r14
sub r13, 7
mov qword ptr [rbp - 88], r13
mov r13, qword ptr [rbp - 88]
cmp r13, 8
sete r13b
and r13b, 1
mov dil, r13b
call _Assert
mov qword ptr [rbp - 96], 15
mov qword ptr [rbp - 104], 7
mov r13, qword ptr [rbp - 96]
mov r14, qword ptr [rbp - 104]
mov r12, r13
sub r12, r14
mov qword ptr [rbp - 96], r12
mov r12, qword ptr [rbp - 96]
cmp r12, 8
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_composite_sub_a[rip]
mov r14, qword ptr _global_composite_sub_b[rip]
mov r13, r12
sub r13, r14
mov qword ptr _global_composite_sub_a[rip], r13
mov r13, qword ptr _global_composite_sub_a[rip]
cmp r13, 8
sete r13b
and r13b, 1
mov dil, r13b
call _Assert
mov r13, qword ptr _global_composite_sub_b[rip]
mov r14, r13
sub r14, 7
mov qword ptr _global_composite_sub_b[rip], r14
mov r14, qword ptr _global_composite_sub_b[rip]
cmp r14, 0
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 112], 7
mov r14, qword ptr _global_composite_sub_a[rip]
mov r13, qword ptr [rbp - 112]
mov r12, r14
sub r12, r13
mov qword ptr _global_composite_sub_a[rip], r12
mov r12, qword ptr _global_composite_sub_a[rip]
cmp r12, 1
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
jmp label3
label3:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
_TestFloatAddition:
label4:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
movsd qword ptr [rbp - 32], xmm13
movsd qword ptr [rbp - 40], xmm14
movsd qword ptr [rbp - 48], xmm15
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm15
movsd xmm15, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 64], xmm15
movsd xmm15, qword ptr [rbp - 64]
comisd xmm15, qword ptr [rip + _FP2]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 64]
comisd xmm15, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 72], xmm15
movsd xmm15, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 80], xmm15
movsd xmm15, qword ptr [rbp - 72]
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, xmm15
addsd xmm13, xmm14
movsd qword ptr [rbp - 88], xmm13
movsd xmm13, qword ptr [rbp - 88]
comisd xmm13, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rbp - 88]
comisd xmm13, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm13, qword ptr _global_float_1[rip]
movsd xmm14, qword ptr _global_float_2[rip]
movsd xmm15, xmm13
addsd xmm15, xmm14
movsd qword ptr [rbp - 96], xmm15
movsd xmm15, qword ptr [rbp - 96]
comisd xmm15, qword ptr [rip + _FP2]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 96]
comisd xmm15, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr _global_float_1[rip]
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, xmm15
addsd xmm13, xmm14
movsd qword ptr [rbp - 104], xmm13
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm13, qword ptr [rbp - 72]
movsd xmm14, qword ptr _global_float_3[rip]
movsd xmm15, xmm13
addsd xmm15, xmm14
movsd qword ptr [rbp - 112], xmm15
movsd xmm15, qword ptr [rbp - 112]
comisd xmm15, qword ptr [rip + _FP6]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 112]
comisd xmm15, qword ptr [rip + _FP7]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 120], xmm15
movsd xmm15, qword ptr [rbp - 120]
movsd xmm14, xmm15
movsd xmm15, qword ptr [rip + _FP5]
addsd xmm14, xmm15
movsd qword ptr [rbp - 120], xmm14
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm14, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 128], xmm14
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 136], xmm14
movsd xmm14, qword ptr [rbp - 128]
movsd xmm15, qword ptr [rbp - 136]
movsd xmm13, xmm14
addsd xmm13, xmm15
movsd qword ptr [rbp - 128], xmm13
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP2]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm13, qword ptr _global_composite_fadd_a[rip]
movsd xmm15, qword ptr _global_composite_fadd_b[rip]
movsd xmm14, xmm13
addsd xmm14, xmm15
movsd qword ptr _global_composite_fadd_a[rip], xmm14
movsd xmm14, qword ptr _global_composite_fadd_a[rip]
comisd xmm14, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
movsd xmm14, qword ptr _global_composite_fadd_a[rip]
comisd xmm14, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm14, qword ptr _global_composite_fadd_b[rip]
movsd xmm15, xmm14
movsd xmm14, qword ptr [rip + _FP4]
addsd xmm15, xmm14
movsd qword ptr _global_composite_fadd_b[rip], xmm15
movsd xmm15, qword ptr _global_composite_fadd_b[rip]
comisd xmm15, qword ptr [rip + _FP2]
seta r14b
and r14b, 1
movsd xmm15, qword ptr _global_composite_fadd_b[rip]
comisd xmm15, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 144], xmm15
movsd xmm15, qword ptr _global_composite_fadd_a[rip]
movsd xmm14, qword ptr [rbp - 144]
movsd xmm13, xmm15
addsd xmm13, xmm14
movsd qword ptr _global_composite_fadd_a[rip], xmm13
movsd xmm13, qword ptr _global_composite_fadd_a[rip]
comisd xmm13, qword ptr [rip + _FP8]
seta r12b
and r12b, 1
movsd xmm13, qword ptr _global_composite_fadd_a[rip]
comisd xmm13, qword ptr [rip + _FP9]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
jmp label5
label5:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 40]
movsd xmm15, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
_TestFloatSubtraction:
label6:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
movsd qword ptr [rbp - 32], xmm13
movsd qword ptr [rbp - 40], xmm14
movsd qword ptr [rbp - 48], xmm15
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm15
movsd xmm15, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 64], xmm15
movsd xmm15, qword ptr [rbp - 64]
comisd xmm15, qword ptr [rip + _FP10]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 64]
comisd xmm15, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr [rip + _FP12]
movsd qword ptr [rbp - 72], xmm15
movsd xmm15, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 80], xmm15
movsd xmm15, qword ptr [rbp - 72]
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, xmm15
subsd xmm13, xmm14
movsd qword ptr [rbp - 88], xmm13
movsd xmm13, qword ptr [rbp - 88]
comisd xmm13, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rbp - 88]
comisd xmm13, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm13, qword ptr _global_float_4[rip]
movsd xmm14, qword ptr _global_float_2[rip]
movsd xmm15, xmm13
subsd xmm15, xmm14
movsd qword ptr [rbp - 96], xmm15
movsd xmm15, qword ptr [rbp - 96]
comisd xmm15, qword ptr [rip + _FP10]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 96]
comisd xmm15, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr _global_float_4[rip]
movsd xmm14, qword ptr [rbp - 80]
movsd xmm13, xmm15
subsd xmm13, xmm14
movsd qword ptr [rbp - 104], xmm13
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rbp - 104]
comisd xmm13, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm13, qword ptr [rbp - 72]
movsd xmm14, qword ptr _global_float_3[rip]
movsd xmm15, xmm13
subsd xmm15, xmm14
movsd qword ptr [rbp - 112], xmm15
movsd xmm15, qword ptr [rbp - 112]
comisd xmm15, qword ptr [rip + _FP13]
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rbp - 112]
comisd xmm15, qword ptr [rip + _FP14]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm15, qword ptr [rip + _FP12]
movsd qword ptr [rbp - 120], xmm15
movsd xmm15, qword ptr [rbp - 120]
movsd xmm14, xmm15
movsd xmm15, qword ptr [rip + _FP5]
subsd xmm14, xmm15
movsd qword ptr [rbp - 120], xmm14
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 120]
comisd xmm14, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm14, qword ptr [rip + _FP12]
movsd qword ptr [rbp - 128], xmm14
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 136], xmm14
movsd xmm14, qword ptr [rbp - 128]
movsd xmm15, qword ptr [rbp - 136]
movsd xmm13, xmm14
subsd xmm13, xmm15
movsd qword ptr [rbp - 128], xmm13
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP10]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm13, qword ptr _global_composite_fsub_a[rip]
movsd xmm15, qword ptr _global_composite_fsub_b[rip]
movsd xmm14, xmm13
subsd xmm14, xmm15
movsd qword ptr _global_composite_fsub_a[rip], xmm14
movsd xmm14, qword ptr _global_composite_fsub_a[rip]
comisd xmm14, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
movsd xmm14, qword ptr _global_composite_fsub_a[rip]
comisd xmm14, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm14, qword ptr _global_composite_fsub_b[rip]
movsd xmm15, xmm14
movsd xmm14, qword ptr [rip + _FP5]
subsd xmm15, xmm14
movsd qword ptr _global_composite_fsub_b[rip], xmm15
movsd xmm15, qword ptr [rip + _FP0]
movsd xmm14, qword ptr [rip + _FP15]
xorpd xmm15, xmm14
movsd xmm14, qword ptr _global_composite_fsub_b[rip]
comisd xmm14, xmm15
seta r14b
and r14b, 1
movsd xmm14, qword ptr _global_composite_fsub_b[rip]
comisd xmm14, qword ptr [rip + _FP0]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 144], xmm14
movsd xmm14, qword ptr _global_composite_fsub_a[rip]
movsd xmm15, qword ptr [rbp - 144]
movsd xmm13, xmm14
subsd xmm13, xmm15
movsd qword ptr _global_composite_fsub_a[rip], xmm13
movsd xmm13, qword ptr [rip + _FP0]
movsd xmm15, qword ptr [rip + _FP15]
xorpd xmm13, xmm15
movsd xmm15, qword ptr _global_composite_fsub_a[rip]
comisd xmm15, xmm13
seta r12b
and r12b, 1
movsd xmm15, qword ptr _global_composite_fsub_a[rip]
comisd xmm15, qword ptr [rip + _FP0]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
jmp label7
label7:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 40]
movsd xmm15, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
_TestMixedTypeAddition:
label8:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
movsd qword ptr [rbp - 32], xmm13
movsd qword ptr [rbp - 40], xmm14
movsd qword ptr [rbp - 48], xmm15
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm15
mov r14, qword ptr _global_int_1[rip]
cvtsi2sd xmm15, r14
movsd xmm14, qword ptr _global_float_1[rip]
movsd xmm13, xmm15
addsd xmm13, xmm14
movsd qword ptr [rbp - 64], xmm13
movsd xmm13, qword ptr [rbp - 64]
comisd xmm13, qword ptr [rip + _FP8]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 64]
comisd xmm13, qword ptr [rip + _FP9]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov qword ptr [rbp - 72], 5
mov r12, qword ptr [rbp - 72]
cvtsi2sd xmm13, r12
movsd xmm14, qword ptr _global_float_2[rip]
movsd xmm15, xmm13
addsd xmm15, xmm14
movsd qword ptr [rbp - 80], xmm15
movsd xmm15, qword ptr [rbp - 80]
comisd xmm15, qword ptr [rip + _FP16]
seta r12b
and r12b, 1
movsd xmm15, qword ptr [rbp - 80]
comisd xmm15, qword ptr [rip + _FP17]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm15, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 88], xmm15
mov r14, qword ptr _global_int_2[rip]
cvtsi2sd xmm15, r14
movsd xmm14, qword ptr [rbp - 88]
movsd xmm13, xmm15
addsd xmm13, xmm14
movsd qword ptr [rbp - 96], xmm13
movsd xmm13, qword ptr [rbp - 96]
comisd xmm13, qword ptr [rip + _FP18]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 96]
comisd xmm13, qword ptr [rip + _FP19]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
cvtsi2sd xmm13, qword ptr [rip + _INT0]
movsd xmm14, qword ptr _global_float_3[rip]
movsd xmm15, xmm13
addsd xmm15, xmm14
movsd qword ptr [rbp - 104], xmm15
movsd xmm15, qword ptr [rbp - 104]
comisd xmm15, qword ptr [rip + _FP20]
seta r12b
and r12b, 1
movsd xmm15, qword ptr [rbp - 104]
comisd xmm15, qword ptr [rip + _FP21]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
mov r14, qword ptr _global_int_3[rip]
cvtsi2sd xmm15, r14
movsd xmm14, xmm15
movsd xmm15, qword ptr [rip + _FP4]
addsd xmm14, xmm15
movsd qword ptr [rbp - 112], xmm14
movsd xmm14, qword ptr [rbp - 112]
comisd xmm14, qword ptr [rip + _FP22]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rbp - 112]
comisd xmm14, qword ptr [rip + _FP23]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr [rbp - 72]
cvtsi2sd xmm14, r12
movsd xmm15, xmm14
movsd xmm14, qword ptr [rip + _FP24]
addsd xmm15, xmm14
movsd qword ptr [rbp - 120], xmm15
movsd xmm15, qword ptr [rbp - 120]
comisd xmm15, qword ptr [rip + _FP25]
seta r12b
and r12b, 1
movsd xmm15, qword ptr [rbp - 120]
comisd xmm15, qword ptr [rip + _FP26]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm15, qword ptr [rip + _FP4]
movsd qword ptr [rbp - 128], xmm15
cvtsi2sd xmm15, qword ptr [rip + _INT1]
movsd xmm14, qword ptr [rbp - 128]
movsd xmm13, xmm14
addsd xmm13, xmm15
movsd qword ptr [rbp - 128], xmm13
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP8]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 128]
comisd xmm13, qword ptr [rip + _FP9]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov qword ptr [rbp - 136], 5
mov r12, qword ptr [rbp - 136]
cvtsi2sd xmm13, r12
movsd xmm15, xmm13
movsd xmm13, qword ptr [rip + _FP5]
addsd xmm15, xmm13
cvttsd2si r12, xmm15
mov qword ptr [rbp - 136], r12
mov r12, qword ptr [rbp - 136]
cmp r12, 7
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov qword ptr [rbp - 144], 5
mov r12, qword ptr [rbp - 144]
cvtsi2sd xmm15, r12
movsd xmm13, qword ptr _global_composite_mix_add_float[rip]
movsd xmm14, xmm13
addsd xmm14, xmm15
movsd qword ptr _global_composite_mix_add_float[rip], xmm14
movsd xmm14, qword ptr _global_composite_mix_add_float[rip]
comisd xmm14, qword ptr [rip + _FP8]
seta r12b
and r12b, 1
movsd xmm14, qword ptr _global_composite_mix_add_float[rip]
comisd xmm14, qword ptr [rip + _FP9]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm14, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 152], xmm14
mov r14, qword ptr _global_composite_mix_add_int[rip]
cvtsi2sd xmm14, r14
movsd xmm15, qword ptr [rbp - 152]
movsd xmm13, xmm14
addsd xmm13, xmm15
cvttsd2si r14, xmm13
mov qword ptr _global_composite_mix_add_int[rip], r14
mov r14, qword ptr _global_composite_mix_add_int[rip]
cmp r14, 7
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
cvtsi2sd xmm13, qword ptr [rip + _INT1]
movsd xmm15, qword ptr _global_composite_mix_add_float[rip]
movsd xmm14, xmm15
addsd xmm14, xmm13
movsd qword ptr _global_composite_mix_add_float[rip], xmm14
movsd xmm14, qword ptr _global_composite_mix_add_float[rip]
comisd xmm14, qword ptr [rip + _FP27]
seta r14b
and r14b, 1
movsd xmm14, qword ptr _global_composite_mix_add_float[rip]
comisd xmm14, qword ptr [rip + _FP28]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_composite_mix_add_int[rip]
cvtsi2sd xmm14, r12
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP5]
addsd xmm13, xmm14
cvttsd2si r12, xmm13
mov qword ptr _global_composite_mix_add_int[rip], r12
mov r12, qword ptr _global_composite_mix_add_int[rip]
cmp r12, 9
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
jmp label9
label9:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 40]
movsd xmm15, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
_TestMixedTypeSubtraction:
label10:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
movsd qword ptr [rbp - 32], xmm13
movsd qword ptr [rbp - 40], xmm14
movsd qword ptr [rbp - 48], xmm15
movsd xmm15, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm15
mov r14, qword ptr _global_int_3[rip]
cvtsi2sd xmm15, r14
movsd xmm14, qword ptr _global_float_4[rip]
movsd xmm13, xmm14
subsd xmm13, xmm15
movsd qword ptr [rbp - 64], xmm13
movsd xmm13, qword ptr [rip + _FP29]
movsd xmm15, qword ptr [rip + _FP15]
xorpd xmm13, xmm15
movsd xmm15, qword ptr [rbp - 64]
comisd xmm15, xmm13
seta r14b
and r14b, 1
movsd xmm15, qword ptr [rip + _FP30]
movsd xmm13, qword ptr [rip + _FP15]
xorpd xmm15, xmm13
movsd xmm13, qword ptr [rbp - 64]
comisd xmm13, xmm15
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
movsd xmm13, qword ptr [rip + _FP12]
movsd qword ptr [rbp - 72], xmm13
mov r12, qword ptr _global_int_2[rip]
cvtsi2sd xmm13, r12
movsd xmm15, qword ptr [rbp - 72]
movsd xmm14, xmm15
subsd xmm14, xmm13
movsd qword ptr [rbp - 80], xmm14
movsd xmm14, qword ptr [rip + _FP31]
movsd xmm13, qword ptr [rip + _FP15]
xorpd xmm14, xmm13
movsd xmm13, qword ptr [rbp - 80]
comisd xmm13, xmm14
seta r12b
and r12b, 1
movsd xmm13, qword ptr [rip + _FP32]
movsd xmm14, qword ptr [rip + _FP15]
xorpd xmm13, xmm14
movsd xmm14, qword ptr [rbp - 80]
comisd xmm14, xmm13
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
mov qword ptr [rbp - 88], 3
mov r14, qword ptr [rbp - 88]
cvtsi2sd xmm14, r14
movsd xmm13, qword ptr _global_float_2[rip]
movsd xmm15, xmm13
subsd xmm15, xmm14
movsd qword ptr [rbp - 96], xmm15
movsd xmm15, qword ptr [rip + _FP33]
movsd xmm14, qword ptr [rip + _FP15]
xorpd xmm15, xmm14
movsd xmm14, qword ptr [rbp - 96]
comisd xmm14, xmm15
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rip + _FP34]
movsd xmm15, qword ptr [rip + _FP15]
xorpd xmm14, xmm15
movsd xmm15, qword ptr [rbp - 96]
comisd xmm15, xmm14
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_int_1[rip]
cvtsi2sd xmm15, r12
movsd xmm14, qword ptr [rip + _FP35]
subsd xmm14, xmm15
movsd qword ptr [rbp - 104], xmm14
movsd xmm14, qword ptr [rbp - 104]
comisd xmm14, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [rbp - 104]
comisd xmm14, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
cvtsi2sd xmm14, qword ptr [rip + _INT2]
movsd xmm15, qword ptr _global_float_1[rip]
movsd xmm13, xmm15
subsd xmm13, xmm14
movsd qword ptr [rbp - 112], xmm13
movsd xmm13, qword ptr [rbp - 112]
comisd xmm13, qword ptr [rip + _FP36]
seta r14b
and r14b, 1
movsd xmm13, qword ptr [rbp - 112]
comisd xmm13, qword ptr [rip + _FP37]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
cvtsi2sd xmm13, qword ptr [rip + _INT2]
movsd xmm14, qword ptr [rbp - 72]
movsd xmm15, xmm14
subsd xmm15, xmm13
movsd qword ptr [rbp - 120], xmm15
movsd xmm15, qword ptr [rbp - 120]
comisd xmm15, qword ptr [rip + _FP38]
seta r12b
and r12b, 1
movsd xmm15, qword ptr [rbp - 120]
comisd xmm15, qword ptr [rip + _FP39]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm15, qword ptr [rip + _FP12]
movsd qword ptr [rbp - 128], xmm15
cvtsi2sd xmm15, qword ptr [rip + _INT3]
movsd xmm13, qword ptr [rbp - 128]
movsd xmm14, xmm13
subsd xmm14, xmm15
movsd qword ptr [rbp - 128], xmm14
movsd xmm14, qword ptr [rbp - 128]
comisd xmm14, qword ptr [rip + _FP30]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rbp - 128]
comisd xmm14, qword ptr [rip + _FP29]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov qword ptr [rbp - 136], 15
mov r12, qword ptr [rbp - 136]
cvtsi2sd xmm14, r12
movsd xmm15, xmm14
movsd xmm14, qword ptr [rip + _FP5]
subsd xmm15, xmm14
cvttsd2si r12, xmm15
mov qword ptr [rbp - 136], r12
mov r12, qword ptr [rbp - 136]
cmp r12, 12
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
mov qword ptr [rbp - 144], 3
mov r12, qword ptr [rbp - 144]
cvtsi2sd xmm15, r12
movsd xmm14, qword ptr _global_composite_mix_sub_float[rip]
movsd xmm13, xmm14
subsd xmm13, xmm15
movsd qword ptr _global_composite_mix_sub_float[rip], xmm13
movsd xmm13, qword ptr _global_composite_mix_sub_float[rip]
comisd xmm13, qword ptr [rip + _FP30]
seta r12b
and r12b, 1
movsd xmm13, qword ptr _global_composite_mix_sub_float[rip]
comisd xmm13, qword ptr [rip + _FP29]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov dil, r14b
call _Assert
movsd xmm13, qword ptr [rip + _FP5]
movsd qword ptr [rbp - 152], xmm13
mov r14, qword ptr _global_composite_mix_sub_int[rip]
cvtsi2sd xmm13, r14
movsd xmm15, qword ptr [rbp - 152]
movsd xmm14, xmm13
subsd xmm14, xmm15
cvttsd2si r14, xmm14
mov qword ptr _global_composite_mix_sub_int[rip], r14
mov r14, qword ptr _global_composite_mix_sub_int[rip]
cmp r14, 12
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
cvtsi2sd xmm14, qword ptr [rip + _INT2]
movsd xmm15, qword ptr _global_composite_mix_sub_float[rip]
movsd xmm13, xmm15
subsd xmm13, xmm14
movsd qword ptr _global_composite_mix_sub_float[rip], xmm13
movsd xmm13, qword ptr [rip + _FP0]
movsd xmm14, qword ptr [rip + _FP15]
xorpd xmm13, xmm14
movsd xmm14, qword ptr _global_composite_mix_sub_float[rip]
comisd xmm14, xmm13
seta r14b
and r14b, 1
movsd xmm14, qword ptr _global_composite_mix_sub_float[rip]
comisd xmm14, qword ptr [rip + _FP0]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov dil, r12b
call _Assert
mov r12, qword ptr _global_composite_mix_sub_int[rip]
cvtsi2sd xmm14, r12
movsd xmm13, xmm14
movsd xmm14, qword ptr [rip + _FP5]
subsd xmm13, xmm14
cvttsd2si r12, xmm13
mov qword ptr _global_composite_mix_sub_int[rip], r12
mov r12, qword ptr _global_composite_mix_sub_int[rip]
cmp r12, 9
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
jmp label11
label11:
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
movsd xmm13, qword ptr [rbp - 32]
movsd xmm14, qword ptr [rbp - 40]
movsd xmm15, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
.globl _main

_main:
label12:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
call _TestIntAddition
call _TestIntSubtraction
call _TestFloatAddition
call _TestFloatSubtraction
call _TestMixedTypeAddition
call _TestMixedTypeSubtraction
mov qword ptr [rbp - 16], 0
jmp label14
label13:
label14:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
