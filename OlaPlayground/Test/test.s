.intel_syntax noprefix

.section .rodata

g:
.quad 9


.text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
jmp label3
label1:
mov r13, qword ptr [r14]
mov qword ptr [rbp - 32], r13
mov r12, r13
add r12, 1
mov qword ptr [r14], r12
mov r12, qword ptr g[rip]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label4
label2:
mov r14, qword ptr [rbp - 40]
jmp label1
label3:
lea r14, [rip + g]
mov qword ptr [rbp - 40], r14
jmp label2
label4:
mov rax, 0
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
