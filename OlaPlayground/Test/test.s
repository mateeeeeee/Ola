.intel_syntax noprefix

.section .rodata

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


.data

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
sub rsp, 160
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
lea r14, qword ptr [rbp - 104]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 16]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 24]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 32]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 40]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 48]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 56]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 64]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 72]
mov qword ptr [r14], 0
mov cl, 1
call Assert
lea r14, qword ptr [rbp - 104]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 48]
mov r14, qword ptr [r13]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 128]
lea r13, [r14]
mov qword ptr [r13], -5
lea r13, qword ptr [rbp - 128]
lea r14, [r13 + 8]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 128]
lea r13, [r14 + 16]
mov qword ptr [r13], 5
lea r13, qword ptr [rbp - 128]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, -5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 128]
lea r14, [r13 + 8]
mov r13, qword ptr [r14]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 128]
lea r14, [r13 + 16]
mov r13, qword ptr [r14]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov cl, 1
call Assert
jmp label3
label3:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestFloatArrays:
label4:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
movsd qword ptr [rbp - 32], xmm14
movsd qword ptr [rbp - 40], xmm13
movsd qword ptr [rbp - 48], xmm12
movsd qword ptr [rbp - 56], xmm11
movsd qword ptr [rbp - 64], xmm10
lea r14, [rip + GlobalFloatArray]
lea r13, [r14]
movsd xmm14, qword ptr [r13]
lea r13, [rip + GlobalFloatArray]
lea r14, [r13]
movsd xmm13, qword ptr [r14]
comisd xmm14, qword ptr [rip + _FP0]
seta r14b
and r14b, 1
comisd xmm13, qword ptr [rip + _FP1]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, [rip + GlobalFloatArray]
lea r13, [r12 + 8]
movsd xmm13, qword ptr [r13]
lea r13, [rip + GlobalFloatArray]
lea r12, [r13 + 8]
movsd xmm14, qword ptr [r12]
comisd xmm13, qword ptr [rip + _FP2]
seta r12b
and r12b, 1
comisd xmm14, qword ptr [rip + _FP3]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalFloatArray]
lea r13, [r14 + 16]
movsd xmm14, qword ptr [r13]
lea r13, [rip + GlobalFloatArray]
lea r14, [r13 + 16]
movsd xmm13, qword ptr [r14]
comisd xmm14, qword ptr [rip + _FP4]
seta r14b
and r14b, 1
comisd xmm13, qword ptr [rip + _FP5]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 104]
lea r13, [r12]
movsd xmm13, qword ptr [rip + _FP6]
movsd qword ptr [r13], xmm13
lea r13, qword ptr [rbp - 104]
lea r12, [r13 + 8]
movsd xmm13, qword ptr [rip + _FP7]
movsd qword ptr [r12], xmm13
lea r12, qword ptr [rbp - 104]
lea r13, [r12 + 16]
movsd xmm13, qword ptr [rip + _FP8]
movsd qword ptr [r13], xmm13
lea r13, qword ptr [rbp - 104]
lea r12, [r13 + 24]
movsd xmm13, qword ptr [rip + _FP9]
movsd qword ptr [r12], xmm13
lea r12, qword ptr [rbp - 104]
lea r13, [r12]
movsd xmm13, qword ptr [r13]
lea r13, qword ptr [rbp - 104]
lea r12, [r13]
movsd xmm14, qword ptr [r12]
comisd xmm13, qword ptr [rip + _FP10]
seta r12b
and r12b, 1
comisd xmm14, qword ptr [rip + _FP11]
setb r13b
and r13b, 1
mov r14b, r12b
and r14b, r13b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 24]
movsd xmm14, qword ptr [r13]
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 24]
movsd xmm13, qword ptr [r14]
comisd xmm14, qword ptr [rip + _FP12]
seta r14b
and r14b, 1
comisd xmm13, qword ptr [rip + _FP13]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 104]
lea r13, qword ptr [rbp - 104]
lea r14, [r12]
movsd xmm13, qword ptr [r14]
lea r14, [r13 + 8]
movsd xmm14, qword ptr [r14]
lea r14, qword ptr [rbp - 104]
lea r13, [r14 + 16]
movsd xmm12, qword ptr [r13]
lea r13, qword ptr [rbp - 104]
lea r14, [r13 + 24]
movsd xmm11, qword ptr [r14]
movsd xmm10, xmm13
addsd xmm10, xmm14
movsd xmm14, xmm10
addsd xmm14, xmm12
movsd xmm12, xmm14
addsd xmm12, xmm11
movsd qword ptr [rbp - 112], xmm12
movsd xmm12, qword ptr [rbp - 112]
movsd xmm11, qword ptr [rbp - 112]
comisd xmm12, qword ptr [rip + _FP14]
seta r14b
and r14b, 1
comisd xmm11, qword ptr [rip + _FP15]
setb r13b
and r13b, 1
mov r12b, r14b
and r12b, r13b
cmp r12b, 0
setne r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label5
label5:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
movsd xmm14, qword ptr [rbp - 32]
movsd xmm13, qword ptr [rbp - 40]
movsd xmm12, qword ptr [rbp - 48]
movsd xmm11, qword ptr [rbp - 56]
movsd xmm10, qword ptr [rbp - 64]
mov rsp, rbp
pop rbp
ret
TestBoolArrays:
label6:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
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
lea r14, qword ptr [rbp - 32]
lea r13, [r14]
mov byte ptr [r13], 1
lea r13, qword ptr [rbp - 32]
lea r14, [r13 + 1]
mov byte ptr [r14], 1
lea r14, qword ptr [rbp - 32]
lea r13, [r14 + 2]
mov byte ptr [r13], 0
lea r13, qword ptr [rbp - 32]
lea r14, [r13]
mov r13b, byte ptr [r14]
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 32]
lea r14, [r13 + 1]
mov r13b, byte ptr [r14]
cmp r13b, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 32]
lea r14, [r13 + 2]
mov r13b, byte ptr [r14]
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label7
label7:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestArrayModification:
label8:
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
lea r13, qword ptr [rbp - 72]
lea r14, [r13]
mov qword ptr [r14], 10
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 32]
mov qword ptr [r13], 50
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 32]
mov r13, qword ptr [r14]
cmp r13, 50
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea r14, qword ptr [rbp - 72]
lea r12, qword ptr [rbp - 72]
lea rdi, [r14]
mov r14, qword ptr [rdi]
lea rdi, [r12 + 32]
mov r12, qword ptr [rdi]
lea rdi, [r14 + r12]
lea r12, [r13 + 16]
mov qword ptr [r12], rdi
lea r12, qword ptr [rbp - 72]
lea rdi, [r12 + 16]
mov r12, qword ptr [rdi]
cmp r12, 60
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 72]
lea rdi, qword ptr [rbp - 72]
lea r13, [rdi + 8]
mov rdi, qword ptr [r13]
mov r13, rdi
imul r13, 2
lea rdi, [r12 + 8]
mov qword ptr [rdi], r13
lea rdi, qword ptr [rbp - 72]
lea r13, [rdi + 8]
mov rdi, qword ptr [r13]
cmp rdi, 4
sete dil
and dil, 1
mov cl, dil
call Assert
lea rdi, qword ptr [rbp - 72]
lea r13, [rdi + 24]
mov rdi, qword ptr [r13]
mov qword ptr [rbp - 80], rdi
lea r12, [rdi + 1]
mov qword ptr [r13], r12
lea r12, qword ptr [rbp - 72]
lea r13, [r12 + 24]
mov r12, qword ptr [r13]
cmp r12, 5
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 72]
lea r13, [r12 + 24]
mov r12, qword ptr [r13]
lea rdi, [r12 + 1]
mov qword ptr [r13], rdi
lea rdi, qword ptr [rbp - 72]
lea r13, [rdi + 24]
mov rdi, qword ptr [r13]
cmp rdi, 6
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label9
label9:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
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
lea r14, qword ptr [rbp - 95]
lea r13, [r14]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 95]
lea r14, [r13 + 8]
mov qword ptr [r14], 20
lea r14, qword ptr [rbp - 95]
lea r13, [r14 + 16]
mov qword ptr [r13], 30
lea r13, qword ptr [rbp - 95]
lea r14, [r13 + 24]
mov qword ptr [r14], 40
lea r14, qword ptr [rbp - 95]
lea r13, [r14 + 32]
mov qword ptr [r13], 50
lea r13, qword ptr [rbp - 95]
lea r14, qword ptr [rbp - 95]
lea r12, [r13]
mov r13, qword ptr [r12]
lea r12, [r14 + 8]
mov r14, qword ptr [r12]
lea r12, qword ptr [rbp - 95]
lea rdi, [r12 + 16]
mov r12, qword ptr [rdi]
lea rdi, qword ptr [rbp - 95]
lea rsi, [rdi + 24]
mov rdi, qword ptr [rsi]
lea rsi, qword ptr [rbp - 95]
lea rbx, [rsi + 32]
mov rsi, qword ptr [rbx]
lea rbx, [r13 + r14]
lea r14, [rbx + r12]
lea rbx, [r14 + rdi]
lea r14, [rbx + rsi]
mov qword ptr [rbp - 103], r14
mov r14, qword ptr [rbp - 103]
cmp r14, 150
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 95]
lea rbx, qword ptr [rbp - 95]
lea rsi, [r14]
mov r14, qword ptr [rsi]
lea rsi, [rbx + 8]
mov rbx, qword ptr [rsi]
mov rsi, r14
imul rsi, rbx
mov qword ptr [rbp - 111], rsi
mov rsi, qword ptr [rbp - 111]
cmp rsi, 200
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 95]
lea rbx, qword ptr [rbp - 95]
lea r14, [rsi + 32]
mov rsi, qword ptr [r14]
lea r14, [rbx]
mov rbx, qword ptr [r14]
mov r14, rsi
sub r14, rbx
mov qword ptr [rbp - 119], r14
mov r14, qword ptr [rbp - 119]
cmp r14, 40
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 95]
lea rbx, qword ptr [rbp - 95]
lea rsi, [r14 + 32]
mov r14, qword ptr [rsi]
lea rsi, [rbx]
mov rbx, qword ptr [rsi]
cmp r14, rbx
setg bl
and bl, 1
mov byte ptr [rbp - 120], bl
mov bl, byte ptr [rbp - 120]
cmp bl, 1
sete bl
and bl, 1
mov cl, bl
call Assert
lea rbx, qword ptr [rbp - 95]
lea r14, qword ptr [rbp - 95]
lea rsi, [rbx]
mov rbx, qword ptr [rsi]
lea rsi, [r14 + 8]
mov r14, qword ptr [rsi]
lea rsi, qword ptr [rbp - 95]
lea rdi, [rsi + 16]
mov rsi, qword ptr [rdi]
lea rdi, [rbx + r14]
lea r14, [rdi + rsi]
mov rax, r14
cqo
mov r14, 3
idiv r14
mov r14, rax
mov qword ptr [rbp - 128], r14
mov r14, qword ptr [rbp - 128]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
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
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov qword ptr [r13], 100
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 8]
mov qword ptr [r14], 200
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 16]
mov qword ptr [r13], 300
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 24]
mov qword ptr [r14], 400
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 32]
mov qword ptr [r13], 500
mov qword ptr [rbp - 80], 0
mov r13, qword ptr [rbp - 80]
lea r14, qword ptr [rbp - 72]
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rdi + r12]
mov r12, qword ptr [r13]
cmp r12, 100
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov qword ptr [rbp - 80], 2
mov r12, qword ptr [rbp - 80]
lea r13, qword ptr [rbp - 72]
mov rdi, 0
imul rdi, 40
lea r14, [r13 + rdi]
mov rdi, r12
imul rdi, 8
lea r12, [r14 + rdi]
mov rdi, qword ptr [r12]
cmp rdi, 300
sete dil
and dil, 1
mov cl, dil
call Assert
mov qword ptr [rbp - 88], 4
mov rdi, qword ptr [rbp - 88]
lea r12, qword ptr [rbp - 72]
mov r14, 0
imul r14, 40
lea r13, [r12 + r14]
mov r14, rdi
imul r14, 8
lea rdi, [r13 + r14]
mov r14, qword ptr [rdi]
cmp r14, 500
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 96], 1
mov r14, qword ptr [rbp - 96]
lea rdi, qword ptr [rbp - 72]
mov r13, 0
imul r13, 40
lea r12, [rdi + r13]
lea r13, [r14 + 1]
mov r14, r13
imul r14, 8
lea r13, [r12 + r14]
mov r14, qword ptr [r13]
cmp r14, 300
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov r14, qword ptr [rbp - 88]
lea r13, qword ptr [rbp - 72]
mov r12, 0
imul r12, 40
lea rdi, [r13 + r12]
mov r12, r14
sub r12, 2
mov r14, r12
imul r14, 8
lea r12, [rdi + r14]
mov r14, qword ptr [r12]
cmp r14, 300
sete r14b
and r14b, 1
mov cl, r14b
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
sub rsp, 192
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 32]
mov qword ptr [r13], 5
mov qword ptr [rbp - 104], 0
mov qword ptr [rbp - 112], 0
jmp label16
label15:
mov r13, qword ptr [rbp - 112]
lea r14, qword ptr [rbp - 96]
mov r12, qword ptr [rbp - 104]
mov rdi, 0
imul rdi, 40
lea rsi, [r14 + rdi]
mov rdi, r13
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r12 + rdi]
mov qword ptr [rbp - 104], r13
jmp label17
label16:
mov r13, qword ptr [rbp - 112]
cmp r13, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label15
jmp label18
label17:
mov r13, qword ptr [rbp - 112]
mov qword ptr [rbp - 120], r13
lea rdi, [r13 + 1]
mov qword ptr [rbp - 112], rdi
jmp label16
label18:
mov rdi, qword ptr [rbp - 104]
cmp rdi, 15
sete dil
and dil, 1
mov cl, dil
call Assert
mov qword ptr [rbp - 128], 0
jmp label20
label19:
mov rdi, qword ptr [rbp - 128]
lea r13, qword ptr [rbp - 96]
mov r12, qword ptr [rbp - 128]
lea rsi, qword ptr [rbp - 96]
mov r14, 0
imul r14, 40
lea rbx, [rsi + r14]
mov r14, r12
imul r14, 8
lea r12, [rbx + r14]
mov r14, qword ptr [r12]
mov r12, r14
imul r12, 2
mov r14, 0
imul r14, 40
lea rbx, [r13 + r14]
mov r14, rdi
imul r14, 8
lea rdi, [rbx + r14]
mov qword ptr [rdi], r12
jmp label21
label20:
mov rdi, qword ptr [rbp - 128]
cmp rdi, 5
setl dil
and dil, 1
test dil, dil
jne label19
jmp label22
label21:
mov rdi, qword ptr [rbp - 128]
mov qword ptr [rbp - 136], rdi
lea r12, [rdi + 1]
mov qword ptr [rbp - 128], r12
jmp label20
label22:
lea r12, qword ptr [rbp - 96]
lea rdi, [r12]
mov r12, qword ptr [rdi]
cmp r12, 2
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea rdi, [r12 + 8]
mov r12, qword ptr [rdi]
cmp r12, 4
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea rdi, [r12 + 16]
mov r12, qword ptr [rdi]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea rdi, [r12 + 24]
mov r12, qword ptr [rdi]
cmp r12, 8
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea rdi, [r12 + 32]
mov r12, qword ptr [rdi]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea rdi, [r12]
mov r12, qword ptr [rdi]
mov qword ptr [rbp - 144], r12
mov qword ptr [rbp - 152], 1
jmp label24
label23:
mov r12, qword ptr [rbp - 152]
lea rdi, qword ptr [rbp - 96]
mov r14, 0
imul r14, 40
lea rbx, [rdi + r14]
mov r14, r12
imul r14, 8
lea r12, [rbx + r14]
mov r14, qword ptr [r12]
mov r12, qword ptr [rbp - 144]
cmp r14, r12
setg r12b
and r12b, 1
test r12b, r12b
jne label27
jmp label29
label24:
mov r12, qword ptr [rbp - 152]
cmp r12, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label23
jmp label26
label25:
mov r12, qword ptr [rbp - 152]
mov qword ptr [rbp - 160], r12
lea r14, [r12 + 1]
mov qword ptr [rbp - 152], r14
jmp label24
label26:
jmp label30
label27:
mov r14, qword ptr [rbp - 152]
lea r12, qword ptr [rbp - 96]
mov rbx, 0
imul rbx, 40
lea rdi, [r12 + rbx]
mov rbx, r14
imul rbx, 8
lea r14, [rdi + rbx]
mov rbx, qword ptr [r14]
mov qword ptr [rbp - 144], rbx
jmp label29
label28:
label29:
jmp label25
label30:
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
label31:
push rbp
mov rbp, rsp
sub rsp, 144
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
mov qword ptr [rbp - 88], 0
mov qword ptr [rbp - 96], 0
jmp label32
label32:
mov r13, qword ptr [rbp - 88]
cmp r13, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label33
jmp label34
label33:
mov r13, qword ptr [rbp - 88]
lea r14, qword ptr [rbp - 80]
mov r12, qword ptr [rbp - 96]
mov rdi, 0
imul rdi, 40
lea rsi, [r14 + rdi]
mov rdi, r13
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r12 + rdi]
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbp - 88]
mov qword ptr [rbp - 104], r13
lea rdi, [r13 + 1]
mov qword ptr [rbp - 88], rdi
jmp label32
label34:
mov rdi, qword ptr [rbp - 96]
cmp rdi, 15
sete dil
and dil, 1
mov cl, dil
call Assert
mov qword ptr [rbp - 88], 0
jmp label35
label35:
mov rdi, qword ptr [rbp - 88]
cmp rdi, 5
setl dil
and dil, 1
test dil, dil
jne label36
jmp label37
label36:
mov rdi, qword ptr [rbp - 88]
lea r13, qword ptr [rbp - 80]
mov r12, 0
imul r12, 40
lea rsi, [r13 + r12]
mov r12, rdi
imul r12, 8
lea rdi, [rsi + r12]
mov r12, qword ptr [rdi]
mov rax, r12
cqo
mov r12, 2
idiv r12
mov r12, rdx
cmp r12, 0
sete r12b
and r12b, 1
test r12b, r12b
jne label38
jmp label40
label37:
mov r12, qword ptr [rbp - 88]
lea rdi, qword ptr [rbp - 80]
mov rsi, 0
imul rsi, 40
lea r13, [rdi + rsi]
mov rsi, r12
imul rsi, 8
lea r12, [r13 + rsi]
mov rsi, qword ptr [r12]
cmp rsi, 4
sete sil
and sil, 1
mov cl, sil
call Assert
jmp label42
label38:
jmp label37
label39:
label40:
mov rsi, qword ptr [rbp - 88]
mov qword ptr [rbp - 112], rsi
lea r12, [rsi + 1]
mov qword ptr [rbp - 88], r12
jmp label35
label41:
label42:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayLengthSizeof:
label43:
push rbp
mov rbp, rsp
sub rsp, 160
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
jmp label44
label44:
mov rsp, rbp
pop rbp
ret
TestArrayNegativeValues:
label45:
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
mov qword ptr [r13], -10
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 8]
mov qword ptr [r14], -5
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 16]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 24]
mov qword ptr [r14], 5
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 32]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 88]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, -10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 8]
mov r13, qword ptr [r14]
cmp r13, -5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 16]
mov r13, qword ptr [r14]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 24]
mov r13, qword ptr [r14]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 32]
mov r13, qword ptr [r14]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, qword ptr [rbp - 88]
lea r12, [r13]
mov r13, qword ptr [r12]
lea r12, [r14 + 8]
mov r14, qword ptr [r12]
lea r12, qword ptr [rbp - 88]
lea rdi, [r12 + 16]
mov r12, qword ptr [rdi]
lea rdi, qword ptr [rbp - 88]
lea rsi, [rdi + 24]
mov rdi, qword ptr [rsi]
lea rsi, qword ptr [rbp - 88]
lea rbx, [rsi + 32]
mov rsi, qword ptr [rbx]
lea rbx, [r13 + r14]
lea r14, [rbx + r12]
lea rbx, [r14 + rdi]
lea r14, [rbx + rsi]
mov qword ptr [rbp - 96], r14
mov r14, qword ptr [rbp - 96]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 88]
lea rbx, qword ptr [rbp - 88]
lea rsi, [rbx + 32]
mov rbx, qword ptr [rsi]
mov rsi, rbx
neg rsi
lea rbx, [r14]
mov qword ptr [rbx], rsi
lea rbx, qword ptr [rbp - 88]
lea rsi, [rbx]
mov rbx, qword ptr [rsi]
cmp rbx, -10
sete bl
and bl, 1
mov cl, bl
call Assert
jmp label46
label46:
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
label47:
push rbp
mov rbp, rsp
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 8]
mov qword ptr [r14], 20
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 16]
mov qword ptr [r13], 30
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 24]
mov qword ptr [r14], 40
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 32]
mov qword ptr [r13], 50
mov cl, 1
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 32]
mov r13, qword ptr [r14]
cmp r13, 50
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 96], 0
mov qword ptr [rbp - 104], 0
jmp label49
label48:
mov r13, qword ptr [rbp - 104]
lea r14, qword ptr [rbp - 88]
mov r12, qword ptr [rbp - 96]
mov rdi, 0
imul rdi, 40
lea rsi, [r14 + rdi]
mov rdi, r13
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r12 + rdi]
mov qword ptr [rbp - 96], r13
jmp label50
label49:
mov r13, qword ptr [rbp - 104]
cmp r13, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label48
jmp label51
label50:
mov r13, qword ptr [rbp - 104]
mov qword ptr [rbp - 112], r13
lea rdi, [r13 + 1]
mov qword ptr [rbp - 104], rdi
jmp label49
label51:
mov rdi, qword ptr [rbp - 96]
cmp rdi, 150
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label52
label52:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayBoundary:
label53:
push rbp
mov rbp, rsp
sub rsp, 192
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 56]
lea r13, [r14]
mov qword ptr [r13], 42
lea r13, qword ptr [rbp - 56]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, 42
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov cl, 1
call Assert
lea r13, qword ptr [rbp - 136]
lea r14, [r13]
mov qword ptr [r14], 1
lea r14, qword ptr [rbp - 136]
lea r13, [r14 + 8]
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 136]
lea r14, [r13 + 16]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 136]
lea r13, [r14 + 24]
mov qword ptr [r13], 4
lea r13, qword ptr [rbp - 136]
lea r14, [r13 + 32]
mov qword ptr [r14], 5
lea r14, qword ptr [rbp - 136]
lea r13, [r14 + 40]
mov qword ptr [r13], 6
lea r13, qword ptr [rbp - 136]
lea r14, [r13 + 48]
mov qword ptr [r14], 7
lea r14, qword ptr [rbp - 136]
lea r13, [r14 + 56]
mov qword ptr [r13], 8
lea r13, qword ptr [rbp - 136]
lea r14, [r13 + 64]
mov qword ptr [r14], 9
lea r14, qword ptr [rbp - 136]
lea r13, [r14 + 72]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 136]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 136]
lea r14, [r13 + 72]
mov r13, qword ptr [r14]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbp - 144], 0
mov qword ptr [rbp - 152], 0
jmp label55
label54:
mov r13, qword ptr [rbp - 152]
lea r14, qword ptr [rbp - 136]
mov r12, qword ptr [rbp - 144]
mov rdi, 0
imul rdi, 80
lea rsi, [r14 + rdi]
mov rdi, r13
imul rdi, 8
lea r13, [rsi + rdi]
mov rdi, qword ptr [r13]
lea r13, [r12 + rdi]
mov qword ptr [rbp - 144], r13
jmp label56
label55:
mov r13, qword ptr [rbp - 152]
cmp r13, 10
setl r13b
and r13b, 1
test r13b, r13b
jne label54
jmp label57
label56:
mov r13, qword ptr [rbp - 152]
mov qword ptr [rbp - 160], r13
lea rdi, [r13 + 1]
mov qword ptr [rbp - 152], rdi
jmp label55
label57:
mov rdi, qword ptr [rbp - 144]
cmp rdi, 55
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label58
label58:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArraySwap:
label59:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
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
lea r13, qword ptr [rbp - 72]
lea r14, [r13]
mov r13, qword ptr [r14]
mov qword ptr [rbp - 80], r13
lea r13, qword ptr [rbp - 72]
lea r14, qword ptr [rbp - 72]
lea r12, [r14 + 32]
mov r14, qword ptr [r12]
lea r12, [r13]
mov qword ptr [r12], r14
lea r12, qword ptr [rbp - 72]
mov r14, qword ptr [rbp - 80]
lea r13, [r12 + 32]
mov qword ptr [r13], r14
lea r13, qword ptr [rbp - 72]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 32]
mov r13, qword ptr [r14]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 8]
mov r13, qword ptr [r14]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 16]
mov r13, qword ptr [r14]
cmp r13, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 24]
mov r13, qword ptr [r14]
cmp r13, 4
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label60
label60:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rsp, rbp
pop rbp
ret
TestArrayTernary:
label61:
push rbp
mov rbp, rsp
sub rsp, 112
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 64]
lea r13, [r14]
mov qword ptr [r13], 10
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 8]
mov qword ptr [r14], 20
lea r14, qword ptr [rbp - 64]
lea r13, [r14 + 16]
mov qword ptr [r13], 30
lea r13, qword ptr [rbp - 64]
lea r14, qword ptr [rbp - 64]
lea r12, [r13]
mov r13, qword ptr [r12]
lea r12, [r14 + 8]
mov r14, qword ptr [r12]
lea r12, qword ptr [rbp - 64]
lea rdi, [r12]
mov r12, qword ptr [rdi]
lea rdi, qword ptr [rbp - 64]
lea rsi, [rdi + 8]
mov rdi, qword ptr [rsi]
cmp r13, r14
setg r14b
and r14b, 1
test r14b, r14b
mov r14, rdi
cmovne r14, r12
mov qword ptr [rbp - 72], r14
mov r14, qword ptr [rbp - 72]
cmp r14, 20
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 64]
mov r12, qword ptr [rbp - 72]
lea rdi, [r14 + 16]
mov r14, qword ptr [rdi]
mov rdi, qword ptr [rbp - 72]
lea r13, qword ptr [rbp - 64]
lea rsi, [r13 + 16]
mov r13, qword ptr [rsi]
cmp r12, r14
setg r14b
and r14b, 1
test r14b, r14b
mov r14, r13
cmovne r14, rdi
mov qword ptr [rbp - 72], r14
mov r14, qword ptr [rbp - 72]
cmp r14, 30
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov qword ptr [rbp - 80], 0
mov r14, qword ptr [rbp - 80]
lea rdi, qword ptr [rbp - 64]
mov r13, 0
imul r13, 24
lea r12, [rdi + r13]
mov r13, r14
imul r13, 8
lea r14, [r12 + r13]
mov r13, qword ptr [r14]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label62
label62:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayAssignment:
label63:
push rbp
mov rbp, rsp
sub rsp, 144
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
lea r13, [r14 + 16]
mov qword ptr [r13], 3
mov qword ptr [rbp - 104], 0
jmp label65
label64:
mov r13, qword ptr [rbp - 104]
lea r14, qword ptr [rbp - 96]
mov r12, qword ptr [rbp - 104]
lea rdi, qword ptr [rbp - 72]
mov rsi, 0
imul rsi, 24
lea rbx, [rdi + rsi]
mov rsi, r12
imul rsi, 8
lea r12, [rbx + rsi]
mov rsi, qword ptr [r12]
mov r12, 0
imul r12, 24
lea rbx, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rbx + r12]
mov qword ptr [r13], rsi
jmp label66
label65:
mov r13, qword ptr [rbp - 104]
cmp r13, 3
setl r13b
and r13b, 1
test r13b, r13b
jne label64
jmp label67
label66:
mov r13, qword ptr [rbp - 104]
mov qword ptr [rbp - 112], r13
lea rsi, [r13 + 1]
mov qword ptr [rbp - 104], rsi
jmp label65
label67:
lea rsi, qword ptr [rbp - 96]
lea r13, [rsi]
mov rsi, qword ptr [r13]
cmp rsi, 1
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 96]
lea r13, [rsi + 8]
mov rsi, qword ptr [r13]
cmp rsi, 2
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 96]
lea r13, [rsi + 16]
mov rsi, qword ptr [r13]
cmp rsi, 3
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 72]
lea r13, [rsi]
mov qword ptr [r13], 100
lea r13, qword ptr [rbp - 72]
lea rsi, [r13]
mov r13, qword ptr [rsi]
cmp r13, 100
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 96]
lea rsi, [r13]
mov r13, qword ptr [rsi]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label68
label68:
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
label69:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 72]
lea r13, [r14]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 8]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 16]
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 72]
lea r14, [r13 + 24]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 72]
lea r13, [r14 + 32]
mov qword ptr [r13], 0
mov qword ptr [rbp - 80], 0
jmp label71
label70:
mov r13, qword ptr [rbp - 80]
lea r14, qword ptr [rbp - 72]
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov rax, r13
cqo
mov r13, 5
idiv r13
mov r13, rdx
mov r12, r13
imul r12, 8
lea r13, [rdi + r12]
mov r12, qword ptr [r13]
mov qword ptr [rbp - 88], r12
lea rdi, [r12 + 1]
mov qword ptr [r13], rdi
jmp label72
label71:
mov rdi, qword ptr [rbp - 80]
cmp rdi, 100
setl dil
and dil, 1
test dil, dil
jne label70
jmp label73
label72:
mov rdi, qword ptr [rbp - 80]
mov qword ptr [rbp - 96], rdi
lea r13, [rdi + 1]
mov qword ptr [rbp - 80], r13
jmp label71
label73:
lea r13, qword ptr [rbp - 72]
lea rdi, [r13]
mov r13, qword ptr [rdi]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea rdi, [r13 + 8]
mov r13, qword ptr [rdi]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea rdi, [r13 + 16]
mov r13, qword ptr [rdi]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea rdi, [r13 + 24]
mov r13, qword ptr [rdi]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 72]
lea rdi, [r13 + 32]
mov r13, qword ptr [rdi]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label74
label74:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
SumArray__I5:
label75:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r14, rcx
mov r13, qword ptr [r14]
lea r12, qword ptr [rbp - 160]
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
lea r13, qword ptr [rbp - 160]
lea r14, qword ptr [rbp - 88]
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
mov qword ptr [rbp - 104], 0
mov qword ptr [rbp - 112], 0
jmp label77
label76:
mov rdi, qword ptr [rbp - 112]
lea r13, qword ptr [rbp - 88]
mov rsi, qword ptr [rbp - 104]
mov r12, 0
imul r12, 40
lea r14, [r13 + r12]
mov r12, rdi
imul r12, 8
lea rdi, [r14 + r12]
mov r12, qword ptr [rdi]
lea rdi, [rsi + r12]
mov qword ptr [rbp - 104], rdi
jmp label78
label77:
mov rdi, qword ptr [rbp - 112]
cmp rdi, 5
setl dil
and dil, 1
test dil, dil
jne label76
jmp label79
label78:
mov rdi, qword ptr [rbp - 112]
mov qword ptr [rbp - 120], rdi
lea r12, [rdi + 1]
mov qword ptr [rbp - 112], r12
jmp label77
label79:
mov r12, qword ptr [rbp - 104]
mov qword ptr [rbp - 96], r12
jmp label81
label80:
label81:
mov r12, qword ptr [rbp - 96]
mov rax, r12
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
ModifyArrayByValue__I3:
label82:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, rcx
mov r13, qword ptr [r14]
lea r12, qword ptr [rbp - 96]
mov rdi, r14
add rdi, 8
mov rsi, qword ptr [rdi]
mov rdi, r12
add rdi, 8
mov qword ptr [r12], r13
mov r13, r14
add r13, 16
mov r14, qword ptr [r13]
mov r13, r12
add r13, 16
mov qword ptr [rdi], rsi
mov qword ptr [r13], r14
lea r13, qword ptr [rbp - 96]
lea r14, qword ptr [rbp - 72]
mov rdi, qword ptr [r13]
mov rsi, r13
add rsi, 8
mov r12, qword ptr [rsi]
mov rsi, r14
add rsi, 8
mov qword ptr [r14], rdi
mov rdi, r13
add rdi, 16
mov r13, qword ptr [rdi]
mov rdi, r14
add rdi, 16
mov qword ptr [rsi], r12
mov qword ptr [rdi], r13
lea rdi, qword ptr [rbp - 72]
lea r13, [rdi]
mov qword ptr [r13], 999
jmp label83
label83:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayPassByValue:
label84:
push rbp
mov rbp, rsp
sub rsp, 224
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
mov qword ptr [rbp - 144], r14
mov r14, qword ptr [rbp - 144]
cmp r14, 30
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 168]
lea r12, [r14]
mov qword ptr [r12], 1
lea r12, qword ptr [rbp - 168]
lea r14, [r12 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 168]
lea r12, [r14 + 16]
mov qword ptr [r12], 3
lea r12, qword ptr [rbp - 168]
lea r14, qword ptr [rbp - 192]
mov r13, qword ptr [r12]
mov rdi, r12
add rdi, 8
mov rsi, qword ptr [rdi]
mov rdi, r14
add rdi, 8
mov qword ptr [r14], r13
mov r13, r12
add r13, 16
mov r12, qword ptr [r13]
mov r13, r14
add r13, 16
mov qword ptr [rdi], rsi
mov qword ptr [r13], r12
mov rcx, r14
call ModifyArrayByValue__I3
lea r14, qword ptr [rbp - 168]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label85
label85:
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
label86:
push rbp
mov rbp, rsp
sub rsp, 64
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
mov r14, rcx
mov qword ptr [rbp - 48], r14
mov r14, qword ptr [rbp - 48]
mov qword ptr [rbp - 56], 0
jmp label88
label87:
mov r13, qword ptr [rbp - 56]
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rdi + r12]
mov qword ptr [r13], 0
jmp label89
label88:
mov r13, qword ptr [rbp - 56]
cmp r13, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label87
jmp label90
label89:
mov r13, qword ptr [rbp - 56]
mov qword ptr [rbp - 64], r13
lea r12, [r13 + 1]
mov qword ptr [rbp - 56], r12
jmp label88
label90:
jmp label91
label91:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestArrayPassByRef:
label92:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 80]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 80]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 80]
lea r13, [r14 + 32]
mov qword ptr [r13], 5
lea rcx, qword ptr [rbp - 80]
call ZeroArray__I5ref
mov qword ptr [rbp - 88], 0
jmp label94
label93:
mov r13, qword ptr [rbp - 88]
lea r14, qword ptr [rbp - 80]
mov r12, 0
imul r12, 40
lea rdi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rdi + r12]
mov r12, qword ptr [r13]
cmp r12, 0
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label95
label94:
mov r12, qword ptr [rbp - 88]
cmp r12, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label93
jmp label96
label95:
mov r12, qword ptr [rbp - 88]
mov qword ptr [rbp - 96], r12
lea r13, [r12 + 1]
mov qword ptr [rbp - 88], r13
jmp label94
label96:
jmp label97
label97:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
ReverseArray__I5ref:
label98:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
mov r14, rcx
mov qword ptr [rbp - 56], r14
mov r14, qword ptr [rbp - 56]
mov qword ptr [rbp - 64], 0
mov qword ptr [rbp - 72], 4
jmp label99
label99:
mov r13, qword ptr [rbp - 64]
mov r12, qword ptr [rbp - 72]
cmp r13, r12
setl r12b
and r12b, 1
test r12b, r12b
jne label100
jmp label101
label100:
mov r12, qword ptr [rbp - 64]
mov r13, 0
imul r13, 40
lea rdi, [r14 + r13]
mov r13, r12
imul r13, 8
lea r12, [rdi + r13]
mov r13, qword ptr [r12]
mov qword ptr [rbp - 80], r13
mov r13, qword ptr [rbp - 64]
mov r12, qword ptr [rbp - 72]
mov rdi, 0
imul rdi, 40
lea rsi, [r14 + rdi]
mov rdi, r12
imul rdi, 8
lea r12, [rsi + rdi]
mov rdi, qword ptr [r12]
mov r12, 0
imul r12, 40
lea rsi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rsi + r12]
mov qword ptr [r13], rdi
mov r13, qword ptr [rbp - 72]
mov rdi, qword ptr [rbp - 80]
mov r12, 0
imul r12, 40
lea rsi, [r14 + r12]
mov r12, r13
imul r12, 8
lea r13, [rsi + r12]
mov qword ptr [r13], rdi
mov r13, qword ptr [rbp - 64]
mov qword ptr [rbp - 88], r13
lea rdi, [r13 + 1]
mov qword ptr [rbp - 64], rdi
mov rdi, qword ptr [rbp - 72]
mov qword ptr [rbp - 96], rdi
mov r13, rdi
sub r13, 1
mov qword ptr [rbp - 72], r13
jmp label99
label101:
jmp label102
label102:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayReverse:
label103:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
lea r14, qword ptr [rbp - 64]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 64]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 64]
lea r13, [r14 + 32]
mov qword ptr [r13], 5
lea rcx, qword ptr [rbp - 64]
call ReverseArray__I5ref
lea r13, qword ptr [rbp - 64]
lea r14, [r13]
mov r13, qword ptr [r14]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 8]
mov r13, qword ptr [r14]
cmp r13, 4
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 16]
mov r13, qword ptr [r14]
cmp r13, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 24]
mov r13, qword ptr [r14]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 64]
lea r14, [r13 + 32]
mov r13, qword ptr [r14]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label104
label104:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov rsp, rbp
pop rbp
ret
TestArrayBubbleSort:
label105:
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
mov qword ptr [r13], 5
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 8]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 16]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 88]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 32]
mov qword ptr [r13], 2
mov qword ptr [rbp - 96], 0
jmp label107
label106:
mov qword ptr [rbp - 104], 0
jmp label111
label107:
mov r13, qword ptr [rbp - 96]
cmp r13, 5
setl r13b
and r13b, 1
test r13b, r13b
jne label106
jmp label109
label108:
mov r13, qword ptr [rbp - 96]
mov qword ptr [rbp - 112], r13
lea r14, [r13 + 1]
mov qword ptr [rbp - 96], r14
jmp label107
label109:
lea r14, qword ptr [rbp - 88]
lea r13, [r14]
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 8]
mov r14, qword ptr [r13]
cmp r14, 2
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 16]
mov r14, qword ptr [r13]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 24]
mov r14, qword ptr [r13]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 88]
lea r13, [r14 + 32]
mov r14, qword ptr [r13]
cmp r14, 5
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label117
label110:
mov r14, qword ptr [rbp - 104]
lea r13, qword ptr [rbp - 88]
mov r12, qword ptr [rbp - 104]
lea rdi, qword ptr [rbp - 88]
mov rsi, 0
imul rsi, 40
lea rbx, [r13 + rsi]
mov rsi, r14
imul rsi, 8
lea r14, [rbx + rsi]
mov rsi, qword ptr [r14]
mov r14, 0
imul r14, 40
lea rbx, [rdi + r14]
lea r14, [r12 + 1]
mov r12, r14
imul r12, 8
lea r14, [rbx + r12]
mov r12, qword ptr [r14]
cmp rsi, r12
setg r12b
and r12b, 1
test r12b, r12b
jne label114
jmp label116
label111:
mov r12, qword ptr [rbp - 96]
mov rsi, qword ptr [rbp - 104]
mov r14, 4
sub r14, r12
cmp rsi, r14
setl r14b
and r14b, 1
test r14b, r14b
jne label110
jmp label113
label112:
mov r14, qword ptr [rbp - 104]
mov qword ptr [rbp - 120], r14
lea rsi, [r14 + 1]
mov qword ptr [rbp - 104], rsi
jmp label111
label113:
jmp label108
label114:
mov rsi, qword ptr [rbp - 104]
lea r14, qword ptr [rbp - 88]
mov r12, 0
imul r12, 40
lea rbx, [r14 + r12]
mov r12, rsi
imul r12, 8
lea rsi, [rbx + r12]
mov r12, qword ptr [rsi]
mov qword ptr [rbp - 128], r12
mov r12, qword ptr [rbp - 104]
lea rsi, qword ptr [rbp - 88]
mov rbx, qword ptr [rbp - 104]
lea r14, qword ptr [rbp - 88]
mov rdi, 0
imul rdi, 40
lea r13, [r14 + rdi]
lea rdi, [rbx + 1]
mov rbx, rdi
imul rbx, 8
lea rdi, [r13 + rbx]
mov rbx, qword ptr [rdi]
mov rdi, 0
imul rdi, 40
lea r13, [rsi + rdi]
mov rdi, r12
imul rdi, 8
lea r12, [r13 + rdi]
mov qword ptr [r12], rbx
mov r12, qword ptr [rbp - 104]
lea rbx, qword ptr [rbp - 88]
mov rdi, qword ptr [rbp - 128]
mov r13, 0
imul r13, 40
lea rsi, [rbx + r13]
lea r13, [r12 + 1]
mov r12, r13
imul r12, 8
lea r13, [rsi + r12]
mov qword ptr [r13], rdi
jmp label116
label115:
label116:
jmp label112
label117:
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
label118:
push rbp
mov rbp, rsp
sub rsp, 160
mov qword ptr [rbp - 8], r14
mov qword ptr [rbp - 16], r13
mov qword ptr [rbp - 24], r12
mov qword ptr [rbp - 32], rdi
lea r14, qword ptr [rbp - 96]
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 8]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 16]
mov qword ptr [r13], 5
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 24]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 32]
mov qword ptr [r13], 7
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 40]
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 48]
mov qword ptr [r13], 9
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 56]
mov qword ptr [r14], 3
mov qword ptr [rbp - 104], 0
mov qword ptr [rbp - 112], 0
jmp label120
label119:
mov r14, qword ptr [rbp - 112]
lea r13, qword ptr [rbp - 96]
mov r12, 0
imul r12, 64
lea rdi, [r13 + r12]
mov r12, r14
imul r12, 8
lea r14, [rdi + r12]
mov r12, qword ptr [r14]
cmp r12, 3
sete r12b
and r12b, 1
test r12b, r12b
jne label123
jmp label125
label120:
mov r12, qword ptr [rbp - 112]
cmp r12, 8
setl r12b
and r12b, 1
test r12b, r12b
jne label119
jmp label122
label121:
mov r12, qword ptr [rbp - 112]
mov qword ptr [rbp - 120], r12
lea r14, [r12 + 1]
mov qword ptr [rbp - 112], r14
jmp label120
label122:
mov r14, qword ptr [rbp - 104]
cmp r14, 4
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label126
label123:
mov r14, qword ptr [rbp - 104]
mov qword ptr [rbp - 128], r14
lea r12, [r14 + 1]
mov qword ptr [rbp - 104], r12
jmp label125
label124:
label125:
jmp label121
label126:
mov r14, qword ptr [rbp - 8]
mov r13, qword ptr [rbp - 16]
mov r12, qword ptr [rbp - 24]
mov rdi, qword ptr [rbp - 32]
mov rsp, rbp
pop rbp
ret
TestArrayPrefixSum:
label127:
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
lea r13, [r14]
mov qword ptr [r13], 1
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 8]
mov qword ptr [r14], 2
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 16]
mov qword ptr [r13], 3
lea r13, qword ptr [rbp - 96]
lea r14, [r13 + 24]
mov qword ptr [r14], 4
lea r14, qword ptr [rbp - 96]
lea r13, [r14 + 32]
mov qword ptr [r13], 5
mov qword ptr [rbp - 104], 1
jmp label129
label128:
mov r15, qword ptr [rbp - 104]
mov qword ptr [rbp - 120], r15
lea r15, qword ptr [rbp - 96]
mov qword ptr [rbp - 128], r15
mov r12, qword ptr [rbp - 104]
lea rdi, qword ptr [rbp - 96]
mov rsi, qword ptr [rbp - 104]
lea rbx, qword ptr [rbp - 96]
mov r13, 0
imul r13, 40
lea r14, [rdi + r13]
mov r13, r12
imul r13, 8
lea r12, [r14 + r13]
mov r13, qword ptr [r12]
mov r12, 0
imul r12, 40
lea r14, [rbx + r12]
mov r12, rsi
sub r12, 1
mov rsi, r12
imul rsi, 8
lea r12, [r14 + rsi]
mov rsi, qword ptr [r12]
lea r12, [r13 + rsi]
mov rsi, 0
imul rsi, 40
mov r15, qword ptr [rbp - 128]
lea r13, [r15 + rsi]
mov r15, qword ptr [rbp - 120]
mov rsi, r15
imul rsi, 8
lea r14, [r13 + rsi]
mov qword ptr [r14], r12
jmp label130
label129:
mov r14, qword ptr [rbp - 104]
cmp r14, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label128
jmp label131
label130:
mov r14, qword ptr [rbp - 104]
mov qword ptr [rbp - 112], r14
lea r12, [r14 + 1]
mov qword ptr [rbp - 104], r12
jmp label129
label131:
lea r12, qword ptr [rbp - 96]
lea r14, [r12]
mov r12, qword ptr [r14]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea r14, [r12 + 8]
mov r12, qword ptr [r14]
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea r14, [r12 + 16]
mov r12, qword ptr [r14]
cmp r12, 6
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea r14, [r12 + 24]
mov r12, qword ptr [r14]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 96]
lea r14, [r12 + 32]
mov r12, qword ptr [r14]
cmp r12, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label132
label132:
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
label133:
push rbp
mov rbp, rsp
sub rsp, 48
mov qword ptr [rbp - 8], r14
call TestGlobalArrays
call TestLocalArrays
call TestFloatArrays
call TestBoolArrays
call TestArrayModification
call TestArrayExpressions
call TestArrayVariableIndex
call TestArrayInLoops
call TestArrayWhileLoop
call TestArrayLengthSizeof
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
mov qword ptr [rbp - 16], 0
jmp label135
label134:
label135:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
