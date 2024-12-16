.intel_syntax noprefix

.section .rodata

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


_FP0:
.quad 4618441305278452964


_FP1:
.quad 4618441530458434332


_FP2:
.quad 4612811918334230528


_FP3:
.quad 4615063718147915776


_FP4:
.quad 4616977635399557553


_FP5:
.quad 4616977860579538921


_FP6:
.quad 4612811693154249159


_FP7:
.quad 4612812143514211897


_FP8:
.quad 4617315517961601024


_FP9:
.quad 4615739032912039982


_FP10:
.quad 4615739483272002719


.section .text

.extern Assert

.extern AssertMsg

TestIntAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r15, qword ptr global_int_1[rip]
mov r14, qword ptr global_int_2[rip]
mov r13, r15
add r13, r14
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_int_1[rip]
mov r14, r13
add r14, 10
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_int_3[rip]
mov r13, 5
add r13, r14
cmp r13, 12
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

TestIntSubtraction:
label2:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r15, qword ptr global_sub_1[rip]
mov r14, qword ptr global_sub_2[rip]
mov r13, r15
sub r13, r14
cmp r13, 8
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_sub_4[rip]
mov r14, r13
sub r14, 7
cmp r14, 23
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_sub_3[rip]
mov r13, 15
sub r13, r14
cmp r13, 12
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label3
label3:
mov rsp, rbp
pop rbp
ret

TestFloatAddition:
label4:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15b, 1
and r15b, 1
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15b, 1
and r15b, 1
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr global_float_1[rip]
movsd xmm14, qword ptr global_float_2[rip]
movsd xmm13, xmm15
addsd xmm13, xmm14
comisd xmm13, qword ptr [rip + _FP0]
seta r15b
and r15b, 1
comisd xmm13, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r13b, r15b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr global_float_1[rip]
movsd xmm14, xmm13
movsd xmm13, qword ptr [rip + _FP2]
addsd xmm14, xmm13
comisd xmm14, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
comisd xmm14, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r15b, r13b
and r15b, r14b
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr global_float_3[rip]
movsd xmm13, qword ptr [rip + _FP3]
addsd xmm13, xmm14
comisd xmm13, qword ptr [rip + _FP4]
seta r15b
and r15b, 1
comisd xmm13, qword ptr [rip + _FP5]
setb r14b
and r14b, 1
mov r13b, r15b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label5
label5:
mov rsp, rbp
pop rbp
ret

TestFloatSubtraction:
label6:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15b, 1
and r15b, 1
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15b, 1
and r15b, 1
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm15, qword ptr global_float_4[rip]
movsd xmm14, qword ptr global_float_2[rip]
movsd xmm13, xmm15
subsd xmm13, xmm14
comisd xmm13, qword ptr [rip + _FP6]
seta r15b
and r15b, 1
comisd xmm13, qword ptr [rip + _FP7]
setb r14b
and r14b, 1
mov r13b, r15b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
movsd xmm13, qword ptr global_float_4[rip]
movsd xmm14, xmm13
movsd xmm13, qword ptr [rip + _FP2]
subsd xmm14, xmm13
comisd xmm14, qword ptr [rip + _FP6]
seta r13b
and r13b, 1
comisd xmm14, qword ptr [rip + _FP7]
setb r14b
and r14b, 1
mov r15b, r13b
and r15b, r14b
cmp r15b, 0
setne r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm14, qword ptr global_float_3[rip]
movsd xmm13, qword ptr [rip + _FP8]
subsd xmm13, xmm14
comisd xmm13, qword ptr [rip + _FP9]
seta r15b
and r15b, 1
comisd xmm13, qword ptr [rip + _FP10]
setb r14b
and r14b, 1
mov r13b, r15b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label7
label7:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label8:
push rbp
mov rbp, rsp
sub rsp, 32
call TestIntAddition
call TestIntSubtraction
call TestFloatAddition
call TestFloatSubtraction
jmp label10
label9:
jmp label10
label10:
mov rax, 0
mov rsp, rbp
pop rbp
ret

