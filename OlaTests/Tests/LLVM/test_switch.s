	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_switch.ola"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 64
	.seh_stackalloc 64
	lea	rbp, [rsp + 64]
	.seh_setframe rbp, 64
	.seh_endprologue
	mov	qword ptr [rbp - 16], 2
# %bb.1:                                # %switch.header
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	sub	rax, 1
	je	.LBB0_4
	jmp	.LBB0_20
.LBB0_20:                               # %switch.header
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	sub	rax, 2
	je	.LBB0_5
	jmp	.LBB0_21
.LBB0_21:                               # %switch.header
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	sub	rax, 3
	je	.LBB0_6
	jmp	.LBB0_2
.LBB0_2:                                # %switch.default
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB0_3:                                # %switch.end
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	qword ptr [rax], 1
	jmp	.LBB0_7
.LBB0_4:                                # %switch.case1
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_5:                                # %switch.case2
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_6:                                # %switch.case3
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_7:                                # %switch.header4
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
	sub	rax, 1
	je	.LBB0_10
	jmp	.LBB0_22
.LBB0_22:                               # %switch.header4
	mov	rax, qword ptr [rbp - 40]       # 8-byte Reload
	sub	rax, 2
	je	.LBB0_11
	jmp	.LBB0_23
.LBB0_23:                               # %switch.header4
	mov	rax, qword ptr [rbp - 40]       # 8-byte Reload
	sub	rax, 3
	je	.LBB0_12
	jmp	.LBB0_8
.LBB0_8:                                # %switch.default5
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB0_9:                                # %switch.end6
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 48], rax       # 8-byte Spill
	mov	qword ptr [rax], 5
	jmp	.LBB0_13
.LBB0_10:                               # %switch.case17
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB0_11:                               # %switch.case28
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_9
.LBB0_12:                               # %switch.case310
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_9
.LBB0_13:                               # %switch.header13
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 56], rax       # 8-byte Spill
	sub	rax, 1
	je	.LBB0_16
	jmp	.LBB0_24
.LBB0_24:                               # %switch.header13
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	sub	rax, 2
	je	.LBB0_17
	jmp	.LBB0_25
.LBB0_25:                               # %switch.header13
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	sub	rax, 3
	je	.LBB0_18
	jmp	.LBB0_14
.LBB0_14:                               # %switch.default14
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB0_15:                               # %switch.end15
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB0_19
.LBB0_16:                               # %switch.case116
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_15
.LBB0_17:                               # %switch.case218
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_15
.LBB0_18:                               # %switch.case320
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_15
.LBB0_19:                               # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
