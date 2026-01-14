.intel_syntax noprefix

.text

compute__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, rdx
mov r12, r14
imul r12, r13
lea r13, [r12 + 10]
cmp r14, 0
setg r14b
and r14b, 1
test r14b, r14b
jne label1
jmp label2
label1:
lea r14, [r13 + r13]
mov r13, r14
jmp label3
label2:
mov r13, 0
jmp label3
label3:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov rdx, 3
mov rcx, 5
call compute__I__I
mov r14, rax
mov rdx, 4
mov rcx, -1
call compute__I__I
mov r13, rax
lea r12, [r14 + r13]
jmp label5
label5:
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
