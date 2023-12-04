	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_bit.ola"
	.def	TestIntBitwiseAnd;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseAnd
TestIntBitwiseAnd:                      # @TestIntBitwiseAnd
.seh_proc TestIntBitwiseAnd
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
	.def	TestIntBitwiseOr;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseOr
TestIntBitwiseOr:                       # @TestIntBitwiseOr
.seh_proc TestIntBitwiseOr
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
	.def	TestIntBitwiseXor;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseXor
TestIntBitwiseXor:                      # @TestIntBitwiseXor
.seh_proc TestIntBitwiseXor
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
	.def	TestIntBitwiseNot;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseNot
TestIntBitwiseNot:                      # @TestIntBitwiseNot
.seh_proc TestIntBitwiseNot
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
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestBoolBitOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBoolBitOperators
TestBoolBitOperators:                   # @TestBoolBitOperators
.seh_proc TestBoolBitOperators
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
	call	TestIntBitwiseAnd
	call	TestIntBitwiseOr
	call	TestIntBitwiseXor
	call	TestIntBitwiseNot
	call	TestBoolBitOperators
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIntBitwiseAnd
	.addrsig_sym TestIntBitwiseOr
	.addrsig_sym TestIntBitwiseXor
	.addrsig_sym TestIntBitwiseNot
	.addrsig_sym TestBoolBitOperators
