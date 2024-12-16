.intel_syntax noprefix

.section .rodata

GlobalIntX:
.quad 20


GlobalIntY:
.quad 4


GlobalFloatX:
.quad 4620130267728707584


GlobalFloatY:
.quad 4612811918334230528


.section .text

.extern Assert

.extern AssertMsg

TestModulo:
label0:
push rbp
mov rbp, rsp
sub rsp, 88
mov r15, 17
and r15, 3
cmp r15, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntY[rip]
mov rax, 17
cqo
idiv r15
mov r15, rdx
cmp r15, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov rax, 17
cqo
mov r15, 3
idiv r15
mov r15, rdx
cmp r15, 2
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r15, qword ptr GlobalIntX[rip]
mov r14, qword ptr GlobalIntY[rip]
mov rax, r15
cqo
idiv r14
mov r14, rdx
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr GlobalIntX[rip]
mov rax, r14
cqo
mov r14, 3
idiv r14
mov r14, rdx
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov rax, 10
cqo
mov r14, 3
idiv r14
mov r14, rdx
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov rax, 17
cqo
mov r14, 3
idiv r14
mov r14, rdx
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 40
call TestModulo
jmp label4
label3:
jmp label4
label4:
mov rax, 0
mov rsp, rbp
pop rbp
ret

