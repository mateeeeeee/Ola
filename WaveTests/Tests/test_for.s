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
	sub	rsp, 160
	.seh_stackalloc 160
	lea	rbp, [rsp + 128]
	.seh_setframe rbp, 128
	.seh_endprologue
	mov	qword ptr [rbp + 24], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rbp + 16], rax       # 8-byte Spill
.LBB0_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rbp + 16]       # 8-byte Reload
	mov	rcx, qword ptr [rbp + 24]
	mov	rax, rcx
	add	rax, rdx
	mov	qword ptr [rbp + 8], rax        # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rbp + 24], rcx
	cmp	rcx, 6
	mov	qword ptr [rbp + 16], rax       # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %for.cond.for.end_crit_edge
	mov	rax, qword ptr [rbp + 8]        # 8-byte Reload
	sub	rax, 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 16], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 16]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 8], rcx        # 8-byte Spill
	mov	qword ptr [rcx], 1
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp], rax            # 8-byte Spill
.LBB0_3:                                # %for.body1
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rbp]            # 8-byte Reload
	mov	rdx, qword ptr [rbp - 8]        # 8-byte Reload
	mov	rax, qword ptr [rdx]
	mov	r8, rax
	and	r8, 1
	add	rax, rcx
	cmp	r8, 0
	cmove	rax, rcx
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	rcx, qword ptr [rdx]
	add	rcx, 1
	mov	qword ptr [rdx], rcx
	cmp	rcx, 6
	mov	qword ptr [rbp], rax            # 8-byte Spill
	jl	.LBB0_3
# %bb.4:                                # %for.cond2.for.end4_crit_edge
	mov	rax, qword ptr [rbp - 16]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 32]       # 8-byte Reload
	mov	qword ptr [rax], rcx
	mov	rax, qword ptr [rax]
	sub	rax, 9
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 64], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 64]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 56], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 48], rcx       # 8-byte Spill
	mov	qword ptr [rcx], 1
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
.LBB0_5:                                # %for.body5
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 40]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 80], rax       # 8-byte Spill
	mov	rcx, rax
	add	rcx, rdx
	mov	qword ptr [rbp - 72], rcx       # 8-byte Spill
	cmp	rax, 5
	je	.LBB0_8
	jmp	.LBB0_9
.LBB0_6:                                # %for.cond6.for.end8.loopexit_crit_edge
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 72]       # 8-byte Reload
	mov	qword ptr [rax], rcx
.LBB0_7:                                # %for.end8
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	sub	rax, 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 112], rax      # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rax], 1
	mov	rcx, qword ptr [rax]
	imul	rcx, rcx, 3840
	mov	qword ptr [rax], rcx
	mov	rax, qword ptr [rax]
	sub	rax, 3840
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	rax, qword ptr [rbp - 112]      # 8-byte Reload
	add	rsp, 32
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 112]      # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 104], rdx      # 8-byte Spill
	mov	qword ptr [rcx], 1
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 104]      # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 96], rcx       # 8-byte Spill
	mov	qword ptr [rcx], 5
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 88], rax       # 8-byte Spill
	jmp	.LBB0_10
.LBB0_8:                                # %if.then9
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 72]       # 8-byte Reload
	mov	qword ptr [rax], rcx
	jmp	.LBB0_7
.LBB0_9:                                # %if.end11
                                        #   in Loop: Header=BB0_5 Depth=1
	mov	rax, qword ptr [rbp - 72]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 80]       # 8-byte Reload
	add	rcx, 1
	mov	qword ptr [rdx], rcx
	cmp	rcx, 11
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
	jl	.LBB0_5
	jmp	.LBB0_6
.LBB0_10:                               # %for.body16
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rbp - 88]       # 8-byte Reload
	mov	r8, qword ptr [rbp - 96]        # 8-byte Reload
	mov	rax, qword ptr [r8]
	mov	rcx, rax
	add	rcx, -1
	mov	qword ptr [r8], rcx
	imul	rax, rdx
	mov	qword ptr [rbp - 120], rax      # 8-byte Spill
	cmp	rcx, 0
	mov	qword ptr [rbp - 88], rax       # 8-byte Spill
	jg	.LBB0_10
# %bb.11:                               # %for.cond17.for.end19_crit_edge
	mov	rax, qword ptr [rbp - 104]      # 8-byte Reload
	mov	rcx, qword ptr [rbp - 120]      # 8-byte Reload
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rax], 120
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	xor	eax, eax
                                        # kill: def $rax killed $eax
	lea	rsp, [rbp + 32]
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
