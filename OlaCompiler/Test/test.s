.intel_syntax noprefix

.section .rodata

globalString:
.string "global"


__StringLiteral0:
.string "local"


__StringLiteral1:
.string "Literal"


__StringLiteral2:
.string "12345"


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
sub rsp, 68
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
lea rcx, qword ptr [rbp - 14]
call PassStringVariable__C0
lea r14, qword ptr [rbp - 28]
mov qword ptr [r14], 49
lea r14, qword ptr [rbp - 28]
mov r15, r14
add r15, 1
mov byte ptr [r15], 50
lea r15, qword ptr [rbp - 28]
mov r14, r15
add r14, 2
mov byte ptr [r14], 51
lea r14, qword ptr [rbp - 28]
mov r15, r14
add r15, 3
mov byte ptr [r15], 52
lea r15, qword ptr [rbp - 28]
mov r14, r15
add r14, 4
mov byte ptr [r14], 53
lea r14, qword ptr [rbp - 28]
mov r15, r14
add r15, 5
mov byte ptr [r15], 0
lea rcx, qword ptr [rbp - 28]
call StringToInt
mov r15, rax
mov qword ptr [rbp - 36], r15
mov r15, qword ptr [rbp - 36]
cmp r15, 12345
sete r15b
mov cl, r15b
call Assert
mov r15, qword ptr [rbp - 36]
mov qword ptr [rbp - 8], r15
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

