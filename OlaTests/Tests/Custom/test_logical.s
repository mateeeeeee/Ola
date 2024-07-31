.intel_syntax noprefix

.text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
mov qword ptr [rbp-8], 0
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

