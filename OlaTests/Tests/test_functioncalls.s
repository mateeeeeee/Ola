	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_functioncalls.ola"
	.def	Add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function Add
Add:                                    # @Add
# %bb.0:                                # %entry
	mov	rax, rdx
	add	rax, rcx
	ret
                                        # -- End function
	.def	Multiply;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function Multiply
Multiply:                               # @Multiply
# %bb.0:                                # %entry
	mulsd	xmm0, xmm1
	ret
                                        # -- End function
	.def	LogicalAnd;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function LogicalAnd
LogicalAnd:                             # @LogicalAnd
# %bb.0:                                # %entry
	mov	al, cl
	and	al, dl
	ret
                                        # -- End function
	.def	MixParams;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@3ff0000000000000         # -- Begin function MixParams
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.text
	.p2align	4, 0x90
MixParams:                              # @MixParams
.seh_proc MixParams
# %bb.0:                                # %entry
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	mov	qword ptr [rsp + 40], r9        # 8-byte Spill
	movsd	qword ptr [rsp + 48], xmm1      # 8-byte Spill
	mov	qword ptr [rsp + 56], rcx       # 8-byte Spill
	mov	rcx, qword ptr [rsp + 144]
	mov	qword ptr [rsp + 64], rcx       # 8-byte Spill
	mov	byte ptr [rsp + 79], r8b        # 1-byte Spill
	mov	qword ptr [rsp + 96], 0
	xor	eax, eax
                                        # kill: def $rax killed $eax
	xorps	xmm0, xmm0
	cmp	rcx, 0
	mov	qword ptr [rsp + 80], rax       # 8-byte Spill
	movsd	qword ptr [rsp + 88], xmm0      # 8-byte Spill
	jle	.LBB3_3
.LBB3_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rsp + 80]       # 8-byte Reload
	mov	rdx, qword ptr [rsp + 64]       # 8-byte Reload
	mov	r8, qword ptr [rsp + 40]        # 8-byte Reload
	mov	rcx, qword ptr [rsp + 96]
	add	rax, qword ptr [r8 + 8*rcx]
	mov	qword ptr [rsp + 32], rax       # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rsp + 96], rcx
	cmp	rcx, rdx
	mov	qword ptr [rsp + 80], rax       # 8-byte Spill
	jl	.LBB3_1
# %bb.2:                                # %for.cond.for.end_crit_edge
	mov	rax, qword ptr [rsp + 32]       # 8-byte Reload
	cvtsi2sd	xmm0, rax
	movsd	qword ptr [rsp + 88], xmm0      # 8-byte Spill
.LBB3_3:                                # %exit
	mov	al, byte ptr [rsp + 79]         # 1-byte Reload
	movsd	xmm1, qword ptr [rsp + 48]      # 8-byte Reload
                                        # xmm1 = mem[0],zero
	mov	rcx, qword ptr [rsp + 56]       # 8-byte Reload
	movsd	xmm0, qword ptr [rsp + 88]      # 8-byte Reload
                                        # xmm0 = mem[0],zero
	movsd	qword ptr [rsp], xmm0           # 8-byte Spill
	cvtsi2sd	xmm0, rcx
	addsd	xmm0, xmm1
	movsd	qword ptr [rsp + 8], xmm0       # 8-byte Spill
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	xorps	xmm1, xmm1
	movsd	qword ptr [rsp + 16], xmm1      # 8-byte Spill
	test	al, 1
	movsd	qword ptr [rsp + 24], xmm0      # 8-byte Spill
	jne	.LBB3_5
# %bb.4:                                # %exit
	movsd	xmm0, qword ptr [rsp + 16]      # 8-byte Reload
                                        # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 24], xmm0      # 8-byte Spill
.LBB3_5:                                # %exit
	movsd	xmm1, qword ptr [rsp]           # 8-byte Reload
                                        # xmm1 = mem[0],zero
	movsd	xmm0, qword ptr [rsp + 8]       # 8-byte Reload
                                        # xmm0 = mem[0],zero
	movsd	xmm2, qword ptr [rsp + 24]      # 8-byte Reload
                                        # xmm2 = mem[0],zero
	addsd	xmm0, xmm2
	addsd	xmm0, xmm1
	add	rsp, 104
	ret
	.seh_endproc
                                        # -- End function
	.def	ConcatArrays;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ConcatArrays
ConcatArrays:                           # @ConcatArrays
.seh_proc ConcatArrays
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 64
	.seh_stackalloc 64
	lea	rbp, [rsp + 64]
	.seh_setframe rbp, 64
	.seh_endprologue
	mov	qword ptr [rbp - 48], r9        # 8-byte Spill
	mov	qword ptr [rbp - 40], r8        # 8-byte Spill
	mov	qword ptr [rbp - 32], rdx       # 8-byte Spill
	mov	qword ptr [rbp - 24], rcx       # 8-byte Spill
	mov	rax, qword ptr [rbp + 48]
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
	mov	qword ptr [rbp - 8], 0
	cmp	rdx, 0
	jle	.LBB4_2
.LBB4_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rax, qword ptr [rbp - 16]       # 8-byte Reload
	mov	r8, qword ptr [rbp - 24]        # 8-byte Reload
	mov	rdx, qword ptr [rbp - 8]
	mov	r8, qword ptr [r8 + 8*rdx]
	mov	qword ptr [rax + 8*rdx], r8
	mov	rax, qword ptr [rbp - 8]
	add	rax, 1
	mov	qword ptr [rbp - 8], rax
	cmp	rax, rcx
	jl	.LBB4_1
.LBB4_2:                                # %for.end
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rbp - 56], rcx       # 8-byte Spill
	mov	qword ptr [rcx], 0
	cmp	rax, 0
	jle	.LBB4_4
.LBB4_3:                                # %for.body1
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rbp - 48]       # 8-byte Reload
	mov	rdx, qword ptr [rbp - 56]       # 8-byte Reload
	mov	rax, qword ptr [rbp - 16]       # 8-byte Reload
	mov	r9, qword ptr [rbp - 40]        # 8-byte Reload
	mov	r11, qword ptr [rbp - 32]       # 8-byte Reload
	mov	r10, qword ptr [rdx]
	mov	r8, r10
	add	r8, r11
	mov	r9, qword ptr [r9 + 8*r10]
	mov	qword ptr [rax + 8*r8], r9
	mov	rax, qword ptr [rdx]
	add	rax, 1
	mov	qword ptr [rdx], rax
	cmp	rax, rcx
	jl	.LBB4_3
.LBB4_4:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@4041400000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@4041400000000000
	.p2align	3, 0x0
__real@4041400000000000:
	.quad	0x4041400000000000              # double 34.5
	.globl	__real@4004000000000000
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.globl	__real@401e000000000000
	.section	.rdata,"dr",discard,__real@401e000000000000
	.p2align	3, 0x0
__real@401e000000000000:
	.quad	0x401e000000000000              # double 7.5
	.globl	__real@4008000000000000
	.section	.rdata,"dr",discard,__real@4008000000000000
	.p2align	3, 0x0
__real@4008000000000000:
	.quad	0x4008000000000000              # double 3
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 120
	.seh_stackalloc 120
	.seh_endprologue
	mov	ecx, 3
	mov	edx, 5
	call	Add
	cmp	rax, 8
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4008000000000000] # xmm1 = mem[0],zero
	call	Multiply
	movsd	xmm1, qword ptr [rip + __real@401e000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	ecx, 1
	xor	edx, edx
	call	LogicalAnd
	mov	cl, al
	xor	cl, -1
	call	Assert
	mov	qword ptr [rsp + 104], 10
	mov	qword ptr [rsp + 112], 20
	mov	ecx, 1
	movsd	xmm1, qword ptr [rip + __real@4004000000000000] # xmm1 = mem[0],zero
	mov	r8d, 1
	lea	r9, [rsp + 104]
	mov	qword ptr [rsp + 32], 2
	call	MixParams
	movsd	xmm1, qword ptr [rip + __real@4041400000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	qword ptr [rsp + 88], 1
	mov	qword ptr [rsp + 96], 2
	mov	qword ptr [rsp + 72], 3
	mov	qword ptr [rsp + 80], 4
	mov	qword ptr [rsp + 40], 0
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 56], 0
	mov	qword ptr [rsp + 64], 0
	lea	rcx, [rsp + 88]
	mov	r9d, 2
	lea	r8, [rsp + 72]
	lea	rax, [rsp + 40]
	mov	rdx, r9
	mov	qword ptr [rsp + 32], rax
	call	ConcatArrays
	cmp	qword ptr [rsp + 40], 1
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 48], 2
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 56], 3
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 64], 4
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 120
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym Add
	.addrsig_sym Multiply
	.addrsig_sym LogicalAnd
	.addrsig_sym MixParams
	.addrsig_sym ConcatArrays
	.globl	_fltused
