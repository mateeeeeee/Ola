.intel_syntax noprefix

.section .rodata

global_int_1:
.quad 5


global_int_2:
.quad 10


global_int_3:
.quad 7


global_int_4:
.quad 20


.section .text

.extern Assert

.extern AssertMsg

TestIntAddition:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r15, qword ptr global_int_1[rip]
mov r14, qword ptr global_int_2[rip]
mov r13, r15
add r13, r14
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_int_1[rip]
mov r14, r13
add r14, 10
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_int_3[rip]
mov r13, r14
add r13, 5
cmp r13, 12
sete r13b
and r13b, 1
mov cl, r13b
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
sub rsp, 32
jmp label5
label3:
jmp label7
label4:
jmp label3
label5:
mov rcx, 1
call Assert
mov rcx, 1
call Assert
mov r15, qword ptr global_int_1[rip]
mov r14, qword ptr global_int_2[rip]
mov r13, r15
add r13, r14
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_int_1[rip]
mov r14, r13
add r14, 10
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_int_3[rip]
mov r13, r14
add r13, 5
cmp r13, 12
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label4
label6:
label7:
mov rax, 0
mov rsp, rbp
pop rbp
ret

