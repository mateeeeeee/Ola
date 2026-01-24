.intel_syntax noprefix

.text

.extern Assert

.extern AssertMsg

.globl Base$GetX

Base$GetX:
label0:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label1
label1:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Base$GetSum

Base$GetSum:
label2:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
jmp label4
label3:
mov r13, qword ptr [rbp - 32]
jmp label5
label4:
lea r12, [r14]
mov r14, qword ptr [r12]
mov qword ptr [rbp - 32], r14
jmp label3
label5:
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl Derived$GetY

Derived$GetY:
label6:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label7
label7:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Derived$GetSum

Derived$GetSum:
label8:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, rcx
jmp label11
label9:
mov rcx, r14
call Base$GetSum
mov r12, rax
lea rdi, [r13 + r12]
jmp label12
label10:
mov r13, qword ptr [rbp - 48]
jmp label9
label11:
lea r12, [r14 + 8]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 48], r13
jmp label10
label12:
mov rax, rdi
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl ExtendedDerived$GetZ

ExtendedDerived$GetZ:
label13:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label14
label14:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl ExtendedDerived$GetSum

ExtendedDerived$GetSum:
label15:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, rcx
jmp label18
label16:
mov rcx, r14
call Derived$GetSum
mov r12, rax
lea rdi, [r13 + r12]
jmp label19
label17:
mov r13, qword ptr [rbp - 48]
jmp label16
label18:
lea r12, [r14 + 16]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 48], r13
jmp label17
label19:
mov rax, rdi
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
PassBase__Base:
label20:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, qword ptr [r14]
lea r14, qword ptr [rbp - 48]
mov qword ptr [r14], r13
lea r14, qword ptr [rbp - 48]
lea r13, qword ptr [rbp - 32]
mov r12, qword ptr [r14]
mov qword ptr [r13], r12
jmp label23
label21:
cmp r12, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea rcx, qword ptr [rbp - 32]
call Base$GetSum
mov r13, rax
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label24
label22:
mov r12, qword ptr [rbp - 40]
jmp label21
label23:
lea r13, qword ptr [rbp - 32]
lea r12, [r13]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 40], r13
jmp label22
label24:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
PassBaseRef__Baseref:
label25:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
jmp label28
label26:
cmp r13, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov rcx, r14
call Base$GetSum
mov r12, rax
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label29
label27:
mov r13, qword ptr [rbp - 32]
jmp label26
label28:
lea r12, [r14]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 32], r13
jmp label27
label29:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
PassDerivedRef__Derivedref:
label30:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, rcx
jmp label36
label31:
cmp r13, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label34
label32:
cmp r12, 2
sete dil
and dil, 1
mov cl, dil
call Assert
mov rcx, r14
call Derived$GetSum
mov rdi, rax
cmp rdi, 3
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label37
label33:
mov r12, qword ptr [rbp - 40]
jmp label32
label34:
lea rdi, [r14 + 8]
mov r12, qword ptr [rdi]
mov qword ptr [rbp - 40], r12
jmp label33
label35:
mov r13, qword ptr [rbp - 48]
jmp label31
label36:
lea r12, [r14]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 48], r13
jmp label35
label37:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestAssignment:
label38:
push rbp
mov rbp, rsp
sub rsp, 272
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 72]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r12, qword ptr [rbp - 80]
mov r14, qword ptr [r13]
lea r15, [r12]
mov qword ptr [rbp - 192], r15
mov r15, qword ptr [rbp - 192]
mov qword ptr [r15], r14
jmp label53
label39:
cmp qword ptr [rbp - 200], 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea rcx, qword ptr [rbp - 80]
call Base$GetSum
mov r12, rax
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 80]
lea rdi, qword ptr [rbp - 176]
mov rsi, qword ptr [r12]
mov qword ptr [rdi], rsi
mov rcx, rdi
call PassBase__Base
lea rcx, qword ptr [rbp - 80]
call PassBaseRef__Baseref
lea rdi, qword ptr [rbp - 104]
lea r15, [rdi + 8]
mov qword ptr [rbp - 208], r15
mov r15, qword ptr [rbp - 208]
mov qword ptr [r15], 2
lea rdi, qword ptr [rbp - 104]
lea r15, [rdi]
mov qword ptr [rbp - 216], r15
mov r15, qword ptr [rbp - 216]
mov qword ptr [r15], 1
lea rdi, qword ptr [rbp - 104]
lea r15, [rdi + 16]
mov qword ptr [rbp - 224], r15
mov r15, qword ptr [rbp - 224]
mov qword ptr [r15], 3
lea rcx, qword ptr [rbp - 104]
call ExtendedDerived$GetSum
mov rdi, rax
cmp rdi, 6
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label51
label40:
cmp qword ptr [rbp - 232], 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 112]
mov r15, qword ptr [rbp - 216]
mov r15, qword ptr [r15]
mov qword ptr [rbp - 240], r15
lea r12, [r14]
mov r15, qword ptr [rbp - 240]
mov qword ptr [r12], r15
jmp label49
label41:
cmp r14, 1
sete sil
and sil, 1
mov cl, sil
call Assert
lea rcx, qword ptr [rbp - 112]
call Base$GetSum
mov rsi, rax
cmp rsi, 1
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 112]
lea rdi, qword ptr [rbp - 184]
mov rbx, qword ptr [rsi]
mov qword ptr [rdi], rbx
mov rcx, rdi
call PassBase__Base
lea rcx, qword ptr [rbp - 112]
call PassBaseRef__Baseref
lea rdi, qword ptr [rbp - 128]
lea rbx, [rdi]
mov r15, qword ptr [rbp - 240]
mov qword ptr [rbx], r15
lea rbx, qword ptr [rbp - 128]
mov r15, qword ptr [rbp - 208]
mov rdi, qword ptr [r15]
lea rsi, [rbx + 8]
mov qword ptr [rsi], rdi
jmp label47
label42:
cmp rdi, 1
sete bl
and bl, 1
mov cl, bl
call Assert
jmp label45
label43:
cmp rbx, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea rcx, qword ptr [rbp - 128]
call Derived$GetSum
mov r13, rax
cmp r13, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea rcx, qword ptr [rbp - 128]
call PassDerivedRef__Derivedref
jmp label54
label44:
mov rbx, qword ptr [rbp - 136]
jmp label43
label45:
mov r13, qword ptr [rsi]
mov qword ptr [rbp - 136], r13
jmp label44
label46:
mov rdi, qword ptr [rbp - 144]
jmp label42
label47:
lea r13, qword ptr [rbp - 128]
lea rdi, [r13]
mov r13, qword ptr [rdi]
mov qword ptr [rbp - 144], r13
jmp label46
label48:
mov r14, qword ptr [rbp - 152]
jmp label41
label49:
mov rsi, qword ptr [r12]
mov qword ptr [rbp - 152], rsi
jmp label48
label50:
mov r15, qword ptr [rbp - 160]
mov qword ptr [rbp - 232], r15
jmp label40
label51:
mov r15, qword ptr [rbp - 224]
mov rsi, qword ptr [r15]
mov qword ptr [rbp - 160], rsi
jmp label50
label52:
mov r15, qword ptr [rbp - 168]
mov qword ptr [rbp - 200], r15
jmp label39
label53:
mov r15, qword ptr [rbp - 192]
mov rsi, qword ptr [r15]
mov qword ptr [rbp - 168], rsi
jmp label52
label54:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestReferenceAssignment:
label55:
push rbp
mov rbp, rsp
sub rsp, 256
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 72]
mov qword ptr [rbp - 80], r14
mov r15, qword ptr [rbp - 80]
mov qword ptr [rbp - 184], r15
jmp label70
label56:
cmp qword ptr [rbp - 192], 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov rcx, qword ptr [rbp - 184]
call Base$GetSum
mov r12, rax
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 104]
lea rdi, [r12 + 8]
mov qword ptr [rdi], 2
lea rdi, qword ptr [rbp - 104]
lea r12, [rdi]
mov qword ptr [r12], 1
lea r12, qword ptr [rbp - 104]
lea rdi, [r12 + 16]
mov qword ptr [rdi], 3
lea rdi, qword ptr [rbp - 104]
mov qword ptr [rbp - 112], rdi
mov r15, qword ptr [rbp - 112]
mov qword ptr [rbp - 200], r15
jmp label68
label57:
cmp qword ptr [rbp - 208], 1
sete sil
and sil, 1
mov cl, sil
call Assert
mov rcx, qword ptr [rbp - 200]
call Base$GetSum
mov rsi, rax
cmp rsi, 1
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 104]
mov qword ptr [rbp - 120], rsi
mov r15, qword ptr [rbp - 120]
mov qword ptr [rbp - 216], r15
jmp label66
label58:
cmp qword ptr [rbp - 224], 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label64
label59:
cmp r14, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov rcx, qword ptr [rbp - 216]
call Derived$GetSum
mov r13, rax
cmp r13, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 128]
mov r15, qword ptr [rbp - 216]
lea rdi, [r15]
mov r12, qword ptr [rdi]
lea rdi, [r13]
mov qword ptr [rdi], r12
jmp label62
label60:
cmp r12, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea rcx, qword ptr [rbp - 128]
call Base$GetSum
mov r13, rax
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 128]
lea rsi, qword ptr [rbp - 176]
mov rbx, qword ptr [r13]
mov qword ptr [rsi], rbx
mov rcx, rsi
call PassBase__Base
lea rcx, qword ptr [rbp - 128]
call PassBaseRef__Baseref
jmp label71
label61:
mov r12, qword ptr [rbp - 136]
jmp label60
label62:
mov rsi, qword ptr [rdi]
mov qword ptr [rbp - 136], rsi
jmp label61
label63:
mov r14, qword ptr [rbp - 144]
jmp label59
label64:
mov r15, qword ptr [rbp - 216]
lea rsi, [r15 + 8]
mov r14, qword ptr [rsi]
mov qword ptr [rbp - 144], r14
jmp label63
label65:
mov r15, qword ptr [rbp - 152]
mov qword ptr [rbp - 224], r15
jmp label58
label66:
mov r15, qword ptr [rbp - 216]
lea r14, [r15]
mov rsi, qword ptr [r14]
mov qword ptr [rbp - 152], rsi
jmp label65
label67:
mov r15, qword ptr [rbp - 160]
mov qword ptr [rbp - 208], r15
jmp label57
label68:
mov r15, qword ptr [rbp - 200]
lea rsi, [r15]
mov r14, qword ptr [rsi]
mov qword ptr [rbp - 160], r14
jmp label67
label69:
mov r15, qword ptr [rbp - 168]
mov qword ptr [rbp - 192], r15
jmp label56
label70:
mov r15, qword ptr [rbp - 184]
lea r14, [r15]
mov rsi, qword ptr [r14]
mov qword ptr [rbp - 168], rsi
jmp label69
label71:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label72:
push rbp
mov rbp, rsp
sub rsp, 32
call TestAssignment
call TestReferenceAssignment
jmp label73
label73:
mov rax, 0
mov rsp, rbp
pop rbp
ret
