.intel_syntax noprefix

.section .rodata

g:
.quad 9


.section .text

.extern Assert

.extern AssertMsg

ReturnRef:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
lea r15, [rip + g]
mov qword ptr [rbp - 8], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

ReturnValue:
label3:
push rbp
mov rbp, rsp
sub rsp, 8
mov qword ptr [rbp - 8], qword ptr g[rip]
jmp label5
label4:
jmp label5
label5:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

TestRefReturnSimple:
label6:
push rbp
mov rbp, rsp
sub rsp, 80
call ReturnRef
mov r15, rax
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
mov r14, qword ptr [r15]
mov qword ptr [rbp - 16], r14
mov r13, r14
add r13, 1
mov qword ptr [r15], r13
mov r13, qword ptr g[rip]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
call ReturnRef
mov r13, rax
mov r15, qword ptr [r13]
mov qword ptr [rbp - 24], r15
mov r15, qword ptr [rbp - 24]
mov qword ptr [rbp - 32], r15
mov r13, r15
add r13, 1
mov qword ptr [rbp - 24], r13
mov r13, qword ptr g[rip]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
call ReturnValue
mov r13, rax
mov qword ptr [rbp - 40], r13
mov r13, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r13
mov r15, r13
add r15, 1
mov qword ptr [rbp - 40], r15
mov r15, qword ptr g[rip]
cmp r15, 10
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label7
label7:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label8:
push rbp
mov rbp, rsp
sub rsp, 40
call TestRefReturnSimple
mov qword ptr [rbp - 8], 0
jmp label10
label9:
jmp label10
label10:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

