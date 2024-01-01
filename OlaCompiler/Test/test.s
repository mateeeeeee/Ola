	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	modifyArray__I0;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function modifyArray__I0
modifyArray__I0:                        # @modifyArray__I0
.seh_proc modifyArray__I0
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rax], 100
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	modifyArrayCopy__I3;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function modifyArrayCopy__I3
modifyArrayCopy__I3:                    # @modifyArrayCopy__I3
.seh_proc modifyArrayCopy__I3
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp + 16], r8
	mov	qword ptr [rsp], 100
# %bb.1:                                # %exit
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	sumOfArray__I0__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function sumOfArray__I0__I
sumOfArray__I0__I:                      # @sumOfArray__I0__I
.seh_proc sumOfArray__I0__I
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	mov	qword ptr [rsp + 24], rdx
	mov	qword ptr [rsp + 8], 0
	mov	qword ptr [rsp], 0
	jmp	.LBB2_2
.LBB2_1:                                # %for.body
                                        #   in Loop: Header=BB2_2 Depth=1
	mov	rdx, qword ptr [rsp]
	mov	rcx, qword ptr [rsp + 32]
	mov	rax, qword ptr [rsp + 8]
	add	rax, qword ptr [rcx + 8*rdx]
	mov	qword ptr [rsp + 8], rax
	jmp	.LBB2_3
.LBB2_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rsp]
	cmp	rax, qword ptr [rsp + 24]
	jl	.LBB2_1
	jmp	.LBB2_4
.LBB2_3:                                # %for.iter
                                        #   in Loop: Header=BB2_2 Depth=1
	mov	rax, qword ptr [rsp]
	add	rax, 1
	mov	qword ptr [rsp], rax
	jmp	.LBB2_2
.LBB2_4:                                # %for.end
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rsp + 16], rax
# %bb.5:                                # %exit
	mov	rax, qword ptr [rsp + 16]
	add	rsp, 40
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
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 208
	.seh_stackalloc 208
	lea	rbp, [rsp + 128]
	.seh_setframe rbp, 128
	.seh_endprologue
	sub	rsp, 32
	mov	cl, 1
	mov	byte ptr [rbp - 105], cl        # 1-byte Spill
	call	Assert
	mov	cl, byte ptr [rbp - 105]        # 1-byte Reload
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rip + GlobalArray3]
	sub	rax, 10
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	cl, byte ptr [rbp - 105]        # 1-byte Reload
	add	rsp, 32
	mov	qword ptr [rbp - 8], 1
	mov	qword ptr [rbp], 2
	mov	qword ptr [rbp + 8], 0
	mov	qword ptr [rbp + 16], 0
	mov	qword ptr [rbp + 24], 0
	mov	qword ptr [rbp + 32], 0
	mov	qword ptr [rbp + 40], 0
	mov	qword ptr [rbp + 48], 0
	mov	qword ptr [rbp + 56], 0
	mov	qword ptr [rbp + 64], 0
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rbp + 40]
	test	rax, rax
	sete	cl
	sub	rsp, 32
	call	Assert
	lea	rcx, [rbp - 8]
	mov	edx, 10
	call	sumOfArray__I0__I
	add	rsp, 32
	sub	rax, 3
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	qword ptr [rbp - 32], -5
	mov	qword ptr [rbp - 24], 0
	mov	qword ptr [rbp - 16], 5
	mov	rax, qword ptr [rbp - 24]
	test	rax, rax
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	cl, byte ptr [rbp - 105]        # 1-byte Reload
	call	Assert
	add	rsp, 32
	lea	rax, [rbp - 32]
	mov	qword ptr [rbp - 104], rax      # 8-byte Spill
	mov	qword ptr [rbp - 40], rax
	mov	r8, qword ptr [rbp - 16]
	mov	rcx, qword ptr [rbp - 32]
	mov	rdx, qword ptr [rbp - 24]
	sub	rsp, 32
	call	modifyArrayCopy__I3
	add	rsp, 32
	mov	rax, qword ptr [rbp - 32]
	sub	rax, -5
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rbp - 40]
	mov	rax, qword ptr [rax]
	sub	rax, -5
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	rcx, qword ptr [rbp - 104]      # 8-byte Reload
	call	modifyArray__I0
	add	rsp, 32
	mov	rax, qword ptr [rbp - 32]
	sub	rax, 100
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rbp - 40]
	mov	rax, qword ptr [rax]
	sub	rax, 100
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rbp - 40]
	mov	qword ptr [rax], 1000
	mov	rax, qword ptr [rbp - 32]
	sub	rax, 1000
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rax, qword ptr [rbp - 40]
	mov	rax, qword ptr [rax]
	sub	rax, 1000
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	qword ptr [rbp - 48], 0
	mov	qword ptr [rbp - 56], 0
	mov	qword ptr [rbp - 80], 2
	mov	qword ptr [rbp - 88], 1
	mov	qword ptr [rbp - 64], 4
	mov	qword ptr [rbp - 72], 3
	mov	qword ptr [rbp - 96], 0
	jmp	.LBB3_2
.LBB3_1:                                # %for.body
                                        #   in Loop: Header=BB3_2 Depth=1
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 120], rax      # 8-byte Spill
	mov	qword ptr [rax], 0
	jmp	.LBB3_6
.LBB3_2:                                # %for.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_6 Depth 2
	cmp	qword ptr [rbp - 96], 2
	jl	.LBB3_1
	jmp	.LBB3_4
.LBB3_3:                                # %for.iter
                                        #   in Loop: Header=BB3_2 Depth=1
	mov	rax, qword ptr [rbp - 96]
	add	rax, 1
	mov	qword ptr [rbp - 96], rax
	jmp	.LBB3_2
.LBB3_4:                                # %for.end
	cmp	qword ptr [rbp - 48], 10
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	cmp	qword ptr [rbp - 56], 10
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	qword ptr [rbp + 72], 0
	jmp	.LBB3_9
.LBB3_5:                                # %for.body1
                                        #   in Loop: Header=BB3_6 Depth=2
	mov	rax, qword ptr [rbp - 120]      # 8-byte Reload
	mov	rcx, qword ptr [rbp - 96]
	lea	rdx, [rbp - 88]
	shl	rcx, 4
	add	rdx, rcx
	mov	r8, qword ptr [rax]
	mov	rcx, qword ptr [rbp - 48]
	add	rcx, qword ptr [rdx + 8*r8]
	mov	qword ptr [rbp - 48], rcx
	mov	rdx, qword ptr [rbp - 96]
	shl	rdx
	lea	rcx, [rip + Global2dArray]
	shl	rdx, 3
	add	rcx, rdx
	mov	rdx, qword ptr [rax]
	mov	rax, qword ptr [rbp - 56]
	add	rax, qword ptr [rcx + 8*rdx]
	mov	qword ptr [rbp - 56], rax
	jmp	.LBB3_7
.LBB3_6:                                # %for.cond2
                                        #   Parent Loop BB3_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	rax, qword ptr [rbp - 120]      # 8-byte Reload
	cmp	qword ptr [rax], 2
	jl	.LBB3_5
	jmp	.LBB3_8
.LBB3_7:                                # %for.iter3
                                        #   in Loop: Header=BB3_6 Depth=2
	mov	rax, qword ptr [rbp - 120]      # 8-byte Reload
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	jmp	.LBB3_6
.LBB3_8:                                # %for.end4
                                        #   in Loop: Header=BB3_2 Depth=1
	jmp	.LBB3_3
.LBB3_9:                                # %exit
	mov	rax, qword ptr [rbp + 72]
	lea	rsp, [rbp + 80]
	pop	rbp
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
	.addrsig_sym modifyArray__I0
	.addrsig_sym modifyArrayCopy__I3
	.addrsig_sym sumOfArray__I0__I
	.addrsig_sym GlobalArray3
	.addrsig_sym Global2dArray
