.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestLessThanOperators:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setg r14b
mov cl, r14b
call Assert
label1:
mov rsp, rbp
pop rbp
ret

TestLessThanOrEqualOperators:
label2:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setle r14b
mov cl, r14b
call Assert
label3:
mov rsp, rbp
pop rbp
ret

TestGreaterThanOperators:
label4:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setg r14b
cmp r14b, 0
sete r14b
mov cl, r14b
call Assert
label5:
mov rsp, rbp
pop rbp
ret

TestGreaterThanOrEqualOperators:
label6:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setge r14b
cmp r14b, 0
sete r14b
mov cl, r14b
call Assert
label7:
mov rsp, rbp
pop rbp
ret

TestEqualOperators:
label8:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
sete r14b
cmp r14b, 0
sete r14b
mov cl, r14b
call Assert
label9:
mov rsp, rbp
pop rbp
ret

TestNotEqualOperators:
label10:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp-8], 5
mov qword ptr [rbp-16], 10
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
cmp r15, r14
setne r14b
cmp r14b, 1
sete r14b
mov cl, r14b
call Assert
label11:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label12:
push rbp
mov rbp, rsp
sub rsp, 40
call TestLessThanOperators
call TestLessThanOrEqualOperators
call TestGreaterThanOperators
call TestGreaterThanOrEqualOperators
call TestEqualOperators
call TestNotEqualOperators
mov qword ptr [rbp-8], 0
jmp label14
label13:
jmp label14
label14:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

