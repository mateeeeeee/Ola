.intel_syntax noprefix

.section .rodata

globalString:
.string "global"


__StringLiteral0:
.string "local"


__StringLiteral1:
.string "Literal"


.section .text

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
cmp r15b, 108
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
sub rsp, 54
mov rcx, 1
call Assert
lea r15, qword ptr [rbp - 14]
mov qword ptr [r15], 108
lea r15, qword ptr [rbp - 14]
mov r14, r15
add r14, 1
mov byte ptr [r14], 111
lea r14, qword ptr [rbp - 14]
mov r15, r14
add r15, 2
mov byte ptr [r15], 99
lea r15, qword ptr [rbp - 14]
mov r14, r15
add r14, 3
mov byte ptr [r14], 97
lea r14, qword ptr [rbp - 14]
mov r15, r14
add r15, 4
mov byte ptr [r15], 108
lea r15, qword ptr [rbp - 14]
mov r14, r15
add r14, 5
mov byte ptr [r14], 0
mov rcx, 1
call Assert
lea r14, qword ptr [rbp - 14]
mov qword ptr [rbp - 22], r14
mov r14, qword ptr [rbp - 22]
mov r15, r14
mov r14b, byte ptr [r15]
cmp r14b, 108
sete r14b
mov cl, r14b
call Assert
lea r14, [rip + __StringLiteral1]
mov rcx, r14
call PassStringLiteral__C0
mov rcx, qword ptr [rbp - 14]
call PassStringVariable__C0
mov qword ptr [rbp - 8], 0
jmp label6
label5:
jmp label6
label6:
mov r14, qword ptr [rbp - 8]
mov rax, r14
mov rsp, rbp
pop rbp
ret

