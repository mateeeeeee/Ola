.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

IntByRef__Iref:
label0:
push rbp
mov rbp, rsp
sub rsp, 8
mov r15, rcx
mov r14, qword ptr [r15]
mov r13, r14
add r13, 1
mov qword ptr [r15], r13
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 48
lea rcx, qword ptr [rbp - 16]
call IntByRef__Iref
mov rcx, 0
call Assert
jmp label4
label3:
jmp label4
label4:
mov rax, 0
mov rsp, rbp
pop rbp
ret

