.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestIfElseBasic:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 10
mov qword ptr [rbp-16], 20
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setl r14b
test r14b, r14b
jne label1
jmp label2
label1:
mov rcx, 1
call Assert
jmp label3
label2:
mov rcx, 0
call Assert
jmp label3
label3:
jmp label4
label4:
mov rsp, rbp
pop rbp
ret

TestIfElseMultipleConditions:
label5:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 5
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setg r14b
test r14b, r14b
jne label6
jmp label7
label6:
mov rcx, 0
call Assert
jmp label8
label7:
mov r14, qword ptr [rbp-8]
mov r15, qword ptr [rbp-16]
cmp r14, r15
setl r15b
test r15b, r15b
jne label9
jmp label10
label8:
jmp label12
label9:
mov rcx, 0
call Assert
jmp label11
label10:
mov rcx, 1
call Assert
jmp label11
label11:
jmp label8
label12:
mov rsp, rbp
pop rbp
ret

TestNestedIfElse:
label13:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp-8], 42
mov r15, qword ptr [rbp-8]
cmp r15, 21
setg r15b
test r15b, r15b
jne label14
jmp label15
label14:
mov r15, qword ptr [rbp-8]
cmp r15, 0
setg r15b
test r15b, r15b
jne label17
jmp label18
label15:
mov rcx, 0
call Assert
jmp label16
label16:
jmp label20
label17:
mov rcx, 1
call Assert
jmp label19
label18:
mov rcx, 0
call Assert
jmp label19
label19:
jmp label16
label20:
mov rsp, rbp
pop rbp
ret

TestComplexNestedIfElse:
label21:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp-8], 1
mov qword ptr [rbp-16], 5
mov qword ptr [rbp-24], 5
mov r15, qword ptr [rbp-8]
cmp r15, 0
setg r15b
test r15b, r15b
jne label22
jmp label23
label22:
mov r15, qword ptr [rbp-16]
cmp r15, 10
setl r15b
test r15b, r15b
jne label25
jmp label26
label23:
mov r15, qword ptr [rbp-16]
cmp r15, 0
sete r15b
test r15b, r15b
jne label31
jmp label32
label24:
jmp label37
label25:
mov r15, qword ptr [rbp-24]
cmp r15, 5
sete r15b
test r15b, r15b
jne label28
jmp label29
label26:
mov rcx, 0
call Assert
jmp label27
label27:
jmp label24
label28:
mov rcx, 1
call Assert
jmp label30
label29:
mov rcx, 0
call Assert
jmp label30
label30:
jmp label27
label31:
mov rcx, 0
call Assert
jmp label33
label32:
mov r15, qword ptr [rbp-24]
cmp r15, 0
setg r15b
test r15b, r15b
jne label34
jmp label35
label33:
jmp label24
label34:
mov rcx, 0
call Assert
jmp label36
label35:
mov rcx, 0
call Assert
jmp label36
label36:
jmp label33
label37:
mov rsp, rbp
pop rbp
ret

TestIfElseLogicalOperators:
label38:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp-8], 15
mov r15, qword ptr [rbp-8]
cmp r15, 10
setg r15b
test r15b, r15b
jne label39
jmp label40
label39:
mov rcx, 1
call Assert
jmp label41
label40:
mov rcx, 0
call Assert
jmp label41
label41:
jmp label42
label42:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label43:
push rbp
mov rbp, rsp
sub rsp, 40
call TestIfElseBasic
call TestIfElseMultipleConditions
call TestNestedIfElse
call TestComplexNestedIfElse
call TestIfElseLogicalOperators
mov qword ptr [rbp-8], 0
jmp label45
label44:
jmp label45
label45:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

