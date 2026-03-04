.intel_syntax noprefix

.section .rodata

_FP0:
.quad 0


_FP1:
.quad 4614253070214989087


.data

VTable_Shape:
.quad Shape$Area


VTable_Rectangle:
.quad Rectangle$Area


.text

.extern Assert

.extern AssertMsg

.globl Shape$Shape__I__I

Shape$Shape__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, rdx
mov r12, r8
mov qword ptr [rbp - 40], r13
mov qword ptr [rbp - 48], r12
mov r12, qword ptr [rbp - 40]
lea r13, [r14 + 8]
mov qword ptr [r13], r12
mov r13, qword ptr [rbp - 48]
lea r12, [r14 + 16]
mov qword ptr [r12], r13
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl Shape$GetX

Shape$GetX:
label2:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label4
label3:
label4:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Shape$GetY

Shape$GetY:
label5:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label7
label6:
label7:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Shape$Area

Shape$Area:
label8:
push rbp
mov rbp, rsp
sub rsp, 16
mov qword ptr [rbp - 8], r14
mov r14, rcx
mov qword ptr [rbp - 16], 0
jmp label10
label9:
label10:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
.globl Rectangle$Rectangle__I__I__I__I

Rectangle$Rectangle__I__I__I__I:
label11:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, rcx
mov r13, rdx
mov r12, r8
mov rdi, r9
mov rsi, qword ptr [rbp + 48]
mov qword ptr [rbp - 56], r13
mov qword ptr [rbp - 64], r12
mov qword ptr [rbp - 72], rdi
mov qword ptr [rbp - 80], rsi
mov rsi, qword ptr [rbp - 56]
mov rdi, qword ptr [rbp - 64]
mov r8, rdi
mov rdx, rsi
mov rcx, r14
call Shape$Shape__I__I
mov rsi, qword ptr [rbp - 72]
lea rdi, [r14 + 24]
mov qword ptr [rdi], rsi
mov rdi, qword ptr [rbp - 80]
lea rsi, [r14 + 32]
mov qword ptr [rsi], rdi
jmp label12
label12:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
.globl Rectangle$Area

Rectangle$Area:
label13:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
lea r13, [r14 + 24]
mov r12, qword ptr [r13]
lea r13, [r14 + 32]
mov r14, qword ptr [r13]
mov r13, r12
imul r13, r14
mov qword ptr [rbp - 32], r13
jmp label15
label14:
label15:
mov r13, qword ptr [rbp - 32]
mov rax, r13
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.int.$Pair__I__I

Pair.int.int.$Pair__I__I:
label16:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, rdx
mov r12, r8
mov qword ptr [rbp - 40], r13
mov qword ptr [rbp - 48], r12
mov r12, qword ptr [rbp - 40]
lea r13, [r14]
mov qword ptr [r13], r12
mov r13, qword ptr [rbp - 48]
lea r12, [r14 + 8]
mov qword ptr [r12], r13
jmp label17
label17:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.int.$First

Pair.int.int.$First:
label18:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label20
label19:
label20:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.int.$Second

Pair.int.int.$Second:
label21:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label23
label22:
label23:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
AreaAt__Pair.int.int.ref__I__I:
label24:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, rcx
mov r13, rdx
mov r12, r8
mov qword ptr [rbp - 40], r14
mov r14, qword ptr [rbp - 40]
mov qword ptr [rbp - 48], r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 48]
mov r13, qword ptr [rbp - 56]
mov r14, r12
imul r14, r13
mov qword ptr [rbp - 64], r14
jmp label26
label25:
label26:
mov r14, qword ptr [rbp - 64]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.float.$Pair__I__F

Pair.int.float.$Pair__I__F:
label27:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
mov r14, rcx
mov r13, rdx
movsd xmm14, xmm2
mov qword ptr [rbp - 40], r13
movsd qword ptr [rbp - 48], xmm14
mov r13, qword ptr [rbp - 40]
lea r12, [r14]
mov qword ptr [r12], r13
movsd xmm14, qword ptr [rbp - 48]
lea r12, [r14 + 8]
movsd qword ptr [r12], xmm14
jmp label28
label28:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.float.$First

Pair.int.float.$First:
label29:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov r14, rcx
lea r13, [r14]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label31
label30:
label31:
mov r14, qword ptr [rbp - 32]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl Pair.int.float.$Second

Pair.int.float.$Second:
label32:
push rbp
mov rbp, rsp
sub rsp, 32
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
movsd qword ptr [rbp - 24], xmm14
mov r14, rcx
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
mov qword ptr [rbp - 32], r14
jmp label34
label33:
label34:
movsd xmm14, qword ptr [rbp - 32]
movsd xmm0, xmm14
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
movsd xmm14, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label35:
push rbp
mov rbp, rsp
sub rsp, 256
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
movsd qword ptr [rbp - 56], xmm14
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 8]
movsd xmm14, qword ptr [rip + _FP0]
movsd qword ptr [r14], xmm14
movsd xmm2, qword ptr [rip + _FP1]
mov rdx, 10
lea rcx, qword ptr [rbp - 80]
call Pair.int.float.$Pair__I__F
lea r14, qword ptr [rbp - 120]
lea r13, [rip + VTable_Rectangle]
lea r12, [r14]
mov qword ptr [r12], r13
lea r12, qword ptr [rbp - 120]
lea r13, [r12 + 8]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 120]
lea r12, [r13 + 16]
mov qword ptr [r12], 0
lea r12, qword ptr [rbp - 120]
lea r13, [r12 + 24]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 120]
lea r12, [r13 + 32]
mov qword ptr [r12], 0
lea rcx, qword ptr [rbp - 80]
call Pair.int.float.$First
mov r12, rax
mov qword ptr [rbp - 168], 5
mov r9, r12
mov r8, 0
mov rdx, 0
lea rcx, qword ptr [rbp - 120]
call Rectangle$Rectangle__I__I__I__I
lea r12, qword ptr [rbp - 120]
lea r13, qword ptr [rbp - 200]
mov r14, qword ptr [r12]
mov rdi, r12
add rdi, 8
mov rsi, qword ptr [rdi]
mov rdi, r13
add rdi, 8
mov qword ptr [r13], r14
mov r14, r12
add r14, 16
mov rbx, qword ptr [r14]
mov r14, r13
add r14, 16
mov qword ptr [rdi], rsi
mov rdi, r12
add rdi, 24
mov rsi, qword ptr [rdi]
mov rdi, r13
add rdi, 24
mov qword ptr [r14], rbx
mov r14, r12
add r14, 32
mov r12, qword ptr [r14]
mov r14, r13
add r14, 32
mov qword ptr [rdi], rsi
mov qword ptr [r14], r12
lea r14, qword ptr [rbp - 120]
mov qword ptr [rbp - 128], r14
mov r14, qword ptr [rbp - 128]
lea r12, [r14]
mov rdi, qword ptr [r12]
lea r12, [rdi]
mov rdi, qword ptr [r12]
mov rcx, r14
mov rax, rdi
call rax
mov rdi, rax
mov qword ptr [rbp - 136], rdi
lea rdi, qword ptr [rbp - 152]
lea r14, [rdi]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 152]
lea rdi, [r14 + 8]
mov qword ptr [rdi], 0
mov r8, 0
mov rdx, 0
lea rcx, qword ptr [rbp - 152]
call Pair.int.int.$Pair__I__I
lea rdi, qword ptr [rbp - 152]
lea r14, qword ptr [rbp - 216]
mov r12, qword ptr [rdi]
mov rsi, rdi
add rsi, 8
mov rdi, qword ptr [rsi]
mov rsi, r14
add rsi, 8
mov qword ptr [r14], r12
mov qword ptr [rsi], rdi
mov r8, 4
mov rdx, 3
lea rcx, qword ptr [rbp - 152]
call AreaAt__Pair.int.int.ref__I__I
mov rsi, rax
mov qword ptr [rbp - 160], rsi
mov rsi, qword ptr [rbp - 160]
cmp rsi, 12
sete sil
and sil, 1
mov cl, sil
call Assert
mov rsi, qword ptr [rbp - 136]
mov qword ptr [rbp - 64], rsi
jmp label37
label36:
label37:
mov rsi, qword ptr [rbp - 64]
mov rax, rsi
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
movsd xmm14, qword ptr [rbp - 56]
mov rsp, rbp
pop rbp
ret
