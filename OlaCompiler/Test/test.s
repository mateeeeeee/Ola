.intel_syntax noprefix

.section .text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
test 1, 1
jne label1
jmp label3
label1:
mov qword ptr [rbp - 8], 10
jmp label6
label2:
jmp label6
label3:
mov qword ptr [rbp - 8], 15
jmp label6
label4:
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

