.intel_syntax noprefix
.text
.globl main
main:
push	rbp
mov rbp, rsp
sub rsp, 16
label0:
mov qword ptr [rbp+8], 42
mov qword ptr [rbp+0], r15
jmp label2
label1:
jmp label2
label2:
mov rax, r14
add rsp, 16
mov	rsp, rbp
pop	rbp
ret
