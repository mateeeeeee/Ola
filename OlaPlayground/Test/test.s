.intel_syntax noprefix

.section .rodata

_FP0:
.quad 0


_FP1:
.quad 4591870180066957722


_FP2:
.quad 4607092346807469998


_FP3:
.quad 4616741309009111286


_FP4:
.quad 4616763827007248138


.section .text

.extern Assert

.extern AssertMsg

TestWhileLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label1
label1:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label2
jmp label3
label2:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label1
label3:
mov r14, qword ptr [rbp - 32]
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label4
label4:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestWhileLoopBool:
label5:
push rbp
mov rbp, rsp
sub rsp, 65
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov byte ptr [rbp - 17], 1
mov qword ptr [rbp - 25], 0
jmp label6
label6:
mov r14b, byte ptr [rbp - 17]
test r14b, r14b
jne label7
jmp label8
label7:
mov r14, qword ptr [rbp - 25]
mov qword ptr [rbp - 33], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 25], r13
mov r13, qword ptr [rbp - 25]
cmp r13, 3
sete r13b
and r13b, 1
test r13b, r13b
jne label9
jmp label11
label8:
mov r14, qword ptr [rbp - 25]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label12
label9:
mov byte ptr [rbp - 17], 0
jmp label11
label10:
label11:
jmp label6
label12:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestNestedWhileLoops:
label13:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
jmp label14
label14:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label15
jmp label16
label15:
jmp label17
label16:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label20
label17:
mov r14, qword ptr [rbp - 32]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label18
jmp label19
label18:
mov r13, qword ptr [rbp - 32]
mov qword ptr [rbp - 40], r13
mov r14, r13
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label17
label19:
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 24], r13
jmp label14
label20:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestWhileLoopWithBreak:
label21:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label22
label22:
jmp label23
label23:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
mov r13, qword ptr [rbp - 40]
cmp r13, 5
setg r13b
and r13b, 1
test r13b, r13b
jne label25
jmp label27
label24:
mov r13, qword ptr [rbp - 32]
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label29
label25:
jmp label24
label26:
label27:
jmp label22
label28:
label29:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestWhileLoopWithContinue:
label30:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 0
jmp label31
label31:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label32
jmp label33
label32:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 40], r13
mov r13, qword ptr [rbp - 40]
mov rax, r13
cqo
mov r13, 2
idiv r13
mov r13, rdx
cmp r13, 0
sete r13b
and r13b, 1
test r13b, r13b
jne label34
jmp label36
label33:
mov r14, qword ptr [rbp - 32]
cmp r14, 9
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label38
label34:
jmp label31
label35:
label36:
mov r13, qword ptr [rbp - 32]
mov r14, qword ptr [rbp - 40]
mov r12, r13
add r12, r14
mov qword ptr [rbp - 32], r12
jmp label31
label37:
label38:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestWhileLoopMultipleExits:
label39:
push rbp
mov rbp, rsp
sub rsp, 73
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov byte ptr [rbp - 33], 0
jmp label40
label40:
mov r14, qword ptr [rbp - 32]
cmp r14, 5
setl r14b
and r14b, 1
mov r13b, byte ptr [rbp - 33]
cmp r13b, 0
sete r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
test r12b, r12b
jne label41
jmp label42
label41:
mov r12, qword ptr [rbp - 32]
mov qword ptr [rbp - 41], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 32], r13
mov r13, qword ptr [rbp - 32]
cmp r13, 3
sete r13b
and r13b, 1
test r13b, r13b
jne label43
jmp label45
label42:
mov r12, qword ptr [rbp - 32]
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12b, byte ptr [rbp - 33]
mov cl, r12b
call Assert
jmp label46
label43:
mov byte ptr [rbp - 33], 1
jmp label45
label44:
label45:
jmp label40
label46:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestWhileLoopExternalDeclaration:
label47:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 0
jmp label48
label48:
mov r14, qword ptr [rbp - 32]
cmp r14, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label49
jmp label50
label49:
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 32]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 40], r12
mov r12, qword ptr [rbp - 32]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 32], r13
jmp label48
label50:
mov r14, qword ptr [rbp - 40]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label51
label51:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestWhileLoopWithCalculation:
label52:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 10
mov qword ptr [rbp - 32], 0
jmp label53
label53:
mov r14, qword ptr [rbp - 24]
cmp r14, 0
setg r14b
and r14b, 1
test r14b, r14b
jne label54
jmp label55
label54:
mov r14, qword ptr [rbp - 24]
mov r13, r14
sub r13, 2
mov qword ptr [rbp - 24], r13
mov r13, qword ptr [rbp - 32]
mov qword ptr [rbp - 40], r13
mov r14, r13
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label53
label55:
mov r14, qword ptr [rbp - 32]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label56
label56:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestWhileLoopFloatCondition:
label57:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [rbp - 56], xmm14
movsd xmm14, qword ptr [rip + _FP1]
movsd qword ptr [rbp - 64], xmm14
jmp label58
label58:
movsd xmm14, qword ptr [rbp - 64]
comisd xmm14, qword ptr [rip + _FP2]
setb r14b
and r14b, 1
test r14b, r14b
jne label59
jmp label60
label59:
movsd xmm14, qword ptr [rbp - 56]
movsd xmm13, qword ptr [rbp - 64]
movsd xmm12, xmm14
addsd xmm12, xmm13
movsd qword ptr [rbp - 56], xmm12
movsd xmm12, qword ptr [rbp - 64]
movsd xmm13, xmm12
movsd xmm12, qword ptr [rip + _FP1]
addsd xmm13, xmm12
movsd qword ptr [rbp - 64], xmm13
jmp label58
label60:
movsd xmm14, qword ptr [rbp - 56]
comisd xmm14, qword ptr [rip + _FP3]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [rbp - 56]
comisd xmm14, qword ptr [rip + _FP4]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label61
label61:
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
label62:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestWhileLoopInt
call TestWhileLoopBool
call TestNestedWhileLoops
call TestWhileLoopWithBreak
call TestWhileLoopWithContinue
call TestWhileLoopMultipleExits
call TestWhileLoopExternalDeclaration
call TestWhileLoopWithCalculation
call TestWhileLoopFloatCondition
mov qword ptr [rbp - 16], 0
jmp label64
label63:
label64:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
