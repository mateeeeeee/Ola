	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_relational.ola"
	.def	TestLessThanOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestLessThanOperators
TestLessThanOperators:                  # @TestLessThanOperators
.seh_proc TestLessThanOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestLessThanOrEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestLessThanOrEqualOperators
TestLessThanOrEqualOperators:           # @TestLessThanOrEqualOperators
.seh_proc TestLessThanOrEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestGreaterThanOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGreaterThanOperators
TestGreaterThanOperators:               # @TestGreaterThanOperators
.seh_proc TestGreaterThanOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestGreaterThanOrEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGreaterThanOrEqualOperators
TestGreaterThanOrEqualOperators:        # @TestGreaterThanOrEqualOperators
.seh_proc TestGreaterThanOrEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestEqualOperators
TestEqualOperators:                     # @TestEqualOperators
.seh_proc TestEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestNotEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNotEqualOperators
TestNotEqualOperators:                  # @TestNotEqualOperators
.seh_proc TestNotEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	TestLessThanOperators
	call	TestLessThanOrEqualOperators
	call	TestGreaterThanOperators
	call	TestGreaterThanOrEqualOperators
	call	TestEqualOperators
	call	TestNotEqualOperators
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestLessThanOperators
	.addrsig_sym TestLessThanOrEqualOperators
	.addrsig_sym TestGreaterThanOperators
	.addrsig_sym TestGreaterThanOrEqualOperators
	.addrsig_sym TestEqualOperators
	.addrsig_sym TestNotEqualOperators
