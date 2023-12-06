	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"S::Test";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Test"                       # -- Begin function S::Test
	.p2align	4, 0x90
"S::Test":                              # @"S::Test"
.seh_proc "S::Test"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	lea	rcx, [rip + __StringLiteral0]
	call	PrintString
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@3feccccccccccccd         # -- Begin function main
	.section	.rdata,"dr",discard,__real@3feccccccccccccd
	.p2align	3, 0x0
__real@3feccccccccccccd:
	.quad	0x3feccccccccccccd              # double 0.90000000000000002
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@3feccccccccccccd] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	call	PrintFloat
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
__StringLiteral0:                       # @__StringLiteral0
	.asciz	"Alo"

	.addrsig
	.addrsig_sym PrintFloat
	.addrsig_sym PrintString
	.addrsig_sym __StringLiteral0
	.globl	_fltused
