.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 57
mov qword ptr [rbp - 8], r14
mov byte ptr [rbp - 17], 98
mov qword ptr [rbp - 25], 0
jmp label1
label1:
mov r14, qword ptr [rbp - 17]
cmp r14, 97
je label5
cmp r14, 98
je label7
cmp r14, 99
je label9
jmp label2
label2:
mov qword ptr [rbp - 25], 0
jmp label11
label3:
mov r14, qword ptr [rbp - 25]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 16], 0
jmp label11
label4:
label5:
mov qword ptr [rbp - 25], 1
jmp label3
label6:
label7:
mov qword ptr [rbp - 25], 2
jmp label3
label8:
label9:
mov qword ptr [rbp - 25], 3
jmp label3
label10:
label11:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
