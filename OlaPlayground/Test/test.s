.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestWhileLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov r15, 1
mov r13, 0
jmp label1
label1:
cmp r15, 5
setle r14b
and r14b, 1
test r14b, r14b
jne label2
jmp label3
label2:
mov r13, r14
mov r15, r13
mov r14, r13
add r14, r15
mov r13, r15
add r13, 1
jmp label1
label3:
cmp r14, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label4
label4:
mov rsp, rbp
pop rbp
ret

TestWhileLoopBool:
label5:
push rbp
mov rbp, rsp
sub rsp, 49
mov r13, 0
mov r15b, 1
jmp label6
label6:
test r15b, r15b
jne label7
jmp label8
label7:
mov r14, r13
add r14, 1
cmp r14, 3
sete r13b
and r13b, 1
test r13b, r13b
jne label9
mov r15b, r15b
jmp label11
label8:
cmp r14, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label12
label9:
mov r15b, 0
jmp label11
label10:
jmp label12
label11:
mov r15b, r15b
mov r13, r14
jmp label6
label12:
mov rsp, rbp
pop rbp
ret

TestNestedWhileLoops:
label13:
push rbp
mov rbp, rsp
sub rsp, 64
mov r14, 0
mov r15, 0
jmp label14
label14:
cmp r15, 3
setl r14b
and r14b, 1
test r14b, r14b
jne label15
jmp label16
label15:
mov r14, r14
jmp label17
label16:
cmp r13, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
cmp r14, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label20
label17:
cmp r14, 2
setl r13b
and r13b, 1
test r13b, r13b
jne label18
jmp label19
label18:
mov r14, r13
mov r13, r14
add r13, 1
jmp label17
label19:
mov r15, r13
mov r14, r13
mov r13, r15
add r13, 1
jmp label14
label20:
mov rsp, rbp
pop rbp
ret

TestWhileLoopWithBreak:
label21:
push rbp
mov rbp, rsp
sub rsp, 56
mov r14, 1
mov r14, 0
jmp label22
label22:
jmp label23
label23:
mov r15, r14
add r15, r14
mov r13, r14
add r13, 1
cmp r13, 5
setg r14b
and r14b, 1
test r14b, r14b
jne label25
jmp label27
label24:
cmp r15, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label29
label25:
jmp label24
label26:
jmp label29
label27:
mov r14, r15
mov r14, r13
jmp label22
label28:
jmp label29
label29:
mov rsp, rbp
pop rbp
ret

TestWhileLoopWithContinue:
label30:
push rbp
mov rbp, rsp
jmp label31
label31:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label32:
push rbp
mov rbp, rsp
sub rsp, 40
call TestWhileLoopInt
call TestWhileLoopBool
call TestNestedWhileLoops
call TestWhileLoopWithBreak
call TestWhileLoopWithContinue
jmp label34
label33:
jmp label34
label34:
mov rax, 0
mov rsp, rbp
pop rbp
ret

