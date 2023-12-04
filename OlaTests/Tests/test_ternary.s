	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_ternary.ola"
	.def	TestTernaryOperatorIntegers;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorIntegers
TestTernaryOperatorIntegers:            # @TestTernaryOperatorIntegers
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestTernaryOperatorFloats;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorFloats
TestTernaryOperatorFloats:              # @TestTernaryOperatorFloats
# %bb.0:                                # %entry
	mov	cl, 1
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestTernaryOperatorBools;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorBools
TestTernaryOperatorBools:               # @TestTernaryOperatorBools
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
	call	TestTernaryOperatorIntegers
	call	TestTernaryOperatorFloats
	call	TestTernaryOperatorBools
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestTernaryOperatorIntegers
	.addrsig_sym TestTernaryOperatorFloats
	.addrsig_sym TestTernaryOperatorBools
