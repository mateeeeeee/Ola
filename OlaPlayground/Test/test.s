.intel_syntax noprefix

.text

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
lea r12, [r13 + r14]
mov qword ptr [rbp - 48], r14
lea rdi, [r14 + 1]
jmp label2
label2:
cmp rdi, 5
setle sil
and sil, 1
test sil, sil
jne label3
jmp label4
label3:
mov r14, rdi
mov r13, r12
jmp label1
label4:
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label5
label5:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopBool:
label6:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, 0
mov r13b, 1
jmp label7
label7:
mov qword ptr [rbp - 48], r14
lea r12, [r14 + 1]
cmp r12, 3
sete dil
and dil, 1
test dil, dil
jne label12
jmp label8
label8:
mov sil, r13b
jmp label13
label9:
test sil, sil
jne label10
jmp label11
label10:
mov r14, r12
mov r13b, sil
jmp label7
label11:
mov cl, dil
call Assert
jmp label14
label12:
mov sil, 0
jmp label13
label13:
jmp label9
label14:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestNestedDoWhileLoops:
label15:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, 0
mov r13, 0
jmp label16
label16:
mov r12, r14
jmp label20
label17:
cmp rdi, 3
setl bl
and bl, 1
test bl, bl
jne label18
jmp label19
label18:
mov r14, rsi
mov r13, rdi
jmp label16
label19:
cmp rdi, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
cmp rsi, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label24
label20:
mov qword ptr [rbp - 56], r12
lea rsi, [r12 + 1]
jmp label21
label21:
cmp rsi, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label22
jmp label23
label22:
mov r12, rsi
jmp label20
label23:
mov qword ptr [rbp - 64], r13
lea rdi, [r13 + 1]
jmp label17
label24:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithBreak:
label25:
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
jmp label26
label26:
lea r12, [r13 + r14]
mov qword ptr [rbp - 48], r14
lea rdi, [r14 + 1]
cmp rdi, 5
setg sil
and sil, 1
test sil, sil
jne label28
jmp label27
label27:
mov r14, rdi
mov r13, r12
jmp label26
label28:
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label29
label29:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithContinue:
label30:
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
jmp label31
label31:
mov qword ptr [rbp - 48], r14
lea r12, [r14 + 1]
mov rax, r12
cqo
mov rdi, 2
idiv rdi
mov rdi, rdx
cmp rdi, 0
sete dil
and dil, 1
test dil, dil
jne label35
jmp label36
label32:
cmp r12, 5
setl sil
and sil, 1
test sil, sil
jne label33
jmp label34
label33:
mov r14, r12
mov r13, rdi
jmp label31
label34:
cmp rdi, 9
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label37
label35:
mov rdi, r13
jmp label32
label36:
lea r14, [r13 + r12]
mov rdi, r14
jmp label32
label37:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopBoundary:
label38:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, 0
jmp label39
label39:
mov qword ptr [rbp - 32], r14
lea r13, [r14 + 1]
jmp label40
label40:
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label41
label41:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopWithMultipleVariables:
label42:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], 1
mov qword ptr [rbp - 40], 1
jmp label43
label43:
mov r14, qword ptr [rbp - 32]
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 40]
lea r12, [r14 + r13]
mov qword ptr [rbp - 40], r12
jmp label44
label44:
mov r12, qword ptr [rbp - 40]
cmp r12, 10
setl r12b
and r12b, 1
test r12b, r12b
jne label43
jmp label45
label45:
mov r12, qword ptr [rbp - 32]
mov r13, qword ptr [rbp - 40]
cmp r12, 8
sete r12b
and r12b, 1
cmp r13, 13
sete r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label46
label46:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopComplexCondition:
label47:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, 3
mov r13, 0
jmp label48
label48:
mov qword ptr [rbp - 64], r13
lea r12, [r13 + 1]
mov qword ptr [rbp - 72], r14
mov qword ptr [rbp - 80], r14
sub qword ptr [rbp - 80], 1
jmp label49
label49:
cmp r12, 3
setl sil
and sil, 1
cmp qword ptr [rbp - 80], 0
setg bl
and bl, 1
mov dil, sil
and dil, bl
cmp dil, 0
setne dil
and dil, 1
test dil, dil
jne label50
jmp label51
label50:
mov r14, qword ptr [rbp - 80]
mov r13, r12
jmp label48
label51:
cmp r12, 3
sete r12b
and r12b, 1
cmp qword ptr [rbp - 80], 0
sete r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label52
label52:
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
label53:
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
jmp label54
label54:
mov qword ptr [rbp - 48], r13
lea r12, [r13 + 1]
cmp r12, 3
sete dil
and dil, 1
test dil, dil
jne label59
jmp label55
label55:
mov rdi, r12
jmp label60
label56:
cmp rdi, 5
setl sil
and sil, 1
test sil, sil
jne label57
jmp label58
label57:
mov r14, r12
mov r13, rdi
jmp label54
label58:
cmp r12, 13
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label61
label59:
mov rdi, 10
jmp label60
label60:
lea r12, [r14 + rdi]
jmp label56
label61:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestDoWhileLoopMultipleExits:
label62:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 0
jmp label63
label63:
mov qword ptr [rbp - 48], r14
lea r13, [r14 + 1]
cmp r13, 5
sete r12b
and r12b, 1
test r12b, r12b
jne label66
jmp label67
label64:
mov r14, r13
jmp label63
label65:
mov cl, r12b
call Assert
mov cl, dil
call Assert
jmp label69
label66:
mov dil, 1
jmp label65
label67:
cmp r13, 10
setg r14b
and r14b, 1
test r14b, r14b
jne label68
jmp label64
label68:
mov dil, 0
jmp label65
label69:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label70:
push rbp
mov rbp, rsp
sub rsp, 32
call TestDoWhileLoopInt
call TestDoWhileLoopBool
call TestNestedDoWhileLoops
call TestDoWhileLoopWithBreak
call TestDoWhileLoopWithContinue
call TestDoWhileLoopBoundary
call TestDoWhileLoopWithMultipleVariables
call TestDoWhileLoopComplexCondition
call TestDoWhileLoopChangingCondition
call TestDoWhileLoopMultipleExits
jmp label71
label71:
mov rax, 0
mov rsp, rbp
pop rbp
ret
