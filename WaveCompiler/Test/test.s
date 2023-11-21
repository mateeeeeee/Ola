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
	.globl	__real@3ff0000000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.globl	__real@4002666666666666
	.section	.rdata,"dr",discard,__real@4002666666666666
	.p2align	3, 0x0
__real@4002666666666666:
	.quad	0x4002666666666666              # double 2.2999999999999998
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@4002666666666666] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp], xmm0
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	addsd	xmm0, qword ptr [rsp]
	movsd	qword ptr [rsp], xmm0
	cvttsd2si	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.globl	_fltused
