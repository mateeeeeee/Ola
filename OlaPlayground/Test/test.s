.intel_syntax noprefix

.section .rodata

GlobalArray1:
.quad 1
.quad 1
.quad 1


GlobalArray2:
.quad 1
.quad 2
.quad 3
.quad 0
.quad 0


GlobalArray3:
.quad 10
.quad 20
.quad 30


GlobalFloatArray:
.quad 4609434218613702656
.quad 4612811918334230528
.quad 4615063718147915776


GlobalBoolArray:
.byte 1
.byte 0
.byte 1
.byte 0


_FP0:
.quad 4609433768253739919


_FP1:
.quad 4609434668973665393


_FP2:
.quad 4612811693154249159


_FP3:
.quad 4612812143514211897


_FP4:
.quad 4615063492967934407


_FP5:
.quad 4615063943327897145


_FP6:
.quad 4602678819172646912


_FP7:
.quad 4607182418800017408


_FP8:
.quad 4609434218613702656


_FP9:
.quad 4611686018427387904


_FP10:
.quad 4602677017732795964


_FP11:
.quad 4602679719892572386


_FP12:
.quad 4611685568067425167


_FP13:
.quad 4611686243607369273


_FP14:
.quad 4617315405371610340


_FP15:
.quad 4617315630551591708


.text

.extern Assert

.extern AssertMsg

TestGlobalArrays:
label0:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov cl, 1
call Assert
lea r14, [rip + GlobalArray1]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray1]
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray1]
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov cl, 1
call Assert
lea r14, [rip + GlobalArray2]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
lea r13, [r14 + 24]
mov r14, qword ptr [r13]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
lea r13, [r14 + 32]
mov r14, qword ptr [r13]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray3]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray3]
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray3]
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
cmp r14, 30
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label1
label1:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestLocalArrays:
label2:
push rbp
mov rbp, rsp
sub rsp, 192
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 136]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r14, qword ptr [rbp - 136]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 0
lea r14, qword ptr [rbp - 136]
lea rsi, [r14 + 24]
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
lea r14, [rsi + 32]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 136]
lea rsi, [r14 + 40]
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
lea r14, [rsi + 48]
mov qword ptr [r14], 0
lea rsi, qword ptr [rbp - 136]
lea rbx, [rsi + 56]
mov qword ptr [rbx], 0
lea rbx, qword ptr [rbp - 136]
lea rsi, [rbx + 64]
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
lea rbx, [rsi + 72]
mov qword ptr [rbx], 0
mov cl, 1
call Assert
mov rbx, qword ptr [r13]
cmp rbx, 1
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r12]
cmp rbx, 2
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [rdi]
cmp rbx, 0
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r14]
cmp rbx, 0
sete bl
and bl, 1
mov cl, bl
call Assert
lea rbx, qword ptr [rbp - 160]
lea r14, [rbx]
mov qword ptr [r14], -5
lea rbx, qword ptr [rbp - 160]
lea rdi, [rbx + 8]
mov qword ptr [rdi], 0
lea rbx, qword ptr [rbp - 160]
lea r12, [rbx + 16]
mov qword ptr [r12], 5
mov rbx, qword ptr [r14]
cmp rbx, -5
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [rdi]
cmp rbx, 0
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r12]
cmp rbx, 5
sete bl
and bl, 1
mov cl, bl
call Assert
mov cl, 1
call Assert
jmp label3
label3:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestFloatArrays:
label4:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
movsd qword ptr [rbp - 56], xmm14
movsd qword ptr [rbp - 64], xmm13
movsd qword ptr [rbp - 72], xmm12
movsd qword ptr [rbp - 80], xmm11
movsd qword ptr [rbp - 88], xmm10
lea r14, [rip + GlobalFloatArray]
lea r13, [r14]
movsd xmm14, qword ptr [r13]
movsd xmm13, qword ptr [r13]
comisd xmm14, qword ptr [rip + _FP0]
seta r13b
and r13b, 1
comisd xmm13, qword ptr [rip + _FP1]
setb r14b
and r14b, 1
mov r12b, r13b
and r12b, r14b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, [rip + GlobalFloatArray]
lea r14, [r12 + 8]
movsd xmm13, qword ptr [r14]
movsd xmm14, qword ptr [r14]
comisd xmm13, qword ptr [rip + _FP2]
seta r14b
and r14b, 1
comisd xmm14, qword ptr [rip + _FP3]
setb r12b
and r12b, 1
mov r13b, r14b
and r13b, r12b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalFloatArray]
lea r12, [r13 + 16]
movsd xmm14, qword ptr [r12]
movsd xmm13, qword ptr [r12]
comisd xmm14, qword ptr [rip + _FP4]
seta r12b
and r12b, 1
comisd xmm13, qword ptr [rip + _FP5]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 120]
lea r13, [r14]
movsd xmm13, qword ptr [rip + _FP6]
movsd qword ptr [r13], xmm13
lea r14, qword ptr [rbp - 120]
lea r12, [r14 + 8]
movsd xmm13, qword ptr [rip + _FP7]
movsd qword ptr [r12], xmm13
lea r14, qword ptr [rbp - 120]
lea rdi, [r14 + 16]
movsd xmm13, qword ptr [rip + _FP8]
movsd qword ptr [rdi], xmm13
lea r14, qword ptr [rbp - 120]
lea r15, [r14 + 24]
mov qword ptr [rbp - 128], r15
movsd xmm13, qword ptr [rip + _FP9]
mov r15, qword ptr [rbp - 128]
movsd qword ptr [r15], xmm13
movsd xmm13, qword ptr [r13]
movsd xmm14, qword ptr [r13]
comisd xmm13, qword ptr [rip + _FP10]
seta r14b
and r14b, 1
comisd xmm14, qword ptr [rip + _FP11]
setb bl
and bl, 1
mov sil, r14b
and sil, bl
cmp sil, 0
setne sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 128]
movsd xmm14, qword ptr [r15]
mov r15, qword ptr [rbp - 128]
movsd xmm13, qword ptr [r15]
comisd xmm14, qword ptr [rip + _FP12]
seta sil
and sil, 1
comisd xmm13, qword ptr [rip + _FP13]
setb bl
and bl, 1
mov r14b, sil
and r14b, bl
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm13, qword ptr [r13]
movsd xmm14, qword ptr [r12]
movsd xmm12, qword ptr [rdi]
mov r15, qword ptr [rbp - 128]
movsd xmm11, qword ptr [r15]
movsd xmm10, xmm13
addsd xmm10, xmm14
movsd xmm14, xmm10
addsd xmm14, xmm12
movsd xmm12, xmm14
addsd xmm12, xmm11
comisd xmm12, qword ptr [rip + _FP14]
seta dil
and dil, 1
comisd xmm12, qword ptr [rip + _FP15]
setb r12b
and r12b, 1
mov r13b, dil
and r13b, r12b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label5
label5:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
movsd xmm14, qword ptr [rbp - 56]
movsd xmm13, qword ptr [rbp - 64]
movsd xmm12, qword ptr [rbp - 72]
movsd xmm11, qword ptr [rbp - 80]
movsd xmm10, qword ptr [rbp - 88]
mov rsp, rbp
pop rbp
ret
TestBoolArrays:
label6:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, [rip + GlobalBoolArray]
lea r13, [r14]
mov r14b, byte ptr [r13]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalBoolArray]
lea r13, [r14 + 1]
mov r14b, byte ptr [r13]
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalBoolArray]
lea r13, [r14 + 2]
mov r14b, byte ptr [r13]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalBoolArray]
lea r13, [r14 + 3]
mov r14b, byte ptr [r13]
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 48]
lea r13, [r14]
mov byte ptr [r13], 1
lea r14, qword ptr [rbp - 48]
lea r12, [r14 + 1]
mov byte ptr [r12], 1
lea r14, qword ptr [rbp - 48]
lea rdi, [r14 + 2]
mov byte ptr [rdi], 0
mov r14b, byte ptr [r13]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14b, byte ptr [r12]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14b, byte ptr [rdi]
cmp r14b, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label7
label7:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestArrayModification:
label8:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r14, qword ptr [rbp - 88]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 3
lea r14, qword ptr [rbp - 88]
lea rsi, [r14 + 24]
mov qword ptr [rsi], 4
lea r14, qword ptr [rbp - 88]
lea rbx, [r14 + 32]
mov qword ptr [rbx], 5
mov qword ptr [r13], 10
mov r14, qword ptr [r13]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbx], 50
mov r14, qword ptr [rbx]
cmp r14, 50
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [r13]
mov r13, qword ptr [rbx]
lea rbx, [r14 + r13]
mov qword ptr [rdi], rbx
mov rbx, qword ptr [rdi]
cmp rbx, 60
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r12]
lea rdi, [rbx + rbx]
mov qword ptr [r12], rdi
mov rdi, qword ptr [r12]
cmp rdi, 4
sete dil
and dil, 1
mov cl, dil
call Assert
mov rdi, qword ptr [rsi]
mov qword ptr [rbp - 96], rdi
lea r12, [rdi + 1]
mov qword ptr [rsi], r12
mov r12, qword ptr [rsi]
cmp r12, 5
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rsi]
lea rdi, [r12 + 1]
mov qword ptr [rsi], rdi
mov rdi, qword ptr [rsi]
cmp rdi, 6
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label9
label9:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayExpressions:
label10:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r15, [r14]
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 104]
mov qword ptr [r15], 10
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 8]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 112]
mov qword ptr [r15], 20
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 16]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [r15], 30
lea r14, qword ptr [rbp - 96]
lea rsi, [r14 + 24]
mov qword ptr [rsi], 40
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 32]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [r15], 50
mov r15, qword ptr [rbp - 104]
mov r14, qword ptr [r15]
mov r15, qword ptr [rbp - 112]
mov rdi, qword ptr [r15]
mov r15, qword ptr [rbp - 120]
mov r12, qword ptr [r15]
mov r13, qword ptr [rsi]
mov r15, qword ptr [rbp - 128]
mov rsi, qword ptr [r15]
lea rbx, [r14 + rdi]
lea rdi, [rbx + r12]
lea rbx, [rdi + r13]
lea rdi, [rbx + rsi]
cmp rdi, 150
sete dil
and dil, 1
mov cl, dil
call Assert
mov r15, qword ptr [rbp - 104]
mov rdi, qword ptr [r15]
mov r15, qword ptr [rbp - 112]
mov rbx, qword ptr [r15]
mov rsi, rdi
imul rsi, rbx
cmp rsi, 200
sete sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 128]
mov rsi, qword ptr [r15]
mov r15, qword ptr [rbp - 104]
mov rbx, qword ptr [r15]
mov rdi, rsi
sub rdi, rbx
cmp rdi, 40
sete dil
and dil, 1
mov cl, dil
call Assert
mov r15, qword ptr [rbp - 128]
mov rdi, qword ptr [r15]
mov r15, qword ptr [rbp - 104]
mov rbx, qword ptr [r15]
cmp rdi, rbx
setg bl
and bl, 1
cmp bl, 1
sete bl
and bl, 1
mov cl, bl
call Assert
mov r15, qword ptr [rbp - 104]
mov rbx, qword ptr [r15]
mov r15, qword ptr [rbp - 112]
mov rdi, qword ptr [r15]
mov r15, qword ptr [rbp - 120]
mov rsi, qword ptr [r15]
lea r13, [rbx + rdi]
lea rdi, [r13 + rsi]
mov rax, rdi
cqo
mov rdi, 3
idiv rdi
mov rdi, rax
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label11
label11:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayVariableIndex:
label12:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 100
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 8]
mov qword ptr [r14], 200
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 16]
mov qword ptr [r13], 300
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 24]
mov qword ptr [r14], 400
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 32]
mov qword ptr [r13], 500
lea r13, qword ptr [rbp - 80]
mov r14, 0
imul r14, 40
lea r12, [r13 + r14]
mov r14, 0
imul r14, 8
lea r13, [r12 + r14]
mov r14, qword ptr [r13]
cmp r14, 100
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 80]
mov r13, 0
imul r13, 40
lea r12, [r14 + r13]
mov r13, 2
imul r13, 8
lea r14, [r12 + r13]
mov r13, qword ptr [r14]
cmp r13, 300
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 80]
mov r12, 0
imul r12, 40
lea rdi, [r13 + r12]
mov r12, 4
imul r12, 8
lea r13, [rdi + r12]
mov r12, qword ptr [r13]
cmp r12, 500
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r14]
cmp r12, 300
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r14]
cmp r12, 300
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label13
label13:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestArrayInLoops:
label14:
push rbp
mov rbp, rsp
sub rsp, 176
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 88]
lea r15, [r14]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [r15], 1
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 16]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [r15], 3
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 24]
mov qword ptr [rbp - 136], r15
mov r15, qword ptr [rbp - 136]
mov qword ptr [r15], 4
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 32]
mov qword ptr [rbp - 144], r15
mov r15, qword ptr [rbp - 144]
mov qword ptr [r15], 5
mov r14, 0
mov r13, 0
jmp label16
label15:
lea rbx, qword ptr [rbp - 88]
mov rsi, 0
imul rsi, 40
lea rdi, [rbx + rsi]
mov rsi, r14
imul rsi, 8
lea rbx, [rdi + rsi]
mov rsi, qword ptr [rbx]
lea rbx, [r13 + rsi]
jmp label17
label16:
cmp r14, 5
setl sil
and sil, 1
test sil, sil
jne label15
jmp label18
label17:
mov qword ptr [rbp - 96], r14
lea rsi, [r14 + 1]
mov r14, rsi
mov r13, rbx
jmp label16
label18:
cmp r13, 15
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, 0
jmp label20
label19:
lea r14, qword ptr [rbp - 88]
mov rbx, 0
imul rbx, 40
lea rsi, [r14 + rbx]
mov rbx, r13
imul rbx, 8
lea r14, [rsi + rbx]
mov rbx, qword ptr [r14]
lea rsi, [rbx + rbx]
mov qword ptr [r14], rsi
jmp label21
label20:
cmp r13, 5
setl sil
and sil, 1
test sil, sil
jne label19
jmp label22
label21:
mov qword ptr [rbp - 104], r13
lea rsi, [r13 + 1]
mov r13, rsi
jmp label20
label22:
mov r15, qword ptr [rbp - 120]
mov rsi, qword ptr [r15]
cmp rsi, 2
sete sil
and sil, 1
mov cl, sil
call Assert
mov rsi, qword ptr [r12]
cmp rsi, 4
sete sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 128]
mov rsi, qword ptr [r15]
cmp rsi, 6
sete sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 136]
mov rsi, qword ptr [r15]
cmp rsi, 8
sete sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 144]
mov rsi, qword ptr [r15]
cmp rsi, 10
sete sil
and sil, 1
mov cl, sil
call Assert
mov r15, qword ptr [rbp - 120]
mov rsi, qword ptr [r15]
mov r12, 1
mov r13, rsi
jmp label25
label23:
lea rsi, qword ptr [rbp - 88]
mov r14, 0
imul r14, 40
lea rbx, [rsi + r14]
mov r14, r12
imul r14, 8
lea rsi, [rbx + r14]
mov r14, qword ptr [rsi]
cmp r14, r13
setg r14b
and r14b, 1
test r14b, r14b
jne label27
jmp label24
label24:
mov r14, r13
jmp label28
label25:
cmp r12, 5
setl bl
and bl, 1
test bl, bl
jne label23
jmp label29
label26:
mov qword ptr [rbp - 112], r12
lea rbx, [r12 + 1]
mov r12, rbx
mov r13, r14
jmp label25
label27:
mov rbx, qword ptr [rsi]
mov r14, rbx
jmp label28
label28:
jmp label26
label29:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayWhileLoop:
label30:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 5
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 8]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 24]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 32]
mov qword ptr [r13], 1
mov r13, 0
mov r14, 0
jmp label31
label31:
cmp r14, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label32
jmp label33
label32:
lea r12, qword ptr [rbp - 80]
mov rdi, 0
imul rdi, 40
lea rsi, [r12 + rdi]
mov rdi, r14
imul rdi, 8
lea r12, [rsi + rdi]
mov rdi, qword ptr [r12]
lea r12, [r13 + rdi]
mov qword ptr [rbp - 88], r14
lea rdi, [r14 + 1]
mov r13, r12
mov r14, rdi
jmp label31
label33:
cmp r13, 15
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, 0
jmp label34
label34:
cmp r14, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label36
jmp label35
label35:
jmp label38
label36:
lea r13, qword ptr [rbp - 80]
mov rdi, 0
imul rdi, 40
lea r12, [r13 + rdi]
mov rdi, r14
imul rdi, 8
lea r13, [r12 + rdi]
mov rdi, qword ptr [r13]
mov rax, rdi
cqo
mov rdi, 2
idiv rdi
mov rdi, rdx
cmp rdi, 0
sete dil
and dil, 1
test dil, dil
jne label37
jmp label39
label37:
jmp label38
label38:
lea rdi, qword ptr [rbp - 80]
mov r13, 0
imul r13, 40
lea r12, [rdi + r13]
mov r13, r14
imul r13, 8
lea rdi, [r12 + r13]
mov r13, qword ptr [rdi]
cmp r13, 4
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label40
label39:
mov qword ptr [rbp - 96], r14
lea r13, [r14 + 1]
mov r14, r13
jmp label34
label40:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayNegativeValues:
label41:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r15, [r14]
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 104]
mov qword ptr [r15], -10
lea r14, qword ptr [rbp - 96]
lea r12, [r14 + 8]
mov qword ptr [r12], -5
lea r14, qword ptr [rbp - 96]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 0
lea r14, qword ptr [rbp - 96]
lea rsi, [r14 + 24]
mov qword ptr [rsi], 5
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 32]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 112]
mov qword ptr [r15], 10
mov r15, qword ptr [rbp - 104]
mov r14, qword ptr [r15]
cmp r14, -10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [r12]
cmp r14, -5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rdi]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rsi]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 112]
mov r14, qword ptr [r15]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 104]
mov r14, qword ptr [r15]
mov r13, qword ptr [r12]
mov r12, qword ptr [rdi]
mov rdi, qword ptr [rsi]
mov r15, qword ptr [rbp - 112]
mov rsi, qword ptr [r15]
lea rbx, [r14 + r13]
lea r13, [rbx + r12]
lea rbx, [r13 + rdi]
lea r13, [rbx + rsi]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r15, qword ptr [rbp - 112]
mov r13, qword ptr [r15]
mov rbx, r13
neg rbx
mov r15, qword ptr [rbp - 104]
mov qword ptr [r15], rbx
mov r15, qword ptr [rbp - 104]
mov rbx, qword ptr [r15]
cmp rbx, -10
sete bl
and bl, 1
mov cl, bl
call Assert
jmp label42
label42:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestAutoArray:
label43:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov qword ptr [r13], 10
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 8]
mov qword ptr [r12], 20
lea r12, qword ptr [rbp - 88]
lea r14, [r12 + 16]
mov qword ptr [r14], 30
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 24]
mov qword ptr [r12], 40
lea r12, qword ptr [rbp - 88]
lea r14, [r12 + 32]
mov qword ptr [r14], 50
mov cl, 1
call Assert
mov r12, qword ptr [r13]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r14]
cmp r12, 50
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, 0
mov r14, 0
jmp label45
label44:
lea r13, qword ptr [rbp - 88]
mov rdi, 0
imul rdi, 40
lea rsi, [r13 + rdi]
mov rdi, r12
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r14 + rdi]
jmp label46
label45:
cmp r12, 5
setl dil
and dil, 1
test dil, dil
jne label44
jmp label47
label46:
mov qword ptr [rbp - 96], r12
lea rdi, [r12 + 1]
mov r12, rdi
mov r14, r13
jmp label45
label47:
cmp r14, 150
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label48
label48:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayBoundary:
label49:
push rbp
mov rbp, rsp
sub rsp, 176
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 56]
lea r13, [r14]
mov qword ptr [r13], 42
mov r14, qword ptr [r13]
cmp r14, 42
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov cl, 1
call Assert
lea r14, qword ptr [rbp - 136]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r12, qword ptr [rbp - 136]
lea r14, [r12 + 16]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 24]
mov qword ptr [r12], 4
lea r12, qword ptr [rbp - 136]
lea r14, [r12 + 32]
mov qword ptr [r14], 5
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 40]
mov qword ptr [r12], 6
lea r12, qword ptr [rbp - 136]
lea r14, [r12 + 48]
mov qword ptr [r14], 7
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 56]
mov qword ptr [r12], 8
lea r12, qword ptr [rbp - 136]
lea r14, [r12 + 64]
mov qword ptr [r14], 9
lea r14, qword ptr [rbp - 136]
lea r12, [r14 + 72]
mov qword ptr [r12], 10
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [r12]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, 0
mov r12, 0
jmp label51
label50:
lea r13, qword ptr [rbp - 136]
mov rdi, 0
imul rdi, 80
lea rsi, [r13 + rdi]
mov rdi, r14
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r12 + rdi]
jmp label52
label51:
cmp r14, 10
setl dil
and dil, 1
test dil, dil
jne label50
jmp label53
label52:
mov qword ptr [rbp - 144], r14
lea rdi, [r14 + 1]
mov r14, rdi
mov r12, r13
jmp label51
label53:
cmp r12, 55
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label54
label54:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArraySwap:
label55:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r14, qword ptr [rbp - 88]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 3
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 24]
mov qword ptr [rbp - 96], r15
mov r15, qword ptr [rbp - 96]
mov qword ptr [r15], 4
lea r14, qword ptr [rbp - 88]
lea rbx, [r14 + 32]
mov qword ptr [rbx], 5
mov r14, qword ptr [r13]
mov rsi, qword ptr [rbx]
mov qword ptr [r13], rsi
mov qword ptr [rbx], r14
mov r14, qword ptr [r13]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbx]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [r12]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rdi]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 96]
mov r14, qword ptr [r15]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label56
label56:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayTernary:
label57:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 10
lea r14, qword ptr [rbp - 80]
lea r12, [r14 + 8]
mov qword ptr [r12], 20
lea r14, qword ptr [rbp - 80]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 30
mov r14, qword ptr [r13]
mov rsi, qword ptr [r12]
mov rbx, qword ptr [r13]
mov r13, qword ptr [r12]
cmp r14, rsi
setg sil
and sil, 1
test sil, sil
mov rsi, r13
cmovne rsi, rbx
cmp rsi, 20
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [rdi]
mov r13, qword ptr [rdi]
cmp rsi, rbx
setg bl
and bl, 1
test bl, bl
mov rbx, r13
cmovne rbx, rsi
cmp rbx, 30
sete bl
and bl, 1
mov cl, bl
call Assert
lea rbx, qword ptr [rbp - 80]
mov rsi, 0
imul rsi, 24
lea r13, [rbx + rsi]
mov rsi, 0
imul rsi, 8
lea rbx, [r13 + rsi]
mov rsi, qword ptr [rbx]
cmp rsi, 10
sete sil
and sil, 1
mov cl, sil
call Assert
jmp label58
label58:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayAssignment:
label59:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 80]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r12, qword ptr [rbp - 80]
lea r14, [r12 + 16]
mov qword ptr [r14], 3
mov r14, 0
jmp label61
label60:
lea r12, qword ptr [rbp - 104]
lea rdi, qword ptr [rbp - 80]
mov rsi, 0
imul rsi, 24
lea rbx, [rdi + rsi]
mov rsi, r14
imul rsi, 8
lea rdi, [rbx + rsi]
mov rsi, qword ptr [rdi]
mov rdi, 0
imul rdi, 24
lea rbx, [r12 + rdi]
mov rdi, r14
imul rdi, 8
lea r12, [rbx + rdi]
mov qword ptr [r12], rsi
jmp label62
label61:
cmp r14, 3
setl r12b
and r12b, 1
test r12b, r12b
jne label60
jmp label63
label62:
mov qword ptr [rbp - 112], r14
lea r12, [r14 + 1]
mov r14, r12
jmp label61
label63:
lea r12, qword ptr [rbp - 104]
lea r14, [r12]
mov r12, qword ptr [r14]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 104]
lea rsi, [r12 + 8]
mov r12, qword ptr [rsi]
cmp r12, 2
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 104]
lea rsi, [r12 + 16]
mov r12, qword ptr [rsi]
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [r13], 100
mov r12, qword ptr [r13]
cmp r12, 100
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r14]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label64
label64:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayAccumulation:
label65:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov qword ptr [r13], 0
lea r14, qword ptr [rbp - 88]
lea r12, [r14 + 8]
mov qword ptr [r12], 0
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 16]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 112]
mov qword ptr [r15], 0
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 24]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [r15], 0
lea r14, qword ptr [rbp - 88]
lea r15, [r14 + 32]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [r15], 0
mov r14, 0
jmp label67
label66:
lea rbx, qword ptr [rbp - 88]
mov rsi, 0
imul rsi, 40
lea rdi, [rbx + rsi]
mov rax, r14
cqo
mov rsi, 5
idiv rsi
mov rsi, rdx
mov rbx, rsi
imul rbx, 8
lea rsi, [rdi + rbx]
mov rbx, qword ptr [rsi]
mov qword ptr [rbp - 96], rbx
lea rdi, [rbx + 1]
mov qword ptr [rsi], rdi
jmp label68
label67:
cmp r14, 100
setl dil
and dil, 1
test dil, dil
jne label66
jmp label69
label68:
mov qword ptr [rbp - 104], r14
lea rdi, [r14 + 1]
mov r14, rdi
jmp label67
label69:
mov rdi, qword ptr [r13]
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
mov rdi, qword ptr [r12]
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
mov r15, qword ptr [rbp - 112]
mov rdi, qword ptr [r15]
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
mov r15, qword ptr [rbp - 120]
mov rdi, qword ptr [r15]
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
mov r15, qword ptr [rbp - 128]
mov rdi, qword ptr [r15]
cmp rdi, 20
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label70
label70:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
SumArray__I5:
label71:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, rcx
mov r13, qword ptr [r14]
lea r12, qword ptr [rbp - 144]
mov rdi, r14
add rdi, 8
mov rsi, qword ptr [rdi]
mov rdi, r12
add rdi, 8
mov qword ptr [r12], r13
mov r13, r14
add r13, 16
mov rbx, qword ptr [r13]
mov r13, r12
add r13, 16
mov qword ptr [rdi], rsi
mov rdi, r14
add rdi, 24
mov rsi, qword ptr [rdi]
mov rdi, r12
add rdi, 24
mov qword ptr [r13], rbx
mov r13, r14
add r13, 32
mov r14, qword ptr [r13]
mov r13, r12
add r13, 32
mov qword ptr [rdi], rsi
mov qword ptr [r13], r14
lea r13, qword ptr [rbp - 144]
lea r14, qword ptr [rbp - 96]
mov rdi, qword ptr [r13]
mov rsi, r13
add rsi, 8
mov r12, qword ptr [rsi]
mov rsi, r14
add rsi, 8
mov qword ptr [r14], rdi
mov rdi, r13
add rdi, 16
mov rbx, qword ptr [rdi]
mov rdi, r14
add rdi, 16
mov qword ptr [rsi], r12
mov rsi, r13
add rsi, 24
mov r12, qword ptr [rsi]
mov rsi, r14
add rsi, 24
mov qword ptr [rdi], rbx
mov rdi, r13
add rdi, 32
mov r13, qword ptr [rdi]
mov rdi, r14
add rdi, 32
mov qword ptr [rsi], r12
mov qword ptr [rdi], r13
mov rdi, 0
mov r13, 0
jmp label73
label72:
lea rsi, qword ptr [rbp - 96]
mov r12, 0
imul r12, 40
lea r14, [rsi + r12]
mov r12, rdi
imul r12, 8
lea rsi, [r14 + r12]
mov r12, qword ptr [rsi]
lea rsi, [r13 + r12]
jmp label74
label73:
cmp rdi, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label72
jmp label75
label74:
mov qword ptr [rbp - 104], rdi
lea r12, [rdi + 1]
mov rdi, r12
mov r13, rsi
jmp label73
label75:
mov rax, r13
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayPassByValue:
label76:
push rbp
mov rbp, rsp
sub rsp, 240
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 8]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 16]
mov qword ptr [r13], 6
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 24]
mov qword ptr [r14], 8
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 32]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 96]
lea r14, qword ptr [rbp - 136]
mov r12, qword ptr [r13]
mov rdi, r13
add rdi, 8
mov rsi, qword ptr [rdi]
mov rdi, r14
add rdi, 8
mov qword ptr [r14], r12
mov r12, r13
add r12, 16
mov rbx, qword ptr [r12]
mov r12, r14
add r12, 16
mov qword ptr [rdi], rsi
mov rdi, r13
add rdi, 24
mov rsi, qword ptr [rdi]
mov rdi, r14
add rdi, 24
mov qword ptr [r12], rbx
mov r12, r13
add r12, 32
mov r13, qword ptr [r12]
mov r12, r14
add r12, 32
mov qword ptr [rdi], rsi
mov qword ptr [r12], r13
mov rcx, r14
call SumArray__I5
mov r14, rax
cmp r14, 30
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 160]
lea r12, [r14]
mov qword ptr [r12], 1
lea r14, qword ptr [rbp - 160]
lea r13, [r14 + 8]
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 160]
lea r14, [r13 + 16]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 160]
lea r13, qword ptr [rbp - 184]
mov rdi, qword ptr [r14]
mov rsi, r14
add rsi, 8
mov rbx, qword ptr [rsi]
mov rsi, r13
add rsi, 8
mov qword ptr [r13], rdi
mov rdi, r14
add rdi, 16
mov r14, qword ptr [rdi]
mov rdi, r13
add rdi, 16
mov qword ptr [rsi], rbx
mov qword ptr [rdi], r14
jmp label78
label77:
mov rdi, qword ptr [r12]
cmp rdi, 1
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label79
label78:
mov rdi, r13
lea r13, qword ptr [rbp - 208]
mov r14, qword ptr [rdi]
mov rsi, rdi
add rsi, 8
mov rbx, qword ptr [rsi]
mov rsi, r13
add rsi, 8
mov qword ptr [r13], r14
mov r14, rdi
add r14, 16
mov rdi, qword ptr [r14]
mov r14, r13
add r14, 16
mov qword ptr [rsi], rbx
mov qword ptr [r14], rdi
lea r14, qword ptr [rbp - 208]
lea rdi, [r14]
mov qword ptr [rdi], 999
jmp label77
label79:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
ZeroArray__I5ref:
label80:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, rcx
mov r13, 0
jmp label82
label81:
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov r12, r13
imul r12, 8
lea rsi, [rdi + r12]
mov qword ptr [rsi], 0
jmp label83
label82:
cmp r13, 5
setl sil
and sil, 1
test sil, sil
jne label81
jmp label84
label83:
mov qword ptr [rbp - 48], r13
lea rsi, [r13 + 1]
mov r13, rsi
jmp label82
label84:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayPassByRef:
label85:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 32]
mov qword ptr [r13], 5
lea rcx, qword ptr [rbp - 72]
call ZeroArray__I5ref
mov r13, 0
jmp label87
label86:
lea r14, qword ptr [rbp - 72]
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r14, [rdi + r12]
mov r12, qword ptr [r14]
cmp r12, 0
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label88
label87:
cmp r13, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label86
jmp label89
label88:
mov qword ptr [rbp - 80], r13
lea r12, [r13 + 1]
mov r13, r12
jmp label87
label89:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
ReverseArray__I5ref:
label90:
push rbp
mov rbp, rsp
sub rsp, 80
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, rcx
mov r15, 4
mov qword ptr [rbp - 72], r15
mov r15, 0
mov qword ptr [rbp - 80], r15
jmp label91
label91:
mov r15, qword ptr [rbp - 80]
mov rax, qword ptr [rbp - 72]
cmp r15, rax
setl dil
and dil, 1
test dil, dil
jne label92
jmp label93
label92:
mov rdi, 0
imul rdi, 40
lea rsi, [r14 + rdi]
mov r15, qword ptr [rbp - 80]
mov rdi, r15
imul rdi, 8
lea rbx, [rsi + rdi]
mov rdi, qword ptr [rbx]
mov rsi, 0
imul rsi, 40
lea r12, [r14 + rsi]
mov r15, qword ptr [rbp - 72]
mov rsi, r15
imul rsi, 8
lea r13, [r12 + rsi]
mov rsi, qword ptr [r13]
mov qword ptr [rbx], rsi
mov qword ptr [r13], rdi
mov r15, qword ptr [rbp - 80]
mov qword ptr [rbp - 56], r15
mov r15, qword ptr [rbp - 80]
lea r13, [r15 + 1]
mov r15, qword ptr [rbp - 72]
mov qword ptr [rbp - 64], r15
mov r15, qword ptr [rbp - 72]
mov rdi, r15
sub rdi, 1
mov r15, rdi
mov qword ptr [rbp - 72], r15
mov r15, r13
mov qword ptr [rbp - 80], r15
jmp label91
label93:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayReverse:
label94:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 96]
lea r12, [r14 + 8]
mov qword ptr [r12], 2
lea r14, qword ptr [rbp - 96]
lea rdi, [r14 + 16]
mov qword ptr [rdi], 3
lea r14, qword ptr [rbp - 96]
lea rsi, [r14 + 24]
mov qword ptr [rsi], 4
lea r14, qword ptr [rbp - 96]
lea rbx, [r14 + 32]
mov qword ptr [rbx], 5
lea rcx, qword ptr [rbp - 96]
call ReverseArray__I5ref
mov r14, qword ptr [r13]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [r12]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rdi]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rsi]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbx]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label95
label95:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayBubbleSort:
label96:
push rbp
mov rbp, rsp
sub rsp, 208
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 5
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 8]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [r15], 3
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 16]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [r15], 1
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 24]
mov qword ptr [rbp - 136], r15
mov r15, qword ptr [rbp - 136]
mov qword ptr [r15], 4
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 32]
mov qword ptr [rbp - 144], r15
mov r15, qword ptr [rbp - 144]
mov qword ptr [r15], 2
mov r15, 0
mov qword ptr [rbp - 152], r15
jmp label98
label97:
mov r15, 4
mov qword ptr [rbp - 160], r15
mov r15, qword ptr [rbp - 152]
sub r15, r15
mov qword ptr [rbp - 160], r15
mov r15, 0
mov qword ptr [rbp - 168], r15
jmp label103
label98:
mov r15, qword ptr [rbp - 152]
cmp r15, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label97
jmp label100
label99:
mov r15, qword ptr [rbp - 152]
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 152]
lea r14, [r15 + 1]
mov r15, r14
mov qword ptr [rbp - 152], r15
jmp label98
label100:
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 120]
mov r14, qword ptr [r15]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 128]
mov r14, qword ptr [r15]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 136]
mov r14, qword ptr [r15]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r15, qword ptr [rbp - 144]
mov r14, qword ptr [r15]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label106
label101:
lea r14, qword ptr [rbp - 96]
lea rbx, qword ptr [rbp - 96]
mov rsi, 0
imul rsi, 40
lea rdi, [r14 + rsi]
mov r15, qword ptr [rbp - 168]
mov rsi, r15
imul rsi, 8
lea r14, [rdi + rsi]
mov rsi, qword ptr [r14]
mov rdi, 0
imul rdi, 40
lea r12, [rbx + rdi]
mov r15, qword ptr [rbp - 168]
lea r15, [r15 + 1]
mov qword ptr [rbp - 176], r15
mov r15, qword ptr [rbp - 176]
mov rbx, r15
imul rbx, 8
lea rdi, [r12 + rbx]
mov rbx, qword ptr [rdi]
cmp rsi, rbx
setg bl
and bl, 1
test bl, bl
jne label105
jmp label102
label102:
jmp label104
label103:
mov r15, qword ptr [rbp - 168]
mov rax, qword ptr [rbp - 160]
cmp r15, rax
setl bl
and bl, 1
test bl, bl
jne label101
jmp label99
label104:
mov r15, qword ptr [rbp - 168]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 176]
mov r15, r15
mov qword ptr [rbp - 168], r15
jmp label103
label105:
mov rbx, qword ptr [r14]
mov rsi, qword ptr [rdi]
mov qword ptr [r14], rsi
mov qword ptr [rdi], rbx
jmp label104
label106:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayCountMatches:
label107:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 112]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 112]
lea r14, [r13 + 8]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 112]
lea r13, [r14 + 16]
mov qword ptr [r13], 5
lea r13, qword ptr [rbp - 112]
lea r14, [r13 + 24]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 112]
lea r13, [r14 + 32]
mov qword ptr [r13], 7
lea r13, qword ptr [rbp - 112]
lea r14, [r13 + 40]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 112]
lea r13, [r14 + 48]
mov qword ptr [r13], 9
lea r13, qword ptr [rbp - 112]
lea r14, [r13 + 56]
mov qword ptr [r14], 3
mov r14, 0
mov r13, 0
jmp label110
label108:
lea r12, qword ptr [rbp - 112]
mov rdi, 0
imul rdi, 64
lea rsi, [r12 + rdi]
mov rdi, r14
imul rdi, 8
lea r12, [rsi + rdi]
mov rdi, qword ptr [r12]
cmp rdi, 3
sete dil
and dil, 1
test dil, dil
jne label113
jmp label109
label109:
mov rdi, r13
jmp label114
label110:
cmp r14, 8
setl r12b
and r12b, 1
test r12b, r12b
jne label108
jmp label112
label111:
mov qword ptr [rbp - 120], r14
lea r12, [r14 + 1]
mov r14, r12
mov r13, rdi
jmp label110
label112:
cmp r13, 4
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label115
label113:
mov qword ptr [rbp - 128], r13
lea r12, [r13 + 1]
mov rdi, r12
jmp label114
label114:
jmp label111
label115:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayPrefixSum:
label116:
push rbp
mov rbp, rsp
sub rsp, 176
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 8]
mov qword ptr [rbp - 112], r15
mov r15, qword ptr [rbp - 112]
mov qword ptr [r15], 2
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 16]
mov qword ptr [rbp - 120], r15
mov r15, qword ptr [rbp - 120]
mov qword ptr [r15], 3
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 24]
mov qword ptr [rbp - 128], r15
mov r15, qword ptr [rbp - 128]
mov qword ptr [r15], 4
lea r14, qword ptr [rbp - 96]
lea r15, [r14 + 32]
mov qword ptr [rbp - 136], r15
mov r15, qword ptr [rbp - 136]
mov qword ptr [r15], 5
mov r15, 1
mov qword ptr [rbp - 144], r15
jmp label118
label117:
lea rbx, qword ptr [rbp - 96]
mov rsi, 0
imul rsi, 40
lea rdi, [rbx + rsi]
mov r15, qword ptr [rbp - 144]
mov rsi, r15
imul rsi, 8
lea rbx, [rdi + rsi]
lea rsi, qword ptr [rbp - 96]
mov rdi, qword ptr [rbx]
mov r12, 0
imul r12, 40
lea r14, [rsi + r12]
mov r15, qword ptr [rbp - 144]
mov r12, r15
sub r12, 1
mov rsi, r12
imul rsi, 8
lea r12, [r14 + rsi]
mov rsi, qword ptr [r12]
lea r12, [rdi + rsi]
mov qword ptr [rbx], r12
jmp label119
label118:
mov r15, qword ptr [rbp - 144]
cmp r15, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label117
jmp label120
label119:
mov r15, qword ptr [rbp - 144]
mov qword ptr [rbp - 104], r15
mov r15, qword ptr [rbp - 144]
lea r12, [r15 + 1]
mov r15, r12
mov qword ptr [rbp - 144], r15
jmp label118
label120:
mov r12, qword ptr [r13]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r15, qword ptr [rbp - 112]
mov r12, qword ptr [r15]
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r15, qword ptr [rbp - 120]
mov r12, qword ptr [r15]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r15, qword ptr [rbp - 128]
mov r12, qword ptr [r15]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r15, qword ptr [rbp - 136]
mov r12, qword ptr [r15]
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label121
label121:
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
label122:
push rbp
mov rbp, rsp
sub rsp, 32
call TestGlobalArrays
call TestLocalArrays
call TestFloatArrays
call TestBoolArrays
call TestArrayModification
call TestArrayExpressions
call TestArrayVariableIndex
call TestArrayInLoops
call TestArrayWhileLoop
jmp label124
label123:
call TestArrayNegativeValues
call TestAutoArray
call TestArrayBoundary
call TestArraySwap
call TestArrayTernary
call TestArrayAssignment
call TestArrayAccumulation
call TestArrayPassByValue
call TestArrayPassByRef
call TestArrayReverse
call TestArrayBubbleSort
call TestArrayCountMatches
call TestArrayPrefixSum
jmp label125
label124:
mov cl, 1
call Assert
mov cl, 1
call Assert
mov cl, 1
call Assert
mov cl, 1
call Assert
mov cl, 1
call Assert
mov cl, 1
call Assert
jmp label123
label125:
mov rax, 0
mov rsp, rbp
pop rbp
ret
