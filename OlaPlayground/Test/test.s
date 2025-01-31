.intel_syntax noprefix

.section .data

global_a:
.quad 5


global_b:
.quad 3


global_c:
.quad 7


global_d:
.quad 1


global_composite_and_a:
.quad 5


global_composite_and_b:
.quad 3


global_composite_and_c:
.quad 7


global_composite_or_a:
.quad 5


global_composite_or_b:
.quad 3


global_composite_or_c:
.quad 7


global_composite_xor_a:
.quad 5


global_composite_xor_b:
.quad 3


global_composite_xor_c:
.quad 7


.section .text

.extern Assert

.extern AssertMsg

TestBitAnd:
label0:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 5
and r14, 3
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 32]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 3
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
and r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr global_a[rip]
mov r13, qword ptr global_b[rip]
mov r14, r12
and r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr global_b[rip]
mov r12, r14
and r12, r13
mov qword ptr [rbp - 72], r12
mov r12, qword ptr [rbp - 72]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 48]
mov r13, 5
and r13, r12
mov qword ptr [rbp - 80], r13
mov r13, qword ptr [rbp - 80]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_a[rip]
mov r12, r13
and r12, 3
mov qword ptr [rbp - 88], r12
mov r12, qword ptr [rbp - 88]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 96], 5
mov r12, qword ptr [rbp - 96]
mov r13, r12
and r13, 3
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbp - 96]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 104], 5
mov qword ptr [rbp - 112], 3
mov r13, qword ptr [rbp - 104]
mov r12, qword ptr [rbp - 112]
mov r14, r13
and r14, r12
mov qword ptr [rbp - 104], r14
mov r14, qword ptr [rbp - 104]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_composite_and_a[rip]
mov r12, qword ptr global_composite_and_b[rip]
mov r13, r14
and r13, r12
mov qword ptr global_composite_and_a[rip], r13
mov r13, qword ptr global_composite_and_a[rip]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_composite_and_b[rip]
mov r12, r13
and r12, 5
mov qword ptr global_composite_and_b[rip], r12
mov r12, qword ptr global_composite_and_b[rip]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 120], 2
mov r12, qword ptr global_composite_and_c[rip]
mov r13, qword ptr [rbp - 120]
mov r14, r12
and r14, r13
mov qword ptr global_composite_and_c[rip], r14
mov r14, qword ptr global_composite_and_c[rip]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestBitOr:
label2:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 5
or r14, 3
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 32]
cmp r14, 7
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 3
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
or r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 7
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr global_a[rip]
mov r13, qword ptr global_b[rip]
mov r14, r12
or r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 7
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr global_b[rip]
mov r12, r14
or r12, r13
mov qword ptr [rbp - 72], r12
mov r12, qword ptr [rbp - 72]
cmp r12, 7
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 48]
mov r13, 5
or r13, r12
mov qword ptr [rbp - 80], r13
mov r13, qword ptr [rbp - 80]
cmp r13, 7
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_a[rip]
mov r12, r13
or r12, 3
mov qword ptr [rbp - 88], r12
mov r12, qword ptr [rbp - 88]
cmp r12, 7
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 96], 5
mov r12, qword ptr [rbp - 96]
mov r13, r12
or r13, 3
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbp - 96]
cmp r13, 7
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 104], 5
mov qword ptr [rbp - 112], 3
mov r13, qword ptr [rbp - 104]
mov r12, qword ptr [rbp - 112]
mov r14, r13
or r14, r12
mov qword ptr [rbp - 104], r14
mov r14, qword ptr [rbp - 104]
cmp r14, 7
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_composite_or_a[rip]
mov r12, qword ptr global_composite_or_b[rip]
mov r13, r14
or r13, r12
mov qword ptr global_composite_or_a[rip], r13
mov r13, qword ptr global_composite_or_a[rip]
cmp r13, 7
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_composite_or_b[rip]
mov r12, r13
or r12, 5
mov qword ptr global_composite_or_b[rip], r12
mov r12, qword ptr global_composite_or_b[rip]
cmp r12, 7
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 120], 2
mov r12, qword ptr global_composite_or_c[rip]
mov r13, qword ptr [rbp - 120]
mov r14, r12
or r14, r13
mov qword ptr global_composite_or_c[rip], r14
mov r14, qword ptr global_composite_or_c[rip]
cmp r14, 7
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label3
label3:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestBitXor:
label4:
push rbp
mov rbp, rsp
sub rsp, 152
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov r14, 5
xor r14, 3
mov qword ptr [rbp - 32], r14
mov r14, qword ptr [rbp - 32]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 40], 5
mov qword ptr [rbp - 48], 3
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr [rbp - 48]
mov r12, r14
xor r12, r13
mov qword ptr [rbp - 56], r12
mov r12, qword ptr [rbp - 56]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr global_a[rip]
mov r13, qword ptr global_b[rip]
mov r14, r12
xor r14, r13
mov qword ptr [rbp - 64], r14
mov r14, qword ptr [rbp - 64]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 40]
mov r13, qword ptr global_b[rip]
mov r12, r14
xor r12, r13
mov qword ptr [rbp - 72], r12
mov r12, qword ptr [rbp - 72]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rbp - 48]
mov r13, 5
xor r13, r12
mov qword ptr [rbp - 80], r13
mov r13, qword ptr [rbp - 80]
cmp r13, 6
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_a[rip]
mov r12, r13
xor r12, 3
mov qword ptr [rbp - 88], r12
mov r12, qword ptr [rbp - 88]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 96], 5
mov r12, qword ptr [rbp - 96]
mov r13, r12
xor r13, 3
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbp - 96]
cmp r13, 6
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 104], 5
mov qword ptr [rbp - 112], 3
mov r13, qword ptr [rbp - 104]
mov r12, qword ptr [rbp - 112]
mov r14, r13
xor r14, r12
mov qword ptr [rbp - 104], r14
mov r14, qword ptr [rbp - 104]
cmp r14, 6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_composite_xor_a[rip]
mov r12, qword ptr global_composite_xor_b[rip]
mov r13, r14
xor r13, r12
mov qword ptr global_composite_xor_a[rip], r13
mov r13, qword ptr global_composite_xor_a[rip]
cmp r13, 6
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_composite_xor_b[rip]
mov r12, r13
xor r12, 5
mov qword ptr global_composite_xor_b[rip], r12
mov r12, qword ptr global_composite_xor_b[rip]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 120], 2
mov r12, qword ptr global_composite_xor_c[rip]
mov r13, qword ptr [rbp - 120]
mov r14, r12
xor r14, r13
mov qword ptr global_composite_xor_c[rip], r14
mov r14, qword ptr global_composite_xor_c[rip]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestBitNot:
label6:
push rbp
mov rbp, rsp
sub rsp, 136
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], -6
mov r14, qword ptr [rbp - 24]
cmp r14, -6
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 32], 0
mov r14, qword ptr [rbp - 32]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 40], -1
mov r14, qword ptr [rbp - 40]
cmp r14, -1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 48], -256
mov r14, qword ptr [rbp - 48]
cmp r14, -256
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 56], -65536
mov r14, qword ptr [rbp - 56]
cmp r14, -65536
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 64], 5
mov r14, qword ptr [rbp - 64]
mov r13, r14
not r13
mov qword ptr [rbp - 72], r13
mov r13, qword ptr [rbp - 72]
cmp r13, -6
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 80], -1
mov r13, qword ptr [rbp - 80]
mov r14, r13
not r14
mov qword ptr [rbp - 88], r14
mov r14, qword ptr [rbp - 88]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr global_a[rip]
mov r13, r14
not r13
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbp - 96]
cmp r13, -6
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr global_c[rip]
mov r14, r13
not r14
mov qword ptr [rbp - 104], r14
mov r14, qword ptr [rbp - 104]
cmp r14, -8
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label7
label7:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label8:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestBitAnd
call TestBitOr
call TestBitXor
call TestBitNot
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
