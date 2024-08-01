.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

TestSizeofTypes:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
cmp 8, 8
sete r15b
mov cl, r15b
call Assert
cmp 8, 8
sete r15b
mov cl, r15b
call Assert
cmp 1, 1
sete r15b
mov cl, r15b
call Assert
label1:
mov rsp, rbp
pop rbp
ret

TestSizeofExpressions:
label2:
push rbp
mov rbp, rsp
sub rsp, 41
mov qword ptr [rbp-8], 42
mov byte ptr [rbp-9], 1
cmp 8, 8
sete r15b
mov cl, r15b
call Assert
cmp 1, 1
sete r15b
mov cl, r15b
call Assert
label3:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label4:
push rbp
mov rbp, rsp
sub rsp, 40
call TestSizeofTypes
call TestSizeofExpressions
mov qword ptr [rbp-8], 0
jmp label6
label5:
jmp label6
label6:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

