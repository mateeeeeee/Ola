.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestIfElseBasic:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
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
label6:
mov rcx, 0
call Assert
jmp label8
label7:
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
mov rax, 42
cqo
mov r15, 2
idiv r15
mov r15, rdx
cmp r15, 0
sete r15b
and r15b, 1
test r15b, r15b
jne label14
jmp label15
label14:
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
label22:
label23:
label24:
jmp label37
label25:
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
mov r15b, 1
and r15b, 1
cmp r15b, 0
setne r15b
and r15b, 1
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
jmp label45
label44:
jmp label45
label45:
mov rax, 0
mov rsp, rbp
pop rbp
ret

