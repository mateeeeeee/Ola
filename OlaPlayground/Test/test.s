.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestIfElseBasic:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
jmp label1
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
jmp label7
label6:
mov rcx, 0
call Assert
jmp label8
label7:
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
jmp label14
label14:
jmp label17
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
jmp label22
label22:
jmp label25
label23:
jmp label32
label24:
jmp label37
label25:
jmp label28
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
jmp label34
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
jmp label39
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
jmp label45
label44:
jmp label45
label45:
mov rax, 0
mov rsp, rbp
pop rbp
ret

