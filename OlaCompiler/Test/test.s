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
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	lea	rcx, [rsp + 40]
	call	"S::Test"
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
	.addrsig_sym PrintString
	.addrsig_sym "S::Test"
	.addrsig_sym __StringLiteral0
