.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestShortCircuitEvaluation:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
mov r14b, 0
and r14b, 1
cmp r14b, 0
setne r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label2
label1:
mov rcx, 0
call Assert
jmp label3
label2:
mov rcx, 1
call Assert
jmp label3
label3:
mov r14b, 1
or r14b, 1
cmp r14b, 0
setne r14b
and r14b, 1
test r14b, r14b
jne label4
jmp label5
label4:
mov rcx, 1
call Assert
jmp label6
label5:
mov rcx, 0
call Assert
jmp label6
label6:
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
TestIfElseWithBooleanLiterals:
label7:
push rbp
mov rbp, rsp
sub rsp, 32
jmp label8
label8:
mov rcx, 1
call Assert
jmp label9
label9:
mov rcx, 1
call Assert
jmp label10
label10:
mov rsp, rbp
pop rbp
ret
.globl main

main:
label11:
push rbp
mov rbp, rsp
sub rsp, 32
jmp label17
label12:
call TestIfElseWithBooleanLiterals
call TestShortCircuitEvaluation
jmp label18
label13:
mov rcx, 1
call Assert
jmp label12
label14:
mov rcx, 1
call Assert
jmp label13
label15:
mov rcx, 1
call Assert
jmp label14
label16:
mov rcx, 1
call Assert
jmp label15
label17:
mov rcx, 1
call Assert
jmp label16
label18:
mov rax, 0
mov rsp, rbp
pop rbp
ret
