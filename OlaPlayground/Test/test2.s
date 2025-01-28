.intel_syntax noprefix

.section .text

.globl add__I__I

add__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, rdx
mov r12, r14
add r12, r13
jmp label1
label1:
mov rax, r12
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
