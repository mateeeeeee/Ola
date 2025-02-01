.intel_syntax noprefix

.section .rodata

GlobalIntX:
.quad 2


.section .text

.extern Assert

.extern AssertMsg

TestSwitchBasic:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
jmp label1
label1:
jmp label4
jmp label2
label2:
jmp label6
label3:
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label6
label4:
mov r14, 10
jmp label3
label5:
mov r14, 20
jmp label3
label6:
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
TestSwitchMultipleCases:
label7:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
jmp label8
label8:
jmp label13
jmp label9
label9:
jmp label15
label10:
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label15
label11:
jmp label12
label12:
mov r14, 10
jmp label10
label13:
jmp label14
label14:
mov r14, 20
jmp label10
label15:
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
TestSwitchFallthrough:
label16:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
jmp label17
label17:
mov r14, 0
jmp label21
jmp label18
label18:
jmp label23
label19:
cmp r13, 50
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label23
label20:
mov r14, 10
jmp label21
label21:
mov r13, r14
add r13, 20
mov r14, r13
jmp label22
label22:
mov r13, r14
add r13, 30
jmp label19
label23:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestSwitchWithBreak:
label24:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
jmp label25
label25:
jmp label29
jmp label26
label26:
jmp label31
label27:
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label31
label28:
mov r14, 10
jmp label27
label29:
mov r14, 20
jmp label27
label30:
mov r14, 30
jmp label27
label31:
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
TestSwitchGlobalVariable:
label32:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
jmp label33
label33:
mov r14, qword ptr GlobalIntX[rip]
cmp r14, 1
je label36
cmp r14, 2
je label37
cmp r14, 3
je label38
jmp label34
label34:
jmp label39
label35:
cmp r14, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label39
label36:
mov r14, 1
jmp label35
label37:
mov r14, 2
jmp label35
label38:
mov r14, 3
jmp label35
label39:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestSwitchNoMatch:
label40:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
jmp label41
label41:
jmp label42
label42:
jmp label47
label43:
cmp r14, -1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label47
label44:
mov r14, 1
jmp label43
label45:
mov r14, 2
jmp label43
label46:
mov r14, 3
jmp label43
label47:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label48:
push rbp
mov rbp, rsp
sub rsp, 32
call TestSwitchBasic
call TestSwitchMultipleCases
call TestSwitchFallthrough
call TestSwitchWithBreak
jmp label49
label49:
call TestSwitchGlobalVariable
jmp label50
label50:
call TestSwitchNoMatch
jmp label51
label51:
mov rax, 0
mov rsp, rbp
pop rbp
ret
