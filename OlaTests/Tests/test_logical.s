	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_logical.ola"
	.def	TestUnaryLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestUnaryLogicalOperators
TestUnaryLogicalOperators:              # @TestUnaryLogicalOperators
.seh_proc TestUnaryLogicalOperators
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
	.def	TestBinaryLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBinaryLogicalOperators
TestBinaryLogicalOperators:             # @TestBinaryLogicalOperators
.seh_proc TestBinaryLogicalOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestBinaryLogicalOperatorsImplicitCasts;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBinaryLogicalOperatorsImplicitCasts
TestBinaryLogicalOperatorsImplicitCasts: # @TestBinaryLogicalOperatorsImplicitCasts
.seh_proc TestBinaryLogicalOperatorsImplicitCasts
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
                                        # implicit-def: $cl
	call	Assert
                                        # implicit-def: $cl
	call	Assert
	mov	cl, 1
	call	Assert
                                        # implicit-def: $cl
	nop
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestLogicalOperatorsImplicitCasts;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestLogicalOperatorsImplicitCasts
TestLogicalOperatorsImplicitCasts:      # @TestLogicalOperatorsImplicitCasts
.seh_proc TestLogicalOperatorsImplicitCasts
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	call	Assert
                                        # implicit-def: $cl
	call	Assert
                                        # implicit-def: $cl
	nop
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
	call	TestUnaryLogicalOperators
	call	TestBinaryLogicalOperators
	call	TestBinaryLogicalOperatorsImplicitCasts
	call	TestLogicalOperatorsImplicitCasts
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestUnaryLogicalOperators
	.addrsig_sym TestBinaryLogicalOperators
	.addrsig_sym TestBinaryLogicalOperatorsImplicitCasts
	.addrsig_sym TestLogicalOperatorsImplicitCasts
