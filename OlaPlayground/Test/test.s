.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestForLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 1
mov r13, 0
jmp label2
label1:
mov r12, r13
add r12, r14
jmp label3
label2:
cmp r14, 5
setle r12b
and r12b, 1
test r12b, r12b
jne label1
jmp label4
label3:
mov qword ptr [rbp - 40], r14
mov rdi, r14
add rdi, 1
mov r14, rdi
mov r13, r12
jmp label2
label4:
cmp r13, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestForLoopBoolCondition:
label6:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, 0
jmp label8
label7:
mov qword ptr [rbp - 24], r14
mov r13, r14
add r13, 1
jmp label9
label8:
cmp r14, 3
setl r13b
and r13b, 1
test r13b, r13b
jne label7
jmp label10
label9:
mov r14, r13
jmp label8
label10:
cmp r14, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label11
label11:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestForLoopMultipleExpressions:
label12:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, 5
mov r13, 1
mov r12, 0
jmp label14
label13:
mov rdi, r13
add rdi, r14
mov rsi, r12
add rsi, rdi
jmp label15
label14:
cmp r13, 3
setle dil
and dil, 1
test dil, dil
jne label13
jmp label16
label15:
mov qword ptr [rbp - 56], r13
mov rdi, r13
add rdi, 1
mov qword ptr [rbp - 64], r14
mov rbx, r14
sub rbx, 1
mov r14, rbx
mov r13, rdi
mov r12, rsi
jmp label14
label16:
cmp r12, 18
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label17
label17:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestNestedForLoops:
label18:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 0
mov r13, 0
jmp label20
label19:
mov r12, r14
jmp label23
label20:
cmp r13, 3
setl r12b
and r12b, 1
test r12b, r12b
jne label19
jmp label22
label21:
mov qword ptr [rbp - 40], r13
mov rdi, r13
add rdi, 1
mov r14, r12
mov r13, rdi
jmp label20
label22:
cmp r13, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
cmp r14, 2
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label25
label23:
cmp r12, 2
setl dil
and dil, 1
test dil, dil
jne label24
jmp label21
label24:
mov qword ptr [rbp - 48], r12
mov rdi, r12
add rdi, 1
mov r12, rdi
jmp label23
label25:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestForLoopWithBreak:
label26:
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
jmp label28
label27:
mov rdi, r13
add rdi, r14
cmp r14, 3
sete sil
and sil, 1
test sil, sil
jne label31
jmp label29
label28:
cmp r14, 5
setle r12b
and r12b, 1
test r12b, r12b
jne label27
mov r12, r13
jmp label30
label29:
mov qword ptr [rbp - 48], r14
mov rsi, r14
add rsi, 1
mov r14, rsi
mov r13, rdi
jmp label28
label30:
cmp r12, 6
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label32
label31:
mov r12, rdi
jmp label30
label32:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestForLoopWithContinue:
label33:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 1
mov r13, 0
jmp label35
label34:
cmp r14, 3
sete r12b
and r12b, 1
test r12b, r12b
jne label38
jmp label39
label35:
cmp r14, 5
setle r12b
and r12b, 1
test r12b, r12b
jne label34
jmp label37
label36:
mov qword ptr [rbp - 40], r14
mov r12, r14
add r12, 1
mov r14, r12
mov r13, rdi
jmp label35
label37:
cmp r13, 12
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label40
label38:
mov rdi, r13
jmp label36
label39:
mov r12, r13
add r12, r14
mov rdi, r12
jmp label36
label40:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label41:
push rbp
mov rbp, rsp
sub rsp, 32
call TestForLoopInt
call TestForLoopBoolCondition
call TestForLoopMultipleExpressions
call TestNestedForLoops
call TestForLoopWithBreak
call TestForLoopWithContinue
jmp label42
label42:
mov rax, 0
mov rsp, rbp
pop rbp
ret
