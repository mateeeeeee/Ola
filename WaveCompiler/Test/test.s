	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	func;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function func
func:                                   # @func
.seh_proc func
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], rcx        # 8-byte Spill
	cmp	rcx, 0
	jle	.LBB0_2
# %bb.1:                                # %if.then
	mov	rcx, qword ptr [rbp - 8]        # 8-byte Reload
	sub	rsp, 32
	call	PrintInteger
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	mov	rax, qword ptr [rbp - 8]        # 8-byte Reload
	xor	ecx, ecx
                                        # kill: def $rcx killed $ecx
	sub	rcx, rax
	sub	rsp, 32
	call	PrintInteger
	add	rsp, 32
.LBB0_3:                                # %if.end
# %bb.4:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@4004000000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.globl	__real@4000000000000000
	.section	.rdata,"dr",discard,__real@4000000000000000
	.p2align	3, 0x0
__real@4000000000000000:
	.quad	0x4000000000000000              # double 2
	.globl	__real@3ff0000000000000
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	ecx, 5
	sub	rsp, 32
	call	func
	add	rsp, 32
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rbp - 16], xmm0
	movsd	xmm0, qword ptr [rip + __real@4000000000000000] # xmm0 = mem[0],zero
	addsd	xmm0, qword ptr [rbp - 16]
	movsd	qword ptr [rbp - 24], xmm0
	movsd	xmm0, qword ptr [rbp - 24]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4004000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	jbe	.LBB1_2
# %bb.1:                                # %if.then
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rcx, rsp
	mov	byte ptr [rcx], 100
	mov	byte ptr [rcx + 1], 97
	mov	byte ptr [rcx + 2], 0
	sub	rsp, 32
	call	PrintString
	add	rsp, 32
	jmp	.LBB1_3
.LBB1_2:                                # %if.else
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rcx, rsp
	mov	byte ptr [rcx], 110
	mov	byte ptr [rcx + 1], 101
	mov	byte ptr [rcx + 2], 0
	sub	rsp, 32
	call	PrintString
	add	rsp, 32
.LBB1_3:                                # %if.end
	movsd	xmm0, qword ptr [rbp - 24]      # xmm0 = mem[0],zero
	sub	rsp, 32
	call	PrintFloat
	add	rsp, 32
	mov	qword ptr [rbp - 8], 0
# %bb.4:                                # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @arr2d
arr2d:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.p2align	4, 0x0                          # @arr1d
arr1d:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.addrsig
	.addrsig_sym PrintInteger
	.addrsig_sym PrintFloat
	.addrsig_sym PrintString
	.addrsig_sym func
	.globl	_fltused
