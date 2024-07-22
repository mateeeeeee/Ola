.intel_syntax noprefix
.text
.globl main
main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp-8], 5
mov r15, qword ptr [rbp-8]
mov r15, r15
add r15, 2
mov r14, qword ptr [rbp-8]
mov qword ptr [rbp-8], r15
mov r15, qword ptr [rbp-8]
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
