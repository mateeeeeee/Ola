.intel_syntax noprefix
.text
.globl main
main:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp-8], 42
mov qword ptr [rbp-16], 14
mov r15, qword ptr [rbp-8]
mov r14, qword ptr [rbp-16]
mov r15, r15
sub r15, r14
mov r15, r15
add r15, 22
mov qword ptr [rbp-24], r15
mov r15, qword ptr [rbp-24]
mov r15, r15
sub r15, 25
mov qword ptr [rbp], r15
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp]
mov rax, r15
mov rsp, rbp
pop rbp
ret
