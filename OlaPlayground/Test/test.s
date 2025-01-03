.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
jmp label1
label1:
jmp label7
jmp label2
label2:
jmp label9
label3:
mov r15, 0
jmp label9
label4:
label5:
mov rcx, 0
call Assert
jmp label3
label6:
label7:
mov rcx, 1
call Assert
jmp label3
label8:
label9:
mov rax, r15
mov rsp, rbp
pop rbp
ret

