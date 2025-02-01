.intel_syntax noprefix

.section .data

GlobalIntX:
.quad 8


GlobalIntY:
.quad 3


.section .text

.extern Assert

.extern AssertMsg

TestShiftOperatorsIntegers:
label0:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 5
mov qword ptr [rbp - 40], 2
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, r14
shl r13, 1
cmp r13, 16
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
mov r14, r13
sar r14, 1
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
mov r13, 4
mov rcx, r14
shl r13, cl
cmp r13, 32
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntY[rip]
mov r14, 4
mov rcx, r13
sar r14, cl
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
mov r13, r14
shl r13, 1
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 32]
mov r14, r13
sar r14, 1
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, 4
mov rcx, r14
shl r13, cl
cmp r13, 16
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 40]
mov r14, 4
mov rcx, r13
sar r14, cl
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
mov r12, r14
mov rcx, r13
shl r12, cl
cmp r12, 32
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
mov r14, r12
mov rcx, r13
sar r14, cl
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr GlobalIntY[rip]
mov r12, r14
mov rcx, r13
shl r12, cl
cmp r12, 40
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 32]
mov r13, qword ptr GlobalIntY[rip]
mov r14, r12
mov rcx, r13
sar r14, cl
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
mov rcx, r13
shl r12, cl
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r14, r12
mov rcx, r13
sar r14, cl
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov r12, r14
mov rcx, r13
shl r12, cl
cmp r12, 64
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov r14, r12
mov rcx, r13
sar r14, cl
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestCompoundShiftOperatorsIntegers:
label2:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 5
mov qword ptr [rbp - 40], 2
mov r14, qword ptr [rbp - 32]
mov r13, r14
shl r13, 2
mov qword ptr [rbp - 32], r13
mov r13, qword ptr [rbp - 32]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 32]
mov r14, r13
sar r14, 2
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 32]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 48], 4
mov r14, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 40]
mov r12, r14
mov rcx, r13
shl r12, cl
mov qword ptr [rbp - 48], r12
mov r12, qword ptr [rbp - 48]
cmp r12, 16
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 48], 16
mov r12, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 40]
mov r14, r12
mov rcx, r13
sar r14, cl
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 48]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr GlobalIntY[rip]
mov r12, r14
mov rcx, r13
shl r12, cl
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 32]
cmp r12, 40
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 32]
mov r13, qword ptr GlobalIntY[rip]
mov r14, r12
mov rcx, r13
sar r14, cl
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 32]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, r14
shl r13, 1
mov qword ptr GlobalIntX[rip], r13
mov r13, qword ptr GlobalIntX[rip]
cmp r13, 16
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr GlobalIntX[rip]
mov r14, r13
sar r14, 1
mov qword ptr GlobalIntX[rip], r14
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 8
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
mov r12, r14
mov rcx, r13
shl r12, cl
mov qword ptr GlobalIntX[rip], r12
mov r12, qword ptr GlobalIntX[rip]
cmp r12, 32
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr GlobalIntX[rip]
mov r13, qword ptr [rbp - 40]
mov r14, r12
mov rcx, r13
sar r14, cl
mov qword ptr GlobalIntX[rip], r14
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 8
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov r12, r14
mov rcx, r13
shl r12, cl
mov qword ptr GlobalIntX[rip], r12
mov r12, qword ptr GlobalIntX[rip]
cmp r12, 64
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr GlobalIntX[rip]
mov r13, qword ptr GlobalIntY[rip]
mov r14, r12
mov rcx, r13
sar r14, cl
mov qword ptr GlobalIntX[rip], r14
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 8
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr GlobalIntX[rip], 8
jmp label3
label3:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
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
call TestShiftOperatorsIntegers
call TestCompoundShiftOperatorsIntegers
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
