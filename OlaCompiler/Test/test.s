.intel_syntax noprefix

.section .rodata

__StringLiteral0:
.string "m"


__StringLiteral1:
.string "12345"


.section .text

.extern Assert

.extern AssertMsg

.extern PrintInt

.extern PrintFloat

.extern PrintChar

.extern PrintString

.extern ReadInt

.extern ReadFloat

.extern ReadChar

.extern ReadString

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

PassStringLiteral__C0:
label0:
push rbp
mov rbp, rsp
sub rsp, 40
mov r15, rcx
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
mov r14, r15
mov r15b, byte ptr [r14]
cmp r15b, 76
sete r15b
mov cl, r15b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

PassStringVariable__C0:
label2:
push rbp
mov rbp, rsp
sub rsp, 40
mov r15, rcx
mov qword ptr [rbp - 8], r15
mov r15, qword ptr [rbp - 8]
mov r14, r15
mov r15b, byte ptr [r14]
cmp r15b, 86
sete r15b
mov cl, r15b
call Assert
jmp label3
label3:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 64
lea r15, qword ptr [rbp - 10]
mov qword ptr [r15], 109
lea r15, qword ptr [rbp - 10]
mov r14, r15
add r14, 2
mov byte ptr [r14], 0
lea r14, qword ptr [rbp - 10]
mov qword ptr [rbp - 18], r14
mov r14, qword ptr [rbp - 18]
mov r15, r14
mov r14b, byte ptr [r15]
cmp r14b, 109
sete r14b
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 24]
mov qword ptr [r14], 49
lea r14, qword ptr [rbp - 24]
mov r15, r14
add r15, 6
mov byte ptr [r15], 50
lea r15, qword ptr [rbp - 24]
mov r14, r15
add r14, 12
mov byte ptr [r14], 51
lea r14, qword ptr [rbp - 24]
mov r15, r14
add r15, 18
mov byte ptr [r15], 52
lea r15, qword ptr [rbp - 24]
mov r14, r15
add r14, 24
mov byte ptr [r14], 53
lea r14, qword ptr [rbp - 24]
mov r15, r14
add r15, 30
mov byte ptr [r15], 0
mov rcx, qword ptr [rbp - 24]
call StringToInt
mov r15, rax
mov qword ptr [rbp - 32], r15
mov r15, qword ptr [rbp - 32]
cmp r15, 12345
sete r15b
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 0
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

