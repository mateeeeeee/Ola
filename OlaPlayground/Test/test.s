.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestDoWhileLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 1
mov r13, 0
jmp label1
label1:
mov r12, r13
add r12, r14
mov qword ptr [rbp - 48], r14
mov rdi, r14
add rdi, 1
jmp label2
label2:
cmp rdi, 5
setle sil
and sil, 1
test sil, sil
mov r14, rdi
mov r13, r12
jne label1
jmp label3
label3:
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label4
label4:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopBool:
label5:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 0
mov r13b, 1
jmp label6
label6:
mov qword ptr [rbp - 40], r14
mov r12, r14
add r12, 1
cmp r12, 3
sete dil
and dil, 1
test dil, dil
jne label9
mov dil, r13b
jmp label10
label7:
test dil, dil
mov r14, r12
mov r13b, dil
jne label6
jmp label8
label8:
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label11
label9:
mov dil, 0
jmp label10
label10:
jmp label7
label11:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestNestedDoWhileLoops:
label12:
push rbp
mov rbp, rsp
sub rsp, 88
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 0
mov r13, 0
jmp label13
label13:
mov r12, r14
jmp label16
label14:
cmp r12, 3
setl sil
and sil, 1
test sil, sil
mov r14, rdi
mov r13, r12
jne label13
jmp label15
label15:
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
cmp rdi, 4
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label19
label16:
mov qword ptr [rbp - 56], r12
mov rdi, r12
add rdi, 1
jmp label17
label17:
cmp rdi, 2
setl sil
and sil, 1
test sil, sil
mov r12, rdi
jne label16
jmp label18
label18:
mov qword ptr [rbp - 48], r13
mov r12, r13
add r12, 1
jmp label14
label19:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithBreak:
label20:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 0
mov r13, 1
jmp label21
label21:
mov r12, r14
add r12, r13
mov qword ptr [rbp - 48], r13
mov rdi, r13
add rdi, 1
cmp rdi, 5
setg sil
and sil, 1
test sil, sil
jne label23
jmp label22
label22:
mov r14, r12
mov r13, rdi
jmp label21
label23:
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label24
label24:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithContinue:
label25:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 0
mov r13, 0
jmp label26
label26:
mov qword ptr [rbp - 48], r14
mov r12, r14
add r12, 1
mov rax, r12
cqo
mov rdi, 2
idiv rdi
mov rdi, rdx
cmp rdi, 0
sete dil
and dil, 1
test dil, dil
jne label29
jmp label30
label27:
cmp r12, 5
setl dil
and dil, 1
test dil, dil
mov r14, r12
mov r13, rsi
jne label26
jmp label28
label28:
cmp rsi, 9
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label31
label29:
mov rsi, r13
jmp label27
label30:
mov rdi, r13
add rdi, r12
mov rsi, rdi
jmp label27
label31:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestEmptyDoWhileLoop:
label32:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 0
jmp label33
label33:
jmp label34
label34:
mov r13, r14
add r13, 1
cmp r13, 2
setl r12b
and r12b, 1
test r12b, r12b
mov r14, r13
jne label33
jmp label35
label35:
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label36
label36:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopBoundary:
label37:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, 0
jmp label38
label38:
mov qword ptr [rbp - 24], r14
mov r13, r14
add r13, 1
jmp label39
label39:
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label40
label40:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithMultipleVariables:
label41:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 1
mov r13, 1
jmp label42
label42:
mov r12, r13
add r12, r14
jmp label43
label43:
cmp r12, 10
setl dil
and dil, 1
test dil, dil
mov rdi, r14
mov r14, r12
mov r13, rdi
jne label42
jmp label44
label44:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopComplexCondition:
label45:
push rbp
mov rbp, rsp
sub rsp, 104
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, 3
mov r13, 0
jmp label46
label46:
mov qword ptr [rbp - 56], r13
mov r12, r13
add r12, 1
mov qword ptr [rbp - 64], r14
mov qword ptr [rbp - 72], r14
sub qword ptr [rbp - 72], 1
jmp label47
label47:
cmp r12, 3
setl sil
and sil, 1
cmp qword ptr [rbp - 72], 0
setg bl
and bl, 1
mov dil, sil
and dil, bl
cmp dil, 0
setne dil
and dil, 1
test dil, dil
mov r14, qword ptr [rbp - 72]
mov r13, r12
jne label46
jmp label48
label48:
cmp r12, 3
sete r12b
and r12b, 1
cmp qword ptr [rbp - 72], 0
sete dil
and dil, 1
mov r13b, r12b
and r13b, dil
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label49
label49:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopChangingCondition:
label50:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 0
mov r13, 0
jmp label51
label51:
mov qword ptr [rbp - 48], r13
mov r12, r13
add r12, 1
cmp r12, 3
sete dil
and dil, 1
test dil, dil
jne label54
mov rdi, r12
jmp label55
label52:
cmp rdi, 5
setl sil
and sil, 1
test sil, sil
mov r14, r12
mov r13, rdi
jne label51
jmp label53
label53:
cmp r12, 13
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label56
label54:
mov rdi, 10
jmp label55
label55:
mov r12, r14
add r12, rdi
jmp label52
label56:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopMultipleExits:
label57:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 0
jmp label58
label58:
mov qword ptr [rbp - 32], r14
mov r13, r14
add r13, 1
cmp r13, 5
sete r12b
and r12b, 1
test r12b, r12b
jne label61
jmp label62
label59:
mov r14, r13
jmp label58
label60:
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov cl, r14b
call Assert
jmp label64
label61:
mov r14b, 1
jmp label60
label62:
cmp r13, 10
setg r12b
and r12b, 1
test r12b, r12b
jne label63
jmp label59
label63:
mov r14b, 0
jmp label60
label64:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label65:
push rbp
mov rbp, rsp
sub rsp, 32
call TestDoWhileLoopInt
call TestDoWhileLoopBool
call TestNestedDoWhileLoops
call TestDoWhileLoopWithBreak
call TestDoWhileLoopWithContinue
call TestEmptyDoWhileLoop
call TestDoWhileLoopBoundary
call TestDoWhileLoopWithMultipleVariables
call TestDoWhileLoopComplexCondition
call TestDoWhileLoopChangingCondition
call TestDoWhileLoopMultipleExits
jmp label66
label66:
mov rax, 0
mov rsp, rbp
pop rbp
ret
