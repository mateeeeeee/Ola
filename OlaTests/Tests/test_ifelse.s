	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_ifelse.ola"
	.def	TestIfElseBasic;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseBasic
TestIfElseBasic:                        # @TestIfElseBasic
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestIfElseMultipleConditions;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseMultipleConditions
TestIfElseMultipleConditions:           # @TestIfElseMultipleConditions
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestNestedIfElse;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNestedIfElse
TestNestedIfElse:                       # @TestNestedIfElse
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestComplexNestedIfElse;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestComplexNestedIfElse
TestComplexNestedIfElse:                # @TestComplexNestedIfElse
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestIfElseLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseLogicalOperators
TestIfElseLogicalOperators:             # @TestIfElseLogicalOperators
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	TestIfElseBasic
	call	TestIfElseMultipleConditions
	call	TestNestedIfElse
	call	TestComplexNestedIfElse
	call	TestIfElseLogicalOperators
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIfElseBasic
	.addrsig_sym TestIfElseMultipleConditions
	.addrsig_sym TestNestedIfElse
	.addrsig_sym TestComplexNestedIfElse
	.addrsig_sym TestIfElseLogicalOperators
