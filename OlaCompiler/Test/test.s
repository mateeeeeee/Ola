	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
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
	mov	qword ptr [rbp - 16], 10
	cmp	qword ptr [rbp - 16], 1
	jne	.LBB0_2
# %bb.1:                                # %if.then
	xor	eax, eax
	mov	ecx, eax
	sub	rsp, 32
	call	PrintInt
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	mov	eax, 16
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 56], rcx       # 8-byte Spill
	mov	rdx, rcx
	mov	qword ptr [rbp - 64], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 40], rcx       # 8-byte Spill
	mov	rdx, rcx
	mov	qword ptr [rbp - 48], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 1
	mov	rcx, qword ptr [rax]
	sub	rsp, 32
	call	PrintInt
	mov	rax, qword ptr [rbp - 40]       # 8-byte Reload
	add	rsp, 32
	mov	rcx, qword ptr [rax]
	sub	rsp, 32
	call	PrintInt
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	add	rsp, 32
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	mov	qword ptr [rax], 2
	jmp	.LBB0_5
.LBB0_3:                                # %if.end
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB0_8
.LBB0_4:                                # %for.body
                                        #   in Loop: Header=BB0_5 Depth=1
	mov	rcx, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 64]       # 8-byte Reload
	mov	r8, qword ptr [rdx]
	mov	rax, qword ptr [rcx]
	add	r8, rax
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rax], r8
	mov	r8, qword ptr [rcx]
	mov	qword ptr [rdx], r8
	mov	rdx, qword ptr [rax]
	mov	qword ptr [rcx], rdx
	mov	rcx, qword ptr [rax]
	sub	rsp, 32
	call	PrintInt
	add	rsp, 32
	jmp	.LBB0_6
.LBB0_5:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	cmp	rax, qword ptr [rbp - 16]
	jl	.LBB0_4
	jmp	.LBB0_7
.LBB0_6:                                # %for.iter
                                        #   in Loop: Header=BB0_5 Depth=1
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, qword ptr [rax]
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rdx, rsp
	mov	r8, qword ptr [rax]
	mov	qword ptr [rdx], r8
	add	rcx, 1
	mov	qword ptr [rax], rcx
	jmp	.LBB0_5
.LBB0_7:                                # %for.end
	jmp	.LBB0_3
.LBB0_8:                                # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInt
