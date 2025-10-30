.intel_syntax noprefix

.section .text

g:
label0:
push rbp
mov rbp, rsp
sub rsp, 9
mov qword ptr [rbp - 8], r14
mov byte ptr [rbp - 9], 1
jmp label2
label1:
label2:
mov r14b, byte ptr [rbp - 9]
mov al, r14b
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
f:
label3:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], 5
jmp label5
label4:
label5:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label6:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
call f
mov r14, rax
call f
mov r13, rax
mov r12, r13
imul r12, 2
mov r13, r14
add r13, r12
call g
mov r12b, al
movzx r14, r12b
cmp r14, 0
setg r14b
and r14b, 1
test r14b, r14b
jne label7
jmp label8
label7:
mov r12, r13
mov r14, r13
jmp label9
label8:
mov r14, r13
mov r14, r13
jmp label9
label9:
mov r12, r14
add r12, r13
jmp label11
label10:
label11:
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
