.intel_syntax noprefix

.section .text

f:
label0:
jmp label1
label1:
mov al, 1
ret
.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 49
mov qword ptr [rbp - 8], r14
call f
mov r14b, al
mov byte ptr [rbp - 17], r14b
mov r14b, byte ptr [rbp - 17]
test r14b, r14b
jne label3
jmp label6
label3:
mov qword ptr [rbp - 16], 5
jmp label8
label4:
label5:
label6:
mov qword ptr [rbp - 16], 10
jmp label8
label7:
label8:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
