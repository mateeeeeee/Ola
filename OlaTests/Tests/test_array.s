	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_array.ola"
	.def	modifyArray;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function modifyArray
modifyArray:                            # @modifyArray
# %bb.0:                                # %entry
	mov	qword ptr [rcx], 100
	ret
                                        # -- End function
	.def	sumOfArray;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function sumOfArray
sumOfArray:                             # @sumOfArray
.seh_proc sumOfArray
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 24], rdx       # 8-byte Spill
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	mov	qword ptr [rsp + 40], 0
	cmp	rdx, 0
	jle	.LBB1_4
# %bb.1:                                # %for.body.lr.ph
	mov	rcx, qword ptr [rsp + 40]
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rcx        # 8-byte Spill
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
.LBB1_2:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rsp + 16]       # 8-byte Reload
	mov	rcx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rdx, qword ptr [rsp + 24]       # 8-byte Reload
	mov	r8, qword ptr [rsp + 32]        # 8-byte Reload
	add	rcx, qword ptr [r8 + 8*rax]
	mov	qword ptr [rsp], rcx            # 8-byte Spill
	add	rax, 1
	cmp	rax, rdx
	mov	qword ptr [rsp + 8], rcx        # 8-byte Spill
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
	jl	.LBB1_2
# %bb.3:                                # %for.cond.for.end_crit_edge
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	mov	qword ptr [rsp + 40], rax
.LBB1_4:                                # %for.end
	mov	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 184
	.seh_stackalloc 184
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	cmp	qword ptr [rip + GlobalArray3], 10
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 104], 1
	mov	qword ptr [rsp + 112], 2
	mov	qword ptr [rsp + 120], 0
	mov	qword ptr [rsp + 128], 0
	mov	qword ptr [rsp + 136], 0
	mov	qword ptr [rsp + 144], 0
	mov	qword ptr [rsp + 152], 0
	mov	qword ptr [rsp + 160], 0
	mov	qword ptr [rsp + 168], 0
	mov	qword ptr [rsp + 176], 0
	mov	ecx, 1
	call	Assert
	cmp	qword ptr [rsp + 152], 0
	sete	cl
	call	Assert
	lea	rcx, [rsp + 104]
	mov	edx, 10
	call	sumOfArray
	cmp	rax, 3
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 80], -5
	mov	qword ptr [rsp + 88], 0
	mov	qword ptr [rsp + 96], 5
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	lea	rcx, [rsp + 80]
	call	modifyArray
	cmp	qword ptr [rsp + 80], 100
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 80], 100
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 80], 1000
	mov	ecx, 1
	call	Assert
	cmp	qword ptr [rsp + 80], 1000
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 1
	mov	qword ptr [rsp + 56], 2
	mov	qword ptr [rsp + 64], 3
	mov	qword ptr [rsp + 72], 4
	mov	rdx, qword ptr [rip + Global2dArray+8]
	add	rdx, qword ptr [rip + Global2dArray]
	mov	rcx, qword ptr [rsp + 56]
	add	rcx, qword ptr [rsp + 48]
	mov	rax, qword ptr [rip + Global2dArray+24]
	add	rdx, qword ptr [rip + Global2dArray+16]
	add	rax, rdx
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	mov	rax, qword ptr [rsp + 72]
	add	rcx, qword ptr [rsp + 64]
	add	rax, rcx
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	cmp	rax, 10
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 184
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @GlobalArray1
GlobalArray1:
	.quad	1                               # 0x1
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.p2align	4, 0x0                          # @GlobalArray2
GlobalArray2:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	0                               # 0x0
	.quad	0                               # 0x0

	.p2align	4, 0x0                          # @GlobalArray3
GlobalArray3:
	.quad	10                              # 0xa
	.quad	20                              # 0x14
	.quad	30                              # 0x1e

	.p2align	4, 0x0                          # @Global2dArray
Global2dArray:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym modifyArray
	.addrsig_sym sumOfArray
	.addrsig_sym GlobalArray3
	.addrsig_sym Global2dArray
