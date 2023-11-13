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
	.globl	__real@408f400000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@408f400000000000
	.p2align	3, 0x0
__real@408f400000000000:
	.quad	0x408f400000000000              # double 1000
	.globl	__real@408f380000000000
	.section	.rdata,"dr",discard,__real@408f380000000000
	.p2align	3, 0x0
__real@408f380000000000:
	.quad	0x408f380000000000              # double 999
	.globl	__real@4023cccccccccccc
	.section	.rdata,"dr",discard,__real@4023cccccccccccc
	.p2align	3, 0x0
__real@4023cccccccccccc:
	.quad	0x4023cccccccccccc              # double 9.8999999999999985
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@4023cccccccccccc] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 72], xmm0
	movsd	xmm0, qword ptr [rip + globalFloat] # xmm0 = mem[0],zero
	ucomisd	xmm0, qword ptr [rsp + 72]
	seta	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + globalFloat] # xmm0 = mem[0],zero
	subsd	xmm0, qword ptr [rsp + 72]
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	mulsd	xmm0, qword ptr [rsp + 64]
	mulsd	xmm0, qword ptr [rsp + 64]
	movsd	qword ptr [rsp + 56], xmm0
	movsd	xmm0, qword ptr [rip + __real@408f380000000000] # xmm0 = mem[0],zero
	mulsd	xmm0, qword ptr [rsp + 56]
	cvttsd2si	rax, xmm0
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 0
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@408f400000000000] # xmm0 = mem[0],zero
	mulsd	xmm0, qword ptr [rsp + 56]
	cvttsd2si	rax, xmm0
	mov	qword ptr [rsp + 40], rax
	cmp	qword ptr [rsp + 40], 1
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 80], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 80]
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @globalFloat
globalFloat:
	.quad	0x4024000000000000              # double 10

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym globalFloat
	.globl	_fltused
