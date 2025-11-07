.intel_syntax noprefix

.section .rdata

g:
.quad 9


.text

.extern Assert

.extern AssertMsg

.extern PrintInt

.extern PrintFloat

.extern PrintChar

.extern PrintString

.extern ReadInt

.extern ReadFloat

.extern ReadChar

.extern ReadString

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
jmp label3
label1:
mov r13, qword ptr [r14]
mov qword ptr [rbp - 32], r13
mov r13, qword ptr g[rip]
mov qword ptr [rbp - 24], r13
jmp label4
label2:
mov r14, qword ptr [rbp - 40]
jmp label1
label3:
lea r14, [rip + g]
mov qword ptr [rbp - 40], r14
jmp label2
label4:
mov r13, qword ptr [rbp - 24]
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
