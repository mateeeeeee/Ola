.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov qword ptr [rbp - 16], 1
mov qword ptr [rbp - 24], 0
jmp label1
label1:
mov r15, qword ptr [rbp - 16]
cmp r15, 1
je label5
cmp r15, 2
je label6
jmp label2
label2:
mov qword ptr [rbp - 24], 3
jmp label3
label3:
mov r15, qword ptr [rbp - 24]
mov qword ptr [rbp - 8], r15
jmp label9
label4:
jmp label9
label5:
mov qword ptr [rbp - 24], 1
jmp label9
label6:
mov qword ptr [rbp - 24], 2
jmp label3
label7:
jmp label9
label8:
jmp label9
label9:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

