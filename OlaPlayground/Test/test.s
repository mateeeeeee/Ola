.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestWhile:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 0
jmp label1
label1:
cmp r14, 10
setl r13b
and r13b, 1
test r13b, r13b
jne label2
jmp label3
label2:
cmp r14, 5
sete r12b
and r12b, 1
test r12b, r12b
jne label4
jmp label5
label3:
mov r13, 0
jmp label6
label4:
mov r12, r14
add r12, r14
mov r13, r12
jmp label6
label5:
mov r12, r14
add r12, 1
mov r14, r12
jmp label1
label6:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestEarlyReturnInLoop:
label7:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 0
jmp label9
label8:
cmp r14, 5
sete r12b
and r12b, 1
test r12b, r12b
jne label12
jmp label10
label9:
cmp r14, 10
setl r13b
and r13b, 1
test r13b, r13b
jne label8
jmp label11
label10:
mov qword ptr [rbp - 32], r14
mov r12, r14
add r12, 1
mov r14, r12
jmp label9
label11:
mov r13, -1
jmp label13
label12:
mov r13, r14
jmp label13
label13:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestNestedReturn:
label14:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 0
jmp label16
label15:
cmp r14, 1
sete r12b
and r12b, 1
test r12b, r12b
jne label19
jmp label17
label16:
cmp r14, 3
setl r13b
and r13b, 1
test r13b, r13b
jne label15
jmp label18
label17:
mov qword ptr [rbp - 40], r14
mov r12, r14
add r12, 1
mov r14, r12
jmp label16
label18:
mov r13, -1
jmp label24
label19:
mov r12, 0
jmp label21
label20:
cmp r12, 1
sete dil
and dil, 1
test dil, dil
jne label23
jmp label22
label21:
cmp r12, 2
setl dil
and dil, 1
test dil, dil
jne label20
jmp label17
label22:
mov qword ptr [rbp - 48], r12
mov rdi, r12
add rdi, 1
mov r12, rdi
jmp label21
label23:
mov rdi, r14
imul rdi, r12
mov r13, rdi
jmp label24
label24:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestVoidWithEarlyReturn:
label25:
push rbp
mov rbp, rsp
sub rsp, 72
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, 1
mov r13, 0
jmp label27
label26:
mov r12, r13
add r12, r14
cmp r12, 30
setg dil
and dil, 1
test dil, dil
jne label30
jmp label28
label27:
cmp r14, 10
setle r12b
and r12b, 1
test r12b, r12b
jne label26
jmp label29
label28:
mov qword ptr [rbp - 40], r14
mov rdi, r14
add rdi, 1
mov r14, rdi
mov r13, r12
jmp label27
label29:
mov rcx, 0
call Assert
jmp label31
label30:
jmp label31
label31:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label32:
push rbp
mov rbp, rsp
sub rsp, 40
mov qword ptr [rbp - 8], r14
jmp label33
label33:
mov rcx, 1
call Assert
call TestWhile
mov r14, rax
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label34
label34:
mov rcx, 1
call Assert
call TestEarlyReturnInLoop
mov r14, rax
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
call TestNestedReturn
mov r14, rax
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
call TestVoidWithEarlyReturn
jmp label35
label35:
mov rax, 0
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
