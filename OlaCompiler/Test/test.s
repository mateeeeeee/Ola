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
sub rsp, 128
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 2
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp - 24], r14
mov r14, qword ptr [rbp - 24]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr [rbp - 16]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp - 32], r15
mov r15, qword ptr [rbp - 32]
cmp r15, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr GlobalIntY[rip]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp - 40], r14
mov r14, qword ptr [rbp - 40]
cmp r14, 40
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr GlobalIntY[rip]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp - 48], r15
mov r15, qword ptr [rbp - 48]
cmp r15, 0
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 8]
mov r14, r15
shl r14, r15
mov qword ptr [rbp - 56], r14
mov r14, qword ptr [rbp - 56]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, r14
sar r15, r14
mov qword ptr [rbp - 64], r15
mov r15, qword ptr [rbp - 64]
cmp r15, 2
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp - 72], r14
mov r14, qword ptr [rbp - 72]
cmp r14, 64
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r15, qword ptr GlobalIntY[rip]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp - 80], r15
mov r15, qword ptr [rbp - 80]
cmp r15, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, r15
shl r14, r15
mov qword ptr [rbp - 88], r14
mov r14, qword ptr [rbp - 88]
cmp r14, 32
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r15, r14
sar r15, r14
mov qword ptr [rbp - 96], r15
mov r15, qword ptr [rbp - 96]
cmp r15, 2
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov rcx, 1
call Assert
mov rcx, 1
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

TestCompoundShiftOperatorsIntegers:
label2:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], 5
mov qword ptr [rbp - 16], 2
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp - 8], r14
mov r14, qword ptr [rbp - 8]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr [rbp - 16]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
cmp r15, 5
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr GlobalIntX[rip], r14
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 64
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov r15, qword ptr GlobalIntY[rip]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr GlobalIntX[rip], r15
mov r15, qword ptr GlobalIntX[rip]
cmp r15, 8
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntY[rip]
mov r14, r15
shl r14, r15
mov qword ptr GlobalIntY[rip], r14
mov r14, qword ptr GlobalIntY[rip]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntY[rip]
mov r15, r14
sar r15, r14
mov qword ptr GlobalIntY[rip], r15
mov r15, qword ptr GlobalIntY[rip]
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label3
label3:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 40
call TestShiftOperatorsIntegers
call TestCompoundShiftOperatorsIntegers
mov qword ptr [rbp - 8], 0
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

