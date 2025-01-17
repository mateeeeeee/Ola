.intel_syntax noprefix

.section .text

f__I:
label0:
push rbp
mov rbp, rsp
mov r15, rcx
mov r14, r15
add r14, 5
jmp label2
label1:
label2:
mov rax, r14
mov rsp, rbp
pop rbp
ret

.globl main

main:
label3:
push rbp
mov rbp, rsp
jmp label7
label4:
jmp label9
label5:
jmp label4
label6:
label7:
jmp label5
label8:
label9:
mov rax, 13
mov rsp, rbp
pop rbp
ret

