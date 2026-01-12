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
mov r13, r14
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray1]
mov r13, r14
mov r14, r13
add r14, 8
mov r13, qword ptr [r14]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalArray1]
mov r14, r13
mov r13, r14
add r13, 16
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
mov cl, 1
call Assert
lea r14, [rip + GlobalArray2]
mov r13, r14
mov r14, qword ptr [r13]
cmp r14, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
mov r13, r14
mov r14, r13
add r14, 8
mov r13, qword ptr [r14]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalArray2]
mov r14, r13
mov r13, r14
add r13, 16
mov r14, qword ptr [r13]
cmp r14, 3
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray2]
mov r13, r14
mov r14, r13
add r14, 24
mov r13, qword ptr [r14]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalArray2]
mov r14, r13
mov r13, r14
add r13, 32
mov r14, qword ptr [r13]
cmp r14, 0
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray3]
mov r13, r14
mov r14, qword ptr [r13]
cmp r14, 10
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalArray3]
mov r13, r14
mov r14, r13
add r14, 8
mov r13, qword ptr [r14]
cmp r13, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalArray3]
mov r14, r13
mov r13, r14
add r13, 16
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
mov qword ptr [r14], 1
lea r13, qword ptr [rbp - 136]
mov r12, r13
add r12, 8
mov qword ptr [r12], 2
lea r13, qword ptr [rbp - 136]
mov rdi, r13
add rdi, 16
mov qword ptr [rdi], 0
lea r13, qword ptr [rbp - 136]
mov rsi, r13
add rsi, 24
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
mov r13, rsi
add r13, 32
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 136]
mov rsi, r13
add rsi, 40
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
mov r13, rsi
add r13, 48
mov qword ptr [r13], 0
lea rsi, qword ptr [rbp - 136]
mov rbx, rsi
add rbx, 56
mov qword ptr [rbx], 0
lea rbx, qword ptr [rbp - 136]
mov rsi, rbx
add rsi, 64
mov qword ptr [rsi], 0
lea rsi, qword ptr [rbp - 136]
mov rbx, rsi
add rbx, 72
mov qword ptr [rbx], 0
mov cl, 1
call Assert
mov rbx, qword ptr [r14]
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
mov rbx, qword ptr [r13]
cmp rbx, 0
sete bl
and bl, 1
mov cl, bl
call Assert
lea rbx, qword ptr [rbp - 160]
mov qword ptr [rbx], -5
lea r13, qword ptr [rbp - 160]
mov rdi, r13
add rdi, 8
mov qword ptr [rdi], 0
lea r13, qword ptr [rbp - 160]
mov r12, r13
add r12, 16
mov qword ptr [r12], 5
mov r13, qword ptr [rbx]
cmp r13, -5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rdi]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [r12]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
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
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
movsd qword ptr [rbp - 56], xmm14
movsd qword ptr [rbp - 64], xmm13
movsd qword ptr [rbp - 72], xmm12
lea r14, [rip + GlobalFloatArray]
mov r13, r14
movsd xmm14, qword ptr [r13]
comisd xmm14, qword ptr [rip + _FP0]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [r13]
comisd xmm14, qword ptr [rip + _FP1]
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
mov r13, r12
mov r12, r13
add r12, 8
movsd xmm14, qword ptr [r12]
comisd xmm14, qword ptr [rip + _FP2]
seta r13b
and r13b, 1
movsd xmm14, qword ptr [r12]
comisd xmm14, qword ptr [rip + _FP3]
setb r12b
and r12b, 1
mov r14b, r13b
and r14b, r12b
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalFloatArray]
mov r12, r14
mov r14, r12
add r14, 16
movsd xmm14, qword ptr [r14]
comisd xmm14, qword ptr [rip + _FP4]
seta r12b
and r12b, 1
movsd xmm14, qword ptr [r14]
comisd xmm14, qword ptr [rip + _FP5]
setb r14b
and r14b, 1
mov r13b, r12b
and r13b, r14b
cmp r13b, 0
setne r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 104]
movsd xmm14, qword ptr [rip + _FP6]
movsd qword ptr [r13], xmm14
lea r14, qword ptr [rbp - 104]
mov r12, r14
add r12, 8
movsd xmm14, qword ptr [rip + _FP7]
movsd qword ptr [r12], xmm14
lea r14, qword ptr [rbp - 104]
mov rdi, r14
add rdi, 16
movsd xmm14, qword ptr [rip + _FP8]
movsd qword ptr [rdi], xmm14
lea r14, qword ptr [rbp - 104]
mov qword ptr [rbp - 112], r14
add qword ptr [rbp - 112], 24
movsd xmm14, qword ptr [rip + _FP9]
movsd qword ptr [rbp - 112], xmm14
movsd xmm14, qword ptr [r13]
comisd xmm14, qword ptr [rip + _FP10]
seta r14b
and r14b, 1
movsd xmm14, qword ptr [r13]
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
movsd xmm14, qword ptr [rbp - 112]
comisd xmm14, qword ptr [rip + _FP12]
seta sil
and sil, 1
movsd xmm14, qword ptr [rbp - 112]
comisd xmm14, qword ptr [rip + _FP13]
setb bl
and bl, 1
mov r14b, sil
and r14b, bl
cmp r14b, 0
setne r14b
and r14b, 1
mov cl, r14b
call Assert
movsd xmm14, qword ptr [r13]
movsd xmm13, qword ptr [r12]
movsd xmm12, xmm14
addsd xmm12, xmm13
movsd xmm13, qword ptr [rdi]
movsd xmm14, xmm12
addsd xmm14, xmm13
movsd xmm13, qword ptr [rbp - 112]
movsd xmm12, xmm14
addsd xmm12, xmm13
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
mov r13, r14
mov r14b, byte ptr [r13]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalBoolArray]
mov r13, r14
mov r14, r13
add r14, 1
mov r13b, byte ptr [r14]
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, [rip + GlobalBoolArray]
mov r14, r13
mov r13, r14
add r13, 2
mov r14b, byte ptr [r13]
cmp r14b, 1
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, [rip + GlobalBoolArray]
mov r13, r14
mov r14, r13
add r14, 3
mov r13b, byte ptr [r14]
cmp r13b, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 48]
mov byte ptr [r13], 1
lea r14, qword ptr [rbp - 48]
mov r12, r14
add r12, 1
mov byte ptr [r12], 1
lea r14, qword ptr [rbp - 48]
mov rdi, r14
add rdi, 2
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
mov qword ptr [r14], 1
lea r13, qword ptr [rbp - 88]
mov r12, r13
add r12, 8
mov qword ptr [r12], 2
lea r13, qword ptr [rbp - 88]
mov rdi, r13
add rdi, 16
mov qword ptr [rdi], 3
lea r13, qword ptr [rbp - 88]
mov rsi, r13
add rsi, 24
mov qword ptr [rsi], 4
lea r13, qword ptr [rbp - 88]
mov rbx, r13
add rbx, 32
mov qword ptr [rbx], 5
mov qword ptr [r14], 10
mov r13, qword ptr [r14]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov qword ptr [rbx], 50
mov r13, qword ptr [rbx]
cmp r13, 50
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [r14]
mov r14, qword ptr [rbx]
mov rbx, r13
add rbx, r14
mov qword ptr [rdi], rbx
mov rbx, qword ptr [rdi]
cmp rbx, 60
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r12]
mov rdi, rbx
add rdi, rbx
mov qword ptr [r12], rdi
mov rdi, qword ptr [r12]
cmp rdi, 4
sete dil
and dil, 1
mov cl, dil
call Assert
mov rdi, qword ptr [rsi]
mov qword ptr [rbp - 96], rdi
mov r12, rdi
add r12, 1
mov qword ptr [rsi], r12
mov r12, qword ptr [rsi]
cmp r12, 5
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [rsi]
mov rdi, r12
add rdi, 1
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
sub rsp, 144
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 96]
mov qword ptr [r14], 10
lea r13, qword ptr [rbp - 96]
mov qword ptr [rbp - 104], r13
add qword ptr [rbp - 104], 8
mov qword ptr [rbp - 104], 20
lea r13, qword ptr [rbp - 96]
mov qword ptr [rbp - 112], r13
add qword ptr [rbp - 112], 16
mov qword ptr [rbp - 112], 30
lea r13, qword ptr [rbp - 96]
mov rsi, r13
add rsi, 24
mov qword ptr [rsi], 40
lea r13, qword ptr [rbp - 96]
mov rbx, r13
add rbx, 32
mov qword ptr [rbx], 50
mov r13, qword ptr [r14]
mov rdi, qword ptr [rbp - 104]
mov r12, r13
add r12, rdi
mov rdi, qword ptr [rbp - 112]
mov r13, r12
add r13, rdi
mov rdi, qword ptr [rsi]
mov rsi, r13
add rsi, rdi
mov rdi, qword ptr [rbx]
mov r13, rsi
add r13, rdi
cmp r13, 150
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [r14]
mov rdi, qword ptr [rbp - 104]
mov rsi, r13
imul rsi, rdi
cmp rsi, 200
sete sil
and sil, 1
mov cl, sil
call Assert
mov rsi, qword ptr [rbx]
mov rdi, qword ptr [r14]
mov r13, rsi
sub r13, rdi
cmp r13, 40
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbx]
mov rbx, qword ptr [r14]
cmp r13, rbx
setg bl
and bl, 1
cmp bl, 1
sete bl
and bl, 1
mov cl, bl
call Assert
mov rbx, qword ptr [r14]
mov r14, qword ptr [rbp - 104]
mov r13, rbx
add r13, r14
mov r14, qword ptr [rbp - 112]
mov rbx, r13
add rbx, r14
mov rax, rbx
cqo
mov rbx, 3
idiv rbx
mov rbx, rax
cmp rbx, 20
sete bl
and bl, 1
mov cl, bl
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
mov qword ptr [r14], 100
lea r14, qword ptr [rbp - 80]
mov r13, r14
add r13, 8
mov qword ptr [r13], 200
lea r13, qword ptr [rbp - 80]
mov r14, r13
add r14, 16
mov qword ptr [r14], 300
lea r14, qword ptr [rbp - 80]
mov r13, r14
add r13, 24
mov qword ptr [r13], 400
lea r13, qword ptr [rbp - 80]
mov r14, r13
add r14, 32
mov qword ptr [r14], 500
lea r14, qword ptr [rbp - 80]
mov r13, 0
imul r13, 40
mov r12, r14
add r12, r13
mov r13, 0
imul r13, 8
mov r14, r12
add r14, r13
mov r13, qword ptr [r14]
cmp r13, 100
sete r13b
and r13b, 1
mov cl, r13b
call Assert
lea r13, qword ptr [rbp - 80]
mov r14, 0
imul r14, 40
mov r12, r13
add r12, r14
mov r14, 2
imul r14, 8
mov r13, r12
add r13, r14
mov r14, qword ptr [r13]
cmp r14, 300
sete r14b
and r14b, 1
mov cl, r14b
call Assert
lea r14, qword ptr [rbp - 80]
mov r12, 0
imul r12, 40
mov rdi, r14
add rdi, r12
mov r12, 4
imul r12, 8
mov r14, rdi
add r14, r12
mov r12, qword ptr [r14]
cmp r12, 500
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r13]
cmp r12, 300
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r13]
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
sub rsp, 160
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
lea r14, qword ptr [rbp - 88]
mov qword ptr [r14], 1
lea r14, qword ptr [rbp - 88]
mov r13, r14
add r13, 8
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 88]
mov r14, r13
add r14, 16
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 88]
mov r13, r14
add r13, 24
mov qword ptr [r13], 4
lea r13, qword ptr [rbp - 88]
mov r14, r13
add r14, 32
mov qword ptr [r14], 5
mov r14, 0
mov qword ptr [rbp - 128], 0
jmp label16
label15:
lea r13, qword ptr [rbp - 88]
mov r12, 0
imul r12, 40
mov rbx, r13
add rbx, r12
mov r12, r14
imul r12, 8
mov r13, rbx
add r13, r12
mov r12, qword ptr [r13]
mov r13, qword ptr [rbp - 128]
add r13, r12
jmp label17
label16:
cmp r14, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label15
jmp label18
label17:
mov qword ptr [rbp - 96], r14
mov r12, r14
add r12, 1
mov r14, r12
mov qword ptr [rbp - 128], r13
jmp label16
label18:
cmp qword ptr [rbp - 128], 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, 0
jmp label20
label19:
lea rbx, qword ptr [rbp - 88]
mov rsi, 0
imul rsi, 40
mov r13, rbx
add r13, rsi
mov rsi, r12
imul rsi, 8
mov rbx, r13
add rbx, rsi
mov rsi, qword ptr [rbx]
mov r13, rsi
add r13, rsi
mov qword ptr [rbx], r13
jmp label21
label20:
cmp r12, 5
setl dil
and dil, 1
test dil, dil
jne label19
jmp label22
label21:
mov qword ptr [rbp - 104], r12
mov r13, r12
add r13, 1
mov r12, r13
jmp label20
label22:
lea rdi, qword ptr [rbp - 88]
mov rsi, qword ptr [rdi]
cmp rsi, 2
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 88]
mov rbx, rsi
add rbx, 8
mov rsi, qword ptr [rbx]
cmp rsi, 4
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 88]
mov rbx, rsi
add rbx, 16
mov rsi, qword ptr [rbx]
cmp rsi, 6
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 88]
mov rbx, rsi
add rbx, 24
mov rsi, qword ptr [rbx]
cmp rsi, 8
sete sil
and sil, 1
mov cl, sil
call Assert
lea rsi, qword ptr [rbp - 88]
mov rbx, rsi
add rbx, 32
mov rsi, qword ptr [rbx]
cmp rsi, 10
sete sil
and sil, 1
mov cl, sil
call Assert
mov rsi, qword ptr [rdi]
mov qword ptr [rbp - 112], rsi
mov rsi, 1
jmp label24
label23:
lea rdi, qword ptr [rbp - 88]
mov rbx, 0
imul rbx, 40
mov r13, rdi
add r13, rbx
mov rbx, rsi
imul rbx, 8
mov rdi, r13
add rdi, rbx
mov rbx, qword ptr [rdi]
mov rdi, qword ptr [rbp - 112]
cmp rbx, rdi
setg dil
and dil, 1
test dil, dil
jne label26
jmp label25
label24:
cmp rsi, 5
setl dil
and dil, 1
test dil, dil
jne label23
jmp label27
label25:
mov qword ptr [rbp - 120], rsi
mov rdi, rsi
add rdi, 1
mov rsi, rdi
jmp label24
label26:
lea rdi, qword ptr [rbp - 88]
mov rbx, 0
imul rbx, 40
mov r13, rdi
add r13, rbx
mov rbx, rsi
imul rbx, 8
mov rsi, r13
add rsi, rbx
mov rbx, qword ptr [rsi]
mov qword ptr [rbp - 112], rbx
jmp label25
label27:
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
label28:
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
mov qword ptr [r14], 5
lea r14, qword ptr [rbp - 96]
mov r13, r14
add r13, 8
mov qword ptr [r13], 4
lea r13, qword ptr [rbp - 96]
mov r14, r13
add r14, 16
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 96]
mov r13, r14
add r13, 24
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 96]
mov r14, r13
add r14, 32
mov qword ptr [r14], 1
mov r14, 0
mov r13, 0
jmp label29
label29:
cmp r13, 5
setl r12b
and r12b, 1
test r12b, r12b
jne label30
jmp label31
label30:
lea rdi, qword ptr [rbp - 96]
mov r12, 0
imul r12, 40
mov rsi, rdi
add rsi, r12
mov r12, r13
imul r12, 8
mov rdi, rsi
add rdi, r12
mov r12, qword ptr [rdi]
mov rdi, r14
add rdi, r12
mov qword ptr [rbp - 104], r13
mov r12, r13
add r12, 1
mov r14, rdi
mov r13, r12
jmp label29
label31:
cmp r14, 15
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, 0
jmp label32
label32:
cmp r12, 5
setl dil
and dil, 1
test dil, dil
jne label33
jmp label34
label33:
lea rsi, qword ptr [rbp - 96]
mov rdi, 0
imul rdi, 40
mov rbx, rsi
add rbx, rdi
mov rdi, r12
imul rdi, 8
mov rsi, rbx
add rsi, rdi
mov rdi, qword ptr [rsi]
mov rax, rdi
cqo
mov rdi, 2
idiv rdi
mov rdi, rdx
cmp rdi, 0
sete dil
and dil, 1
test dil, dil
jne label34
jmp label35
label34:
lea rdi, qword ptr [rbp - 96]
mov rsi, 0
imul rsi, 40
mov rbx, rdi
add rbx, rsi
mov rsi, r12
imul rsi, 8
mov rdi, rbx
add rdi, rsi
mov rsi, qword ptr [rdi]
cmp rsi, 4
sete sil
and sil, 1
mov cl, sil
call Assert
jmp label36
label35:
mov qword ptr [rbp - 112], r12
mov rdi, r12
add rdi, 1
mov r12, rdi
jmp label32
label36:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov rbx, qword ptr [rbp - 24]
mov r13, qword ptr [rbp - 32]
mov r12, qword ptr [rbp - 40]
mov rdi, qword ptr [rbp - 48]
mov rsp, rbp
pop rbp
ret
TestArrayNegativeValues:
label37:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], rbx
mov qword ptr [rbp - 32], r13
mov qword ptr [rbp - 40], r12
mov qword ptr [rbp - 48], rdi
mov r15, qword ptr [rbp - 88]
mov qword ptr [rbp - 96], r15
mov qword ptr [rbp - 96], -10
lea r13, qword ptr [rbp - 88]
mov r12, r13
add r12, 8
mov qword ptr [r12], -5
lea r13, qword ptr [rbp - 88]
mov rdi, r13
add rdi, 16
mov qword ptr [rdi], 0
lea r13, qword ptr [rbp - 88]
mov rsi, r13
add rsi, 24
mov qword ptr [rsi], 5
lea r13, qword ptr [rbp - 88]
mov rbx, r13
add rbx, 32
mov qword ptr [rbx], 10
mov r13, qword ptr [rbp - 96]
cmp r13, -10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [r12]
cmp r13, -5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rdi]
cmp r13, 0
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rsi]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbx]
cmp r13, 10
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbp - 96]
mov r14, qword ptr [r12]
mov r12, r13
add r12, r14
mov r14, qword ptr [rdi]
mov rdi, r12
add rdi, r14
mov r14, qword ptr [rsi]
mov rsi, rdi
add rsi, r14
mov r14, qword ptr [rbx]
mov rdi, rsi
add rdi, r14
cmp rdi, 0
sete dil
and dil, 1
mov cl, dil
call Assert
mov rdi, qword ptr [rbx]
mov rbx, rdi
neg rbx
mov qword ptr [rbp - 96], rbx
mov rbx, qword ptr [rbp - 96]
cmp rbx, -10
sete bl
and bl, 1
mov cl, bl
call Assert
jmp label38
label38:
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
label39:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 88]
mov qword ptr [r14], 10
lea r13, qword ptr [rbp - 88]
mov r12, r13
add r12, 8
mov qword ptr [r12], 20
lea r12, qword ptr [rbp - 88]
mov r13, r12
add r13, 16
mov qword ptr [r13], 30
lea r13, qword ptr [rbp - 88]
mov r12, r13
add r12, 24
mov qword ptr [r12], 40
lea r12, qword ptr [rbp - 88]
mov r13, r12
add r13, 32
mov qword ptr [r13], 50
mov cl, 1
call Assert
mov r12, qword ptr [r14]
cmp r12, 10
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, qword ptr [r13]
cmp r12, 50
sete r12b
and r12b, 1
mov cl, r12b
call Assert
mov r12, 0
mov r13, 0
jmp label41
label40:
lea r14, qword ptr [rbp - 88]
mov rdi, 0
imul rdi, 40
mov rsi, r14
add rsi, rdi
mov rdi, r12
imul rdi, 8
mov r14, rsi
add r14, rdi
mov rdi, qword ptr [r14]
mov r14, r13
add r14, rdi
jmp label42
label41:
cmp r12, 5
setl r14b
and r14b, 1
test r14b, r14b
jne label40
jmp label43
label42:
mov qword ptr [rbp - 96], r12
mov rdi, r12
add rdi, 1
mov r12, rdi
mov r13, r14
jmp label41
label43:
cmp r13, 150
sete r14b
and r14b, 1
mov cl, r14b
call Assert
jmp label44
label44:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayBoundary:
label45:
push rbp
mov rbp, rsp
sub rsp, 176
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 56]
mov qword ptr [r14], 42
mov r13, qword ptr [r14]
cmp r13, 42
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov cl, 1
call Assert
lea r13, qword ptr [rbp - 136]
mov qword ptr [r13], 1
lea r14, qword ptr [rbp - 136]
mov r12, r14
add r12, 8
mov qword ptr [r12], 2
lea r12, qword ptr [rbp - 136]
mov r14, r12
add r14, 16
mov qword ptr [r14], 3
lea r14, qword ptr [rbp - 136]
mov r12, r14
add r12, 24
mov qword ptr [r12], 4
lea r12, qword ptr [rbp - 136]
mov r14, r12
add r14, 32
mov qword ptr [r14], 5
lea r14, qword ptr [rbp - 136]
mov r12, r14
add r12, 40
mov qword ptr [r12], 6
lea r12, qword ptr [rbp - 136]
mov r14, r12
add r14, 48
mov qword ptr [r14], 7
lea r14, qword ptr [rbp - 136]
mov r12, r14
add r12, 56
mov qword ptr [r12], 8
lea r12, qword ptr [rbp - 136]
mov r14, r12
add r14, 64
mov qword ptr [r14], 9
lea r14, qword ptr [rbp - 136]
mov r12, r14
add r12, 72
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
jmp label47
label46:
lea r13, qword ptr [rbp - 136]
mov rdi, 0
imul rdi, 80
mov rsi, r13
add rsi, rdi
mov rdi, r14
imul rdi, 8
mov r13, rsi
add r13, rdi
mov rdi, qword ptr [r13]
mov r13, r12
add r13, rdi
jmp label48
label47:
cmp r14, 10
setl r13b
and r13b, 1
test r13b, r13b
jne label46
jmp label49
label48:
mov qword ptr [rbp - 144], r14
mov rdi, r14
add rdi, 1
mov r14, rdi
mov r12, r13
jmp label47
label49:
cmp r12, 55
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label50
label50:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArraySwap:
label51:
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
mov qword ptr [r14], 1
lea r13, qword ptr [rbp - 88]
mov r12, r13
add r12, 8
mov qword ptr [r12], 2
lea r13, qword ptr [rbp - 88]
mov rdi, r13
add rdi, 16
mov qword ptr [rdi], 3
lea r13, qword ptr [rbp - 88]
mov rsi, r13
add rsi, 24
mov qword ptr [rsi], 4
lea r13, qword ptr [rbp - 88]
mov rbx, r13
add rbx, 32
mov qword ptr [rbx], 5
mov r13, qword ptr [r14]
mov qword ptr [rbp - 96], r13
mov r13, qword ptr [rbx]
mov qword ptr [r14], r13
mov r13, qword ptr [rbp - 96]
mov qword ptr [rbx], r13
mov r13, qword ptr [r14]
cmp r13, 5
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rbx]
cmp r13, 1
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [r12]
cmp r13, 2
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rdi]
cmp r13, 3
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rsi]
cmp r13, 4
sete r13b
and r13b, 1
mov cl, r13b
call Assert
jmp label52
label52:
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
label53:
push rbp
mov rbp, rsp
sub rsp, 96
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 64]
mov qword ptr [r14], 10
lea r13, qword ptr [rbp - 64]
mov r12, r13
add r12, 8
mov qword ptr [r12], 20
lea r13, qword ptr [rbp - 64]
mov rdi, r13
add rdi, 16
mov qword ptr [rdi], 30
mov r13, qword ptr [r14]
mov rsi, qword ptr [r12]
cmp r13, rsi
setg sil
and sil, 1
mov r13, qword ptr [r14]
mov r14, qword ptr [r12]
mov r12, r14
test sil, sil
cmovne r12, r13
cmp r12, 20
sete r13b
and r13b, 1
mov cl, r13b
call Assert
mov r13, qword ptr [rdi]
cmp r12, r13
setg r13b
and r13b, 1
mov rsi, qword ptr [rdi]
mov rdi, rsi
test r13b, r13b
cmovne rdi, r12
cmp rdi, 30
sete dil
and dil, 1
mov cl, dil
call Assert
lea rdi, qword ptr [rbp - 64]
mov r12, 0
imul r12, 24
mov r13, rdi
add r13, r12
mov r12, 0
imul r12, 8
mov rdi, r13
add rdi, r12
mov r12, qword ptr [rdi]
cmp r12, 10
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
TestArrayAssignment:
label55:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 64]
mov qword ptr [r14], 1
lea r14, qword ptr [rbp - 64]
mov r13, r14
add r13, 8
mov qword ptr [r13], 2
lea r13, qword ptr [rbp - 64]
mov r14, r13
add r14, 16
mov qword ptr [r14], 3
mov r14, 0
jmp label57
label56:
lea rdi, qword ptr [rbp - 88]
mov r13, 0
imul r13, 24
mov r12, rdi
add r12, r13
mov r13, r14
imul r13, 8
mov rdi, r12
add rdi, r13
lea r13, qword ptr [rbp - 64]
mov r12, 0
imul r12, 24
mov rsi, r13
add rsi, r12
mov r12, r14
imul r12, 8
mov r13, rsi
add r13, r12
mov r12, qword ptr [r13]
mov qword ptr [rdi], r12
jmp label58
label57:
cmp r14, 3
setl r13b
and r13b, 1
test r13b, r13b
jne label56
jmp label59
label58:
mov qword ptr [rbp - 96], r14
mov r12, r14
add r12, 1
mov r14, r12
jmp label57
label59:
lea r13, qword ptr [rbp - 88]
mov r12, qword ptr [r13]
cmp r12, 1
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 88]
mov rdi, r12
add rdi, 8
mov r12, qword ptr [rdi]
cmp r12, 2
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 88]
mov rdi, r12
add rdi, 16
mov r12, qword ptr [rdi]
cmp r12, 3
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 64]
mov qword ptr [r12], 100
mov rdi, qword ptr [r12]
cmp rdi, 100
sete dil
and dil, 1
mov cl, dil
call Assert
mov rdi, qword ptr [r13]
cmp rdi, 1
sete dil
and dil, 1
mov cl, dil
call Assert
jmp label60
label60:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
TestArrayAccumulation:
label61:
push rbp
mov rbp, rsp
sub rsp, 128
mov qword ptr [rbp - 8], rsi
mov qword ptr [rbp - 16], r14
mov qword ptr [rbp - 24], r13
mov qword ptr [rbp - 32], r12
mov qword ptr [rbp - 40], rdi
lea r14, qword ptr [rbp - 80]
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 80]
mov r13, r14
add r13, 8
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 80]
mov r14, r13
add r14, 16
mov qword ptr [r14], 0
lea r14, qword ptr [rbp - 80]
mov r13, r14
add r13, 24
mov qword ptr [r13], 0
lea r13, qword ptr [rbp - 80]
mov r14, r13
add r14, 32
mov qword ptr [r14], 0
mov r14, 0
jmp label63
label62:
mov rax, r14
cqo
mov r12, 5
idiv r12
mov r12, rdx
lea r13, qword ptr [rbp - 80]
mov rdi, 0
imul rdi, 40
mov rsi, r13
add rsi, rdi
mov rdi, r12
imul rdi, 8
mov r12, rsi
add r12, rdi
mov rdi, qword ptr [r12]
mov qword ptr [rbp - 96], rdi
mov rsi, rdi
add rsi, 1
mov qword ptr [r12], rsi
jmp label64
label63:
cmp r14, 100
setl r13b
and r13b, 1
test r13b, r13b
jne label62
jmp label65
label64:
mov qword ptr [rbp - 88], r14
mov rsi, r14
add rsi, 1
mov r14, rsi
jmp label63
label65:
lea r13, qword ptr [rbp - 80]
mov r12, qword ptr [r13]
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 80]
mov r13, r12
add r13, 8
mov r12, qword ptr [r13]
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 80]
mov r13, r12
add r13, 16
mov r12, qword ptr [r13]
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 80]
mov r13, r12
add r13, 24
mov r12, qword ptr [r13]
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
lea r12, qword ptr [rbp - 80]
mov r13, r12
add r13, 32
mov r12, qword ptr [r13]
cmp r12, 20
sete r12b
and r12b, 1
mov cl, r12b
call Assert
jmp label66
label66:
mov rsi, qword ptr [rbp - 8]
mov r14, qword ptr [rbp - 16]
mov r13, qword ptr [rbp - 24]
mov r12, qword ptr [rbp - 32]
mov rdi, qword ptr [rbp - 40]
mov rsp, rbp
pop rbp
ret
.globl main

main:
label67:
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
jmp label69
label68:
call TestArrayNegativeValues
call TestAutoArray
call TestArrayBoundary
call TestArraySwap
call TestArrayTernary
call TestArrayAssignment
call TestArrayAccumulation
jmp label70
label69:
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
jmp label68
label70:
mov rax, 0
mov rsp, rbp
pop rbp
ret
