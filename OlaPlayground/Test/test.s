.intel_syntax noprefix

.section .text

.extern Assert

.extern AssertMsg

TestDoWhileLoopInt:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov r14, 1
mov r14, 0
jmp label1
label1:
mov r15, r14
add r15, r14
mov r13, r14
add r13, 1
jmp label2
label2:
mov r14, r15
mov r14, r13
cmp r13, 5
setle r13b
and r13b, 1
test r13b, r13b
jne label1
jmp label3
label3:
cmp r15, 15
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label4
label4:
mov rsp, rbp
pop rbp
ret

TestDoWhileLoopBool:
label5:
push rbp
mov rbp, rsp
sub rsp, 49
mov r14, 0
mov r14b, 1
jmp label6
label6:
mov r15, r14
add r15, 1
cmp r15, 3
sete r14b
and r14b, 1
test r14b, r14b
jne label9
mov r14b, r14b
jmp label11
label7:
mov r14b, r14b
mov r14, r15
test r14b, r14b
jne label6
jmp label8
label8:
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label12
label9:
mov r14b, 0
jmp label11
label10:
jmp label12
label11:
jmp label7
label12:
mov rsp, rbp
pop rbp
ret

TestNestedDoWhileLoops:
label13:
push rbp
mov rbp, rsp
sub rsp, 64
mov r15, 0
mov r14, 0
jmp label14
label14:
mov r14, r15
jmp label17
label15:
mov r14, r15
mov r15, r15
cmp r15, 3
setl r15b
and r15b, 1
test r15b, r15b
jne label14
jmp label16
label16:
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
cmp r15, 4
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label20
label17:
mov r15, r14
add r15, 1
jmp label18
label18:
mov r14, r15
cmp r15, 2
setl r15b
and r15b, 1
test r15b, r15b
jne label17
jmp label19
label19:
mov r15, r14
add r15, 1
jmp label15
label20:
mov rsp, rbp
pop rbp
ret

TestDoWhileLoopWithBreak:
label21:
push rbp
mov rbp, rsp
sub rsp, 56
mov r14, 1
mov r14, 0
jmp label22
label22:
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
label23:
mov r14, r15
mov r14, r13
jmp label22
label24:
cmp r15, 15
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label29
label25:
jmp label24
label26:
jmp label29
label27:
jmp label23
label28:
jmp label29
label29:
mov rsp, rbp
pop rbp
ret

TestDoWhileLoopWithContinue:
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
call TestDoWhileLoopInt
call TestDoWhileLoopBool
call TestNestedDoWhileLoops
call TestDoWhileLoopWithBreak
call TestDoWhileLoopWithContinue
jmp label34
label33:
jmp label34
label34:
mov rax, 0
mov rsp, rbp
pop rbp
ret

