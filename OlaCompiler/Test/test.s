.intel_syntax noprefix
.text
.extern Assert
.extern AssertMsg
.globl main
main:
label0:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp-8], 5
mov r15, qword ptr [rbp-8]
mov r14, r15
add r14, 2
mov qword ptr [rbp-8], r14
mov r14, qword ptr [rbp-8]
mov qword ptr [rbp], r14
jmp label2
label1:
jmp label2
label2:
mov r14, qword ptr [rbp]
mov rax, r14
mov rsp, rbp
pop rbp
ret
