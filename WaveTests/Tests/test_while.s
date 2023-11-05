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
	sub	rsp, 96
	.seh_stackalloc 96
	lea	rbp, [rsp + 96]
	.seh_setframe rbp, 96
	.seh_endprologue
	mov	qword ptr [rbp - 8], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
.LBB0_1:                                # %while.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rbp - 16]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 8]
	mov	rax, rcx
	add	rax, rdx
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rbp - 8], rcx
	cmp	rcx, 6
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %while.cond.while.end_crit_edge
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	sub	rax, 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 48], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rax], 0
	mov	rax, qword ptr [rax]
	test	rax, rax
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	add	rsp, 32
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 40], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 5
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	qword ptr [rax], 0
.LBB0_3:                                # %while.body5
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rax, qword ptr [rcx]
	add	rax, 1
	mov	qword ptr [rcx], rax
	cmp	rax, 5
	jne	.LBB0_3
# %bb.4:                                # %if.then
	mov	rcx, qword ptr [rbp - 40]       # 8-byte Reload
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	rcx, qword ptr [rcx]
	sub	rax, rcx
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 80], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 80]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 72], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 72]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 64], rcx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 56], rax       # 8-byte Spill
.LBB0_5:                                # %while.body8
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 64]       # 8-byte Reload
	mov	rax, qword ptr [rcx]
	add	rax, 1
	mov	qword ptr [rcx], rax
	mov	r8, rax
	and	r8, 1
	add	rax, rdx
	cmp	r8, 0
	cmove	rax, rdx
	mov	qword ptr [rbp - 88], rax       # 8-byte Spill
	cmp	qword ptr [rcx], 5
	mov	qword ptr [rbp - 56], rax       # 8-byte Spill
	jl	.LBB0_5
# %bb.6:                                # %while.cond7.while.end9_crit_edge
	mov	rax, qword ptr [rbp - 72]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 88]       # 8-byte Reload
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rax], 9
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
