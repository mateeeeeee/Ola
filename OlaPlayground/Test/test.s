.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestForLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 16], 1
mov qword ptr [rbp - 16], 2
mov qword ptr [rbp - 16], 3
mov qword ptr [rbp - 16], 4
mov qword ptr [rbp - 16], 5
jmp label1
label1:
mov cl, 1
call Assert
jmp label2
label2:
mov rsp, rbp
pop rbp
ret
TestForLoopManualIncrement:
label3:
push rbp
mov rbp, rsp
sub rsp, 32
jmp label4
label4:
mov cl, 1
call Assert
jmp label5
label5:
mov rsp, rbp
pop rbp
ret
TestForLoopMultipleExpressions:
label6:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], 1
mov qword ptr [rbp - 16], 5
mov qword ptr [rbp - 8], 2
mov qword ptr [rbp - 16], 4
mov qword ptr [rbp - 8], 3
mov qword ptr [rbp - 16], 3
jmp label7
label7:
mov cl, 1
call Assert
jmp label8
label8:
mov rsp, rbp
pop rbp
ret
TestNestedForLoops:
label9:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 32], 0
mov qword ptr [rbp - 40], 0
mov qword ptr [rbp - 48], 0
jmp label11
label10:
jmp label15
label11:
mov r14, qword ptr [rbp - 32]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label10
jmp label13
label12:
mov r14, qword ptr [rbp - 32]
mov qword ptr [rbp - 56], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 32], r13
jmp label11
label13:
mov r14, qword ptr [rbp - 32]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label18
label14:
mov r13, qword ptr [rbp - 48]
mov r14, r13
add r14, 1
mov qword ptr [rbp - 48], r14
jmp label16
label15:
mov r14, qword ptr [rbp - 40]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label14
jmp label17
label16:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 64], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label15
label17:
jmp label12
label18:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestNestedForLoopsReset:
label19:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], 0
mov qword ptr [rbp - 32], 0
jmp label21
label20:
mov qword ptr [rbp - 40], 0
jmp label25
label21:
mov r14, qword ptr [rbp - 24]
cmp r14, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label20
jmp label23
label22:
mov r14, qword ptr [rbp - 24]
mov qword ptr [rbp - 48], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 24], r13
jmp label21
label23:
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
jmp label28
label24:
mov r13, qword ptr [rbp - 32]
mov qword ptr [rbp - 56], r13
mov r14, r13
add r14, 1
mov qword ptr [rbp - 32], r14
jmp label26
label25:
mov r14, qword ptr [rbp - 40]
cmp r14, 2
setl r14b
and r14b, 1
test r14b, r14b
jne label24
jmp label27
label26:
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 64], r14
mov r13, r14
add r13, 1
mov qword ptr [rbp - 40], r13
jmp label25
label27:
jmp label22
label28:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestForLoopWithBreak:
label29:
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
jmp label31
label30:
mov rdi, r13
add rdi, r14
cmp r14, 3
sete sil
and sil, 1
test sil, sil
jne label34
jmp label32
label31:
cmp r14, 5
setle r12b
and r12b, 1
test r12b, r12b
jne label30
mov r12, r13
jmp label33
label32:
mov qword ptr [rbp - 48], r14
mov rsi, r14
add rsi, 1
mov r14, rsi
mov r13, rdi
jmp label31
label33:
cmp r12, 6
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label35
label34:
mov r12, rdi
jmp label33
label35:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestForLoopWithContinue:
label36:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 16], 1
mov qword ptr [rbp - 16], 2
mov qword ptr [rbp - 16], 3
mov qword ptr [rbp - 16], 4
mov qword ptr [rbp - 16], 5
jmp label37
label37:
mov cl, 0
call Assert
jmp label38
label38:
mov rsp, rbp
pop rbp
ret
TestForLoopEmptyBody:
label39:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 16], 0
mov qword ptr [rbp - 16], 1
mov qword ptr [rbp - 16], 2
mov qword ptr [rbp - 16], 3
mov qword ptr [rbp - 16], 4
jmp label40
label40:
mov cl, 1
call Assert
mov cl, 1
call Assert
jmp label41
label41:
mov rsp, rbp
pop rbp
ret
.globl main

main:
label42:
push rbp
mov rbp, rsp
sub rsp, 32
call TestForLoopInt
call TestForLoopManualIncrement
call TestForLoopMultipleExpressions
call TestNestedForLoops
call TestNestedForLoopsReset
call TestForLoopWithBreak
call TestForLoopWithContinue
call TestForLoopEmptyBody
jmp label43
label43:
mov rax, 0
mov rsp, rbp
pop rbp
ret
