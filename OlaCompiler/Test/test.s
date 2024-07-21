.intel_syntax noprefix
.text
.globl main
main:
push	rbp
mov rbp, rsp
sub rsp, 16
label0:
mov qword ptr [rbp-8], 42
mov r15, qword ptr [rbp-8]
mov qword ptr [rbp], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp]
mov rax, r15
mov	rsp, rbp
pop	rbp
ret
