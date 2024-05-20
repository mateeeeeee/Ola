.intel_syntax noprefix
.text
.globl main
main:
label0:
mov qword ptr [rbp+0], 5
jmp label2
label1:
jmp label2
label2:
mov rax, r15
ret
