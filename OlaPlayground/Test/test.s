.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
jmp label4
label1:
jmp label6
label2:
jmp label1
label3:
label4:
jmp label2
label5:
label6:
mov rax, 13
mov rsp, rbp
pop rbp
ret

