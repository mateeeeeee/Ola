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
	mov	qword ptr [rbp - 8], 0
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rbp - 16]       # 8-byte Reload
	mov	rax, qword ptr [rbp - 8]
	mov	rcx, rax
	add	rcx, 1
	mov	qword ptr [rbp - 8], rcx
	add	rax, rdx
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	cmp	rcx, 5
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %dowhile.end
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	sub	rax, 10
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	mov	qword ptr [rbp - 56], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rcx, rsp
	mov	qword ptr [rcx], 0
	mov	rax, qword ptr [rcx]
	mov	rdx, rax
	inc	rdx
	mov	qword ptr [rcx], rdx
	test	rax, rax
	sete	cl
	sub	rsp, 32
	call	Assert
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	add	rsp, 32
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, rcx
	mov	qword ptr [rbp - 48], rdx       # 8-byte Spill
	mov	qword ptr [rcx], 5
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
	mov	qword ptr [rax], 3
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
.LBB0_3:                                # %dowhile.body4
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 48]       # 8-byte Reload
	mov	r8, qword ptr [rbp - 40]        # 8-byte Reload
	mov	r9, qword ptr [rcx]
	mov	r10, qword ptr [r8]
	mov	rdx, r9
	add	rdx, rax
	cmp	r9, r10
	cmovg	rax, rdx
	mov	qword ptr [rbp - 64], rax       # 8-byte Spill
	mov	rdx, qword ptr [rcx]
	add	rdx, -1
	mov	qword ptr [rcx], rdx
	mov	rdx, qword ptr [r8]
	add	rdx, 1
	mov	qword ptr [r8], rdx
	cmp	qword ptr [rcx], 0
	setg	cl
	cmp	rdx, 10
	setl	dl
	and	cl, dl
	test	cl, 1
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	jne	.LBB0_3
# %bb.4:                                # %dowhile.end6
	mov	rax, qword ptr [rbp - 64]       # 8-byte Reload
	sub	rax, 5
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, rsp
	mov	qword ptr [rbp - 80], rax       # 8-byte Spill
	mov	qword ptr [rax], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rbp - 72], rax       # 8-byte Spill
.LBB0_5:                                # %dowhile.body7
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 80]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 72]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rbp - 96], rax       # 8-byte Spill
	add	rax, rcx
	mov	qword ptr [rbp - 88], rax       # 8-byte Spill
	cmp	rax, 9
	jle	.LBB0_7
.LBB0_6:                                # %dowhile.end9
	mov	rax, qword ptr [rbp - 88]       # 8-byte Reload
	cmp	rax, 10
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	rsp, rbp
	pop	rbp
	ret
.LBB0_7:                                # %if.end12
                                        #   in Loop: Header=BB0_5 Depth=1
	mov	rax, qword ptr [rbp - 88]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 80]       # 8-byte Reload
	mov	rcx, qword ptr [rbp - 96]       # 8-byte Reload
	add	rcx, 1
	mov	qword ptr [rdx], rcx
	cmp	rcx, 6
	mov	qword ptr [rbp - 72], rax       # 8-byte Spill
	jl	.LBB0_5
	jmp	.LBB0_6
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
