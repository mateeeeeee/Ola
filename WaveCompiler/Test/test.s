	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
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
	sub	rsp, 48
	.seh_stackalloc 48
	lea	rbp, [rsp + 48]
	.seh_setframe rbp, 48
	.seh_endprologue
	mov	qword ptr [rbp - 16], 0
	mov	qword ptr [rbp - 24], 0
	lea	rax, [rip + Global2dArray]
	mov	qword ptr [rbp - 32], rax
	mov	rax, qword ptr [rbp - 32]
	mov	qword ptr [rip + Global2dArray], rax
	mov	qword ptr [rbp - 40], 0
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 48], rax       # 8-byte Spill
	mov	qword ptr [rax], 0
	jmp	.LBB0_6
.LBB0_2:                                # %for.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_6 Depth 2
	cmp	qword ptr [rbp - 40], 2
	jl	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	mov	rax, qword ptr [rbp - 40]
	add	rax, 1
	mov	qword ptr [rbp - 40], rax
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	cmp	qword ptr [rbp - 16], 10
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	rcx, qword ptr [rbp - 16]
	sub	rsp, 32
	call	PrintInt
	add	rsp, 32
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB0_9
.LBB0_5:                                # %for.body1
                                        #   in Loop: Header=BB0_6 Depth=2
	mov	rcx, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 40]
	shl	rdx, 3
	add	rdx, qword ptr [rbp - 32]
	mov	r8, qword ptr [rcx]
	mov	rax, qword ptr [rbp - 16]
	add	rax, qword ptr [rdx + 8*r8]
	mov	qword ptr [rbp - 16], rax
	mov	rax, qword ptr [rbp - 40]
	shl	rax, 3
	add	rax, qword ptr [rbp - 32]
	mov	rcx, qword ptr [rcx]
	mov	rcx, qword ptr [rax + 8*rcx]
	sub	rsp, 32
	call	PrintInt
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	add	rsp, 32
	mov	rdx, qword ptr [rbp - 40]
	shl	rdx
	lea	rcx, [rip + Global2dArray]
	shl	rdx, 3
	add	rcx, rdx
	mov	rdx, qword ptr [rax]
	mov	rax, qword ptr [rbp - 24]
	add	rax, qword ptr [rcx + 8*rdx]
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB0_7
.LBB0_6:                                # %for.cond2
                                        #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	cmp	qword ptr [rax], 2
	jl	.LBB0_5
	jmp	.LBB0_8
.LBB0_7:                                # %for.iter3
                                        #   in Loop: Header=BB0_6 Depth=2
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	jmp	.LBB0_6
.LBB0_8:                                # %for.end4
                                        #   in Loop: Header=BB0_2 Depth=1
	jmp	.LBB0_3
.LBB0_9:                                # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @Global2dArray
Global2dArray:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.addrsig
	.addrsig_sym PrintInt
	.addrsig_sym Assert
	.addrsig_sym Global2dArray
