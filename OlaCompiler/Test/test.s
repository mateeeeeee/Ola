.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestShiftOperatorsIntegers:
label0:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 2
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp-24], r14
mov r14, qword ptr [rbp-24]
cmp r14, 20
sete r14b
mov cl, r14b
call Assert
mov r14, qword ptr [rbp-8]
mov r15, qword ptr [rbp-16]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp-32], r15
mov r15, qword ptr [rbp-32]
cmp r15, 1
sete r15b
mov cl, r15b
call Assert
label1:
mov rsp, rbp
pop rbp
ret

TestCompoundShiftOperatorsIntegers:
label2:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 2
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
mov rcx, r14
mov r14, r15
shl r14, cl
mov qword ptr [rbp-8], r14
mov r14, qword ptr [rbp-8]
cmp r14, 20
sete r14b
mov cl, r14b
call Assert
mov r14, qword ptr [rbp-8]
mov r15, qword ptr [rbp-16]
mov rcx, r15
mov r15, r14
sar r15, cl
mov qword ptr [rbp-8], r15
mov r15, qword ptr [rbp-8]
cmp r15, 5
sete r15b
mov cl, r15b
call Assert
label3:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 40
call TestShiftOperatorsIntegers
call TestCompoundShiftOperatorsIntegers
mov qword ptr [rbp-8], 0
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

