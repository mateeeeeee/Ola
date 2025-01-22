.intel_syntax noprefix

.section .rodata

_FP0:
.quad 4611686018427387904


_FP1:
.quad 4607182418800017408


_FP2:
.quad 4613937818241073152


_FP3:
.quad 4618441417868443648


_FP4:
.quad 4616189618054758400


_FP5:
.quad 4619567317775286272


.section .text

.extern Assert

.extern AssertMsg

Add__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 24
mov r15, rcx
mov r14, rdx
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov r14, qword ptr [rbp - 8]
mov r15, qword ptr [rbp - 16]
mov r13, r14
add r13, r15
mov qword ptr [rbp - 24], r13
jmp label2
label1:
label2:
mov r13, qword ptr [rbp - 24]
mov rax, r13
mov rsp, rbp
pop rbp
ret
AddThreeNumbers__I__I__I:
label3:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, rcx
mov r14, rdx
mov r13, r8
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov r13, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r15, r13
add r15, r14
mov r14, qword ptr [rbp - 24]
mov r13, r15
add r13, r14
mov qword ptr [rbp - 32], r13
jmp label5
label4:
label5:
mov r13, qword ptr [rbp - 32]
mov rax, r13
mov rsp, rbp
pop rbp
ret
AddFourNumbers__I__I__I__I:
label6:
push rbp
mov rbp, rsp
sub rsp, 40
mov r15, rcx
mov r14, rdx
mov r13, r8
mov r12, r9
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov r12, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r14, r12
add r14, r13
mov r13, qword ptr [rbp - 24]
mov r12, r14
add r12, r13
mov r13, qword ptr [rbp - 32]
mov r14, r12
add r14, r13
mov qword ptr [rbp - 40], r14
jmp label8
label7:
label8:
mov r14, qword ptr [rbp - 40]
mov rax, r14
mov rsp, rbp
pop rbp
ret
AddSixNumbers__I__I__I__I__I__I:
label9:
push rbp
mov rbp, rsp
sub rsp, 56
mov r15, rcx
mov r14, rdx
mov r13, r8
mov r12, r9
mov r11, qword ptr [rbp + 48]
mov r10, qword ptr [rbp + 56]
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], r11
mov qword ptr [rbp - 48], r10
mov r10, qword ptr [rbp - 8]
mov r11, qword ptr [rbp - 16]
mov r12, r10
add r12, r11
mov r11, qword ptr [rbp - 24]
mov r10, r12
add r10, r11
mov r11, qword ptr [rbp - 32]
mov r12, r10
add r12, r11
mov r11, qword ptr [rbp - 40]
mov r10, r12
add r10, r11
mov r11, qword ptr [rbp - 48]
mov r12, r10
add r12, r11
mov qword ptr [rbp - 56], r12
jmp label11
label10:
label11:
mov r12, qword ptr [rbp - 56]
mov rax, r12
mov rsp, rbp
pop rbp
ret
AlternatingSum__I__I__I__I__I__I:
label12:
push rbp
mov rbp, rsp
sub rsp, 56
mov r15, rcx
mov r14, rdx
mov r13, r8
mov r12, r9
mov r11, qword ptr [rbp + 48]
mov r10, qword ptr [rbp + 56]
mov qword ptr [rbp - 8], r15
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], r11
mov qword ptr [rbp - 48], r10
mov r10, qword ptr [rbp - 8]
mov r11, qword ptr [rbp - 16]
mov r12, r10
sub r12, r11
mov r11, qword ptr [rbp - 24]
mov r10, r12
add r10, r11
mov r11, qword ptr [rbp - 32]
mov r12, r10
sub r12, r11
mov r11, qword ptr [rbp - 40]
mov r10, r12
add r10, r11
mov r11, qword ptr [rbp - 48]
mov r12, r10
sub r12, r11
mov qword ptr [rbp - 56], r12
jmp label14
label13:
label14:
mov r12, qword ptr [rbp - 56]
mov rax, r12
mov rsp, rbp
pop rbp
ret
AddFloats__F__F:
label15:
push rbp
mov rbp, rsp
sub rsp, 24
movsd xmm15, xmm0
movsd xmm14, xmm1
movsd qword ptr [rbp - 8], xmm15
movsd qword ptr [rbp - 16], xmm14
movsd xmm14, qword ptr [rbp - 8]
movsd xmm15, qword ptr [rbp - 16]
movsd xmm13, xmm14
addsd xmm13, xmm15
movsd qword ptr [rbp - 24], xmm13
jmp label17
label16:
label17:
movsd xmm13, qword ptr [rbp - 24]
movsd xmm0, xmm13
mov rsp, rbp
pop rbp
ret
AddIntAndFloat__I__F__F:
label18:
push rbp
mov rbp, rsp
sub rsp, 32
mov r15, rcx
movsd xmm15, xmm1
movsd xmm14, xmm2
mov qword ptr [rbp - 8], r15
movsd qword ptr [rbp - 16], xmm15
movsd qword ptr [rbp - 24], xmm14
mov r15, qword ptr [rbp - 8]
cvtsi2sd xmm14, r15
movsd xmm15, qword ptr [rbp - 16]
movsd xmm13, xmm14
addsd xmm13, xmm15
movsd xmm15, qword ptr [rbp - 24]
movsd xmm14, xmm13
addsd xmm14, xmm15
movsd qword ptr [rbp - 32], xmm14
jmp label20
label19:
label20:
movsd xmm14, qword ptr [rbp - 32]
movsd xmm0, xmm14
mov rsp, rbp
pop rbp
ret
ConditionSum__F__F__F__F__B:
label21:
push rbp
mov rbp, rsp
sub rsp, 41
movsd xmm15, xmm0
movsd xmm14, xmm1
movsd xmm13, xmm2
movsd xmm12, xmm3
mov r15b, byte ptr [rbp + 48]
movsd qword ptr [rbp - 8], xmm15
movsd qword ptr [rbp - 16], xmm14
movsd qword ptr [rbp - 24], xmm13
movsd qword ptr [rbp - 32], xmm12
mov byte ptr [rbp - 33], r15b
mov r15b, byte ptr [rbp - 33]
movsd xmm12, qword ptr [rbp - 8]
movsd xmm13, qword ptr [rbp - 16]
movsd xmm14, xmm12
addsd xmm14, xmm13
movsd xmm13, qword ptr [rbp - 24]
movsd xmm12, qword ptr [rbp - 32]
movsd xmm15, xmm13
addsd xmm15, xmm12
movsd xmm12, xmm15
test r15b, r15b
je label24
movsd xmm12, xmm14
label24:
movsd qword ptr [rbp - 41], xmm12
jmp label23
label22:
label23:
movsd xmm12, qword ptr [rbp - 41]
movsd xmm0, xmm12
mov rsp, rbp
pop rbp
ret
AddBooleans__B__B__B__B:
label25:
push rbp
mov rbp, rsp
sub rsp, 12
mov r15b, cl
mov r14b, dl
mov r13b, r8b
mov r12b, r9b
mov byte ptr [rbp - 1], r15b
mov byte ptr [rbp - 2], r14b
mov byte ptr [rbp - 3], r13b
mov byte ptr [rbp - 4], r12b
mov r12b, byte ptr [rbp - 1]
mov r13b, byte ptr [rbp - 2]
mov r14b, r12b
add r14b, r13b
mov r13b, byte ptr [rbp - 3]
mov r12b, r14b
add r12b, r13b
mov r13b, byte ptr [rbp - 4]
mov r14b, r12b
add r14b, r13b
movzx r13, r14b
mov qword ptr [rbp - 12], r13
jmp label27
label26:
label27:
mov r13, qword ptr [rbp - 12]
mov rax, r13
mov rsp, rbp
pop rbp
ret
TestIntCalls:
label28:
push rbp
mov rbp, rsp
sub rsp, 48
mov rdx, 2
mov rcx, 1
call Add__I__I
mov r15, rax
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r8, 3
mov rdx, 2
mov rcx, 1
call AddThreeNumbers__I__I__I
mov r15, rax
cmp r15, 6
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call AddFourNumbers__I__I__I__I
mov r15, rax
cmp r15, 10
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 6
mov qword ptr [rbp - 16], 5
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call AddSixNumbers__I__I__I__I__I__I
mov r15, rax
cmp r15, 21
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 6
mov qword ptr [rbp - 16], 5
mov r9, 4
mov r8, 3
mov rdx, 2
mov rcx, 1
call AlternatingSum__I__I__I__I__I__I
mov r15, rax
cmp r15, -3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label29
label29:
mov rsp, rbp
pop rbp
ret
TestFloatCalls:
label30:
push rbp
mov rbp, rsp
sub rsp, 40
movsd xmm1, qword ptr [rip + _FP0]
movsd xmm0, qword ptr [rip + _FP1]
call AddFloats__F__F
movsd xmm15, xmm0
comisd xmm15, qword ptr [rip + _FP2]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
movsd xmm2, qword ptr [rip + _FP2]
movsd xmm1, qword ptr [rip + _FP0]
mov rcx, 1
call AddIntAndFloat__I__F__F
movsd xmm15, xmm0
comisd xmm15, qword ptr [rip + _FP3]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 1
movsd xmm3, qword ptr [rip + _FP4]
movsd xmm2, qword ptr [rip + _FP2]
movsd xmm1, qword ptr [rip + _FP0]
movsd xmm0, qword ptr [rip + _FP1]
call ConditionSum__F__F__F__F__B
movsd xmm15, xmm0
comisd xmm15, qword ptr [rip + _FP2]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov qword ptr [rbp - 8], 0
movsd xmm3, qword ptr [rip + _FP4]
movsd xmm2, qword ptr [rip + _FP2]
movsd xmm1, qword ptr [rip + _FP0]
movsd xmm0, qword ptr [rip + _FP1]
call ConditionSum__F__F__F__F__B
movsd xmm15, xmm0
comisd xmm15, qword ptr [rip + _FP5]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label31
label31:
mov rsp, rbp
pop rbp
ret
TestBoolCalls:
label32:
push rbp
mov rbp, rsp
sub rsp, 32
mov r9, 0
mov r8, 1
mov rdx, 0
mov rcx, 1
call AddBooleans__B__B__B__B
mov r15, rax
cmp r15, 2
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label33
label33:
mov rsp, rbp
pop rbp
ret
.globl main

main:
label34:
push rbp
mov rbp, rsp
sub rsp, 40
call TestIntCalls
call TestFloatCalls
call TestBoolCalls
mov qword ptr [rbp - 8], 0
jmp label36
label35:
label36:
mov r15, qword ptr [rbp - 8]
mov rax, r15
mov rsp, rbp
pop rbp
ret
