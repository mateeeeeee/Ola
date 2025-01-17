.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

f:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
jmp label2
label1:
label2:
mov rax, 24
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
sub rsp, 24
jmp label9
jmp label7
label4:
label5:
label6:
label7:
label8:
label9:
mov rax, 24
mov rsp, rbp
pop rbp
ret

