.intel_syntax noprefix

.text

.extern _Assert

.extern _AssertMsg

.globl _ShiftMix__I__I__I__I__I__I__I__I

_ShiftMix__I__I__I__I__I__I__I__I:
label0:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rbx
mov qword ptr [rbp - 16], r12
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r14
mov r14, rdi
mov r15, rsi
mov qword ptr [rbp - 48], r15
mov r12, rdx
mov rbx, rcx
mov r15, r8
mov qword ptr [rbp - 56], r15
mov r15, r9
mov qword ptr [rbp - 64], r15
mov r15, qword ptr [rbp + 16]
mov qword ptr [rbp - 72], r15
mov r15, qword ptr [rbp + 24]
mov qword ptr [rbp - 80], r15
mov r15, r12
mov qword ptr [rbp - 88], r15
mov r15, qword ptr [rbp - 72]
mov rcx, r15
mov r15, qword ptr [rbp - 88]
shl r15, cl
mov qword ptr [rbp - 88], r15
mov r15, rbx
mov qword ptr [rbp - 96], r15
mov r15, qword ptr [rbp - 80]
mov rcx, r15
mov r15, qword ptr [rbp - 96]
shl r15, cl
mov qword ptr [rbp - 96], r15
lea r13, [r14 + 1]
mov r15, r13
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 56]
mov rcx, r15
mov r15, qword ptr [rbp - 104]
sar r15, cl
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 48]
lea r13, [r15 + 1]
mov r15, r13
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 64]
mov rcx, r15
mov r15, qword ptr [rbp - 112]
sar r15, cl
mov qword ptr [rbp - 112], r15
lea r13, [r12 + 1]
mov r15, r13
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 72]
mov rcx, r15
mov r15, qword ptr [rbp - 120]
sar r15, cl
mov qword ptr [rbp - 120], r15
lea r13, [rbx + 1]
mov r15, r13
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 80]
mov rcx, r15
mov r15, qword ptr [rbp - 128]
sar r15, cl
mov qword ptr [rbp - 128], r15
mov r13, r14
mov r15, qword ptr [rbp - 56]
mov rcx, r15
shl r13, cl
mov r15, qword ptr [rbp - 48]
mov r14, r15
mov r15, qword ptr [rbp - 64]
mov rcx, r15
shl r14, cl
lea rbx, [r13 + r14]
mov r15, qword ptr [rbp - 88]
lea r14, [rbx + r15]
mov r15, qword ptr [rbp - 96]
lea r13, [r14 + r15]
mov r15, qword ptr [rbp - 104]
lea r14, [r13 + r15]
mov r15, qword ptr [rbp - 112]
lea r13, [r14 + r15]
mov r15, qword ptr [rbp - 120]
lea r14, [r13 + r15]
mov r15, qword ptr [rbp - 128]
lea r13, [r14 + r15]
mov r15, qword ptr [rbp - 56]
mov rax, qword ptr [rbp - 64]
lea r14, [r15 + rax]
mov r12, r14
and r12, 7
mov r14, rbx
mov rcx, r12
shl r14, cl
lea r12, [r13 + r14]
mov r15, qword ptr [rbp - 88]
mov rax, qword ptr [rbp - 96]
lea r14, [r15 + rax]
mov r15, qword ptr [rbp - 72]
mov rax, qword ptr [rbp - 80]
lea r13, [r15 + rax]
mov rbx, r13
and rbx, 7
mov r13, r14
mov rcx, rbx
sar r13, cl
lea rbx, [r12 + r13]
mov r15, qword ptr [rbp - 104]
mov rax, qword ptr [rbp - 120]
lea r13, [r15 + rax]
mov r15, qword ptr [rbp - 64]
mov r12, r15
and r12, 7
mov r14, r13
mov rcx, r12
shl r14, cl
lea r12, [rbx + r14]
mov r15, qword ptr [rbp - 112]
mov rax, qword ptr [rbp - 128]
lea r14, [r15 + rax]
mov r15, qword ptr [rbp - 56]
mov rbx, r15
and rbx, 7
mov r13, r14
mov rcx, rbx
sar r13, cl
lea rbx, [r12 + r13]
jmp label1
label1:
mov rax, rbx
mov rbx, qword ptr [rbp - 8]
mov r12, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r14, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl _PowerOfTwoSum__I

_PowerOfTwoSum__I:
label2:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], rbx
mov qword ptr [rbp - 16], r12
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r14
mov r14, rdi
mov r13, 0
mov r15, 0
mov qword ptr [rbp - 48], r15
jmp label3
label3:
mov r15, qword ptr [rbp - 48]
cmp r15, r14
setl bl
and bl, 1
test bl, bl
jne label4
jmp label5
label4:
mov rbx, 1
mov r15, qword ptr [rbp - 48]
mov rcx, r15
shl rbx, cl
lea r12, [r13 + rbx]
mov r15, qword ptr [rbp - 48]
lea rbx, [r15 + 1]
mov r13, r12
mov r15, rbx
mov qword ptr [rbp - 48], r15
jmp label3
label5:
mov rax, r13
mov rbx, qword ptr [rbp - 8]
mov r12, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r14, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl _RotateLikePattern__I__I

_RotateLikePattern__I__I:
label6:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], rbx
mov qword ptr [rbp - 16], r12
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r14
mov r15, rdi
mov qword ptr [rbp - 48], r15
mov r13, rsi
mov r15, qword ptr [rbp - 48]
mov r12, r15
mov rcx, r13
shl r12, cl
mov rbx, 8
sub rbx, r13
mov r15, qword ptr [rbp - 48]
mov r14, r15
mov rcx, rbx
sar r14, cl
mov rbx, r12
or rbx, r14
mov r14, r13
and r14, 3
mov r13, rbx
mov rcx, r14
shl r13, cl
mov r14, r13
mov r15, qword ptr [rbp - 48]
xor r14, r15
jmp label7
label7:
mov rax, r14
mov rbx, qword ptr [rbp - 8]
mov r12, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r14, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
.globl _main

_main:
label8:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], rbx
mov qword ptr [rbp - 16], r12
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r14
mov qword ptr [rbp - 48], 4
mov qword ptr [rbp - 56], 1
mov r9, 3
mov r8, 2
mov rcx, 11
mov rdx, 7
mov rsi, 5
mov rdi, 3
call _ShiftMix__I__I__I__I__I__I__I__I
mov r14, rax
cmp r14, 1956
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov rdi, 0
call _PowerOfTwoSum__I
mov r14, rax
cmp r14, 0
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov rdi, 1
call _PowerOfTwoSum__I
mov r14, rax
cmp r14, 1
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov rdi, 4
call _PowerOfTwoSum__I
mov r14, rax
cmp r14, 15
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov rdi, 8
call _PowerOfTwoSum__I
mov r14, rax
cmp r14, 255
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
mov rdi, 10
call _PowerOfTwoSum__I
mov r14, rax
cmp r14, 1023
sete r14b
and r14b, 1
mov dil, r14b
call _Assert
jmp label12
label9:
mov r15, qword ptr [rbp - 48]
mov rax, qword ptr [rbp - 48]
cmp r15, rax
sete r13b
and r13b, 1
mov dil, r13b
call _Assert
jmp label11
label10:
cmp r13, r13
sete r12b
and r12b, 1
mov dil, r12b
call _Assert
jmp label13
label11:
mov r12, 104
or r12, 0
mov rbx, 3
and rbx, 3
mov r14, r12
mov rcx, rbx
shl r14, cl
mov r13, r14
xor r13, 13
jmp label10
label12:
mov r14, 20
or r14, 0
mov r13, 2
and r13, 3
mov rbx, r14
mov rcx, r13
shl rbx, cl
mov r15, rbx
mov qword ptr [rbp - 48], r15
mov r15, qword ptr [rbp - 48]
xor r15, 5
mov qword ptr [rbp - 48], r15
jmp label9
label13:
mov rax, 0
mov rbx, qword ptr [rbp - 8]
mov r12, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r14, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
