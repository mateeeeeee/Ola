.intel_syntax noprefix

.section .rodata

_FP0:
.quad 0


_FP1:
.quad 4591870180066957722


_FP2:
.quad 4606732058837280358


_FP3:
.quad 4616741309009111286


_FP4:
.quad 4616763827007248138


.section .text

.extern Assert

.extern AssertMsg

TestForLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label2
label1:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
jmp label3
label2:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label4
label3:
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label2
label4:
mov r14, qword ptr [rbp - 32]
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestForLoopManualIncrement:
label6:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label8
label7:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 40]
mov r13, r12
add r13, 2
mov qword ptr [rbp - 40], r13
jmp label9
label8:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label7
jmp label10
label9:
jmp label8
label10:
mov r14, qword ptr [rbp - 32]
cmp r14, 9
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label11
label11:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestForLoopMultipleExpressions:
label12:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
mov qword ptr [rbp - 48], 5
jmp label14
label13:
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
add r12, r13
mov r13, qword ptr [rbp - 32]
mov r14, r13
add r14, r12
mov qword ptr [rbp - 32], r14
jmp label15
label14:
mov r14, qword ptr [rbp - 40]
cmp r14, 3
setle r14b
and r14b, 1
test r14b, r14b
jne label13
jmp label16
label15:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 56], r14
mov r12, r14
add r12, 1
mov qword ptr [rbp - 40], r12
mov r12, qword ptr [rbp - 48]
mov qword ptr [rbp - 64], r12
mov r14, r12
sub r14, 1
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 56]
mov r14, qword ptr [rbp - 64]
jmp label14
label16:
mov r14, qword ptr [rbp - 32]
cmp r14, 18
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label17
label17:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestNestedForLoops:
label18:
push rbp
mov rbp, rsp
sub rsp, 88
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 0
jmp label20
label19:
jmp label24
label20:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label19
jmp label22
label21:
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 24], r13
jmp label20
label22:
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
jmp label27
label23:
mov r13, qword ptr [rbp - 40]
mov r14, r13
add r14, 1
mov qword ptr [rbp - 40], r14
jmp label25
label24:
mov r14, qword ptr [rbp - 32]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label23
jmp label26
label25:
mov r14, qword ptr [rbp - 32]
mov qword ptr [rbp - 56], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 32], r13
jmp label24
label26:
jmp label21
label27:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestNestedForLoopsReset:
label28:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
jmp label30
label29:
mov qword ptr [rbp - 40], 0
jmp label34
label30:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label29
jmp label32
label31:
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 24], r13
jmp label30
label32:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label37
label33:
mov r13, qword ptr [rbp - 32]
mov qword ptr [rbp - 56], r13
mov r14, r13
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label35
label34:
mov r14, qword ptr [rbp - 40]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label33
jmp label36
label35:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 64], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label34
label36:
jmp label31
label37:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestForLoopWithBreak:
label38:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label40
label39:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 40]
cmp r12, 3
sete r12b
and r12b, 1
test r12b, r12b
jne label43
jmp label45
label40:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label39
jmp label42
label41:
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label40
label42:
mov r14, qword ptr [rbp - 32]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label47
label43:
jmp label42
label44:
label45:
jmp label41
label46:
label47:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestForLoopWithContinue:
label48:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 1
jmp label50
label49:
mov r14, qword ptr [rbp - 40]
cmp r14, 3
sete r14b
and r14b, 1
test r14b, r14b
jne label53
jmp label55
label50:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label49
jmp label52
label51:
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label50
label52:
mov r14, qword ptr [rbp - 32]
cmp r14, 12
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label57
label53:
jmp label51
label54:
label55:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
jmp label51
label56:
label57:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestForLoopEmptyBody:
label58:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
jmp label60
label59:
jmp label61
label60:
mov r14, qword ptr [rbp - 32]
cmp r14, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label59
jmp label62
label61:
mov r14, qword ptr [rbp - 32]
mov qword ptr [rbp - 40], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 32], r13
jmp label60
label62:
mov r14, qword ptr [rbp - 24]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 32]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label63
label63:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestForLoopNeverExecutes:
label64:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 10
jmp label66
label65:
mov r14, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
mov r12, r14
add r12, r13
mov qword ptr [rbp - 32], r12
jmp label67
label66:
mov r14, qword ptr [rbp - 40]
cmp r14, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label65
jmp label68
label67:
mov r12, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r12
mov r13, r12
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label66
label68:
mov r14, qword ptr [rbp - 32]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label69
label69:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestForLoopFloatCondition:
label70:
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
jmp label72
label71:
movsd xmm14, qword ptr [rbp - 56]
movsd xmm13, qword ptr [rbp - 64]
movsd xmm12, xmm14
addsd xmm12, xmm13
movsd qword ptr [rbp - 56], xmm12
jmp label73
label72:
movsd xmm14, qword ptr [rbp - 64]
comisd xmm14, qword ptr [rip + _FP2]
setb r14b
and r14b, 1
test r14b, r14b
jne label71
jmp label74
label73:
movsd xmm12, qword ptr [rbp - 64]
movsd xmm13, xmm12
movsd xmm12, qword ptr [rip + _FP1]
addsd xmm13, xmm12
movsd qword ptr [rbp - 64], xmm13
jmp label72
label74:
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
jmp label75
label75:
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
label76:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestForLoopInt
call TestForLoopManualIncrement
call TestForLoopMultipleExpressions
call TestNestedForLoops
call TestNestedForLoopsReset
call TestForLoopWithBreak
call TestForLoopWithContinue
call TestForLoopEmptyBody
call TestForLoopNeverExecutes
call TestForLoopFloatCondition
mov qword ptr [rbp - 16], 0
jmp label78
label77:
label78:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
