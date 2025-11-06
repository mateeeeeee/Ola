.intel_syntax noprefix

.text

_g:
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
_f:
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
_add__I__I:
label6:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r12
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r14
mov r14, rdi
mov r13, rsi
mov qword ptr [rbp - 32], r14
mov qword ptr [rbp - 40], r13
mov r13, qword ptr [rbp - 32]
mov r14, qword ptr [rbp - 40]
mov r12, r13
add r12, r14
mov qword ptr [rbp - 48], r12
jmp label8
label7:
label8:
mov r12, qword ptr [rbp - 48]
mov rax, r12
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl _main

_main:
label9:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
mov rsi, 3
mov rdi, 5
call _add__I__I
mov r14, rax
mov qword ptr [rbp - 16], r14
jmp label11
label10:
label11:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
