.intel_syntax noprefix

.data

globalString:
.string "global"


.text

.extern Assert

.extern AssertMsg

.extern IsAlnum

.extern IsAlpha

.extern IsLower

.extern IsUpper

.extern IsDigit

.extern IsSpace

.extern ToLower

.extern ToUpper

.extern StringToFloat

.extern StringToInt

.extern StringCopy

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov rcx, 1
call Assert
lea r15, [rip + globalString]
mov r14, r15
mov r15, 0
imul r15, 7
mov r13, r14
add r13, r15
mov r15, 0
imul r15, 1
mov r14, r13
add r14, r15
mov r15b, qword ptr [r14]
cmp r15b, 103
sete r15b
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 0
jmp label2
label1:
jmp label2
label2:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

