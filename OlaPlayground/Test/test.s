.intel_syntax noprefix

.section .rodata

_INT0:
.quad 42


_FP0:
.quad 4631107791820423168


_FP1:
.quad 4614253070214989087


_INT1:
.quad 1


_FP2:
.quad 4607182418800017408


.section .text

.extern Assert

.extern AssertMsg

TestImplicitCastAssignInit:
label0:
push rbp
mov rbp, rsp
sub rsp, 49
cvtsi2sd xmm15, qword ptr [rip + _INT0]
comisd xmm15, qword ptr [rip + _FP0]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov rcx, 1
call Assert
cvttsd2si r15, qword ptr [rip + _FP1]
cmp r15, 3
sete r15b
and r15b, 1
mov cl, r15b
call Assert
mov rcx, 1
call Assert
mov r15, 1
cvtsi2sd xmm15, qword ptr [rip + _INT1]
cmp r15, 1
sete r15b
and r15b, 1
mov cl, r15b
call Assert
comisd xmm15, qword ptr [rip + _FP2]
sete r15b
and r15b, 1
mov cl, r15b
call Assert
jmp label1
label1:
mov rsp, rbp
pop rbp
ret

.globl main

main:
label2:
push rbp
mov rbp, rsp
sub rsp, 40
call TestImplicitCastAssignInit
jmp label4
label3:
jmp label4
label4:
mov rax, 0
mov rsp, rbp
pop rbp
ret

