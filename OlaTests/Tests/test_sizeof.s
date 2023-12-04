	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_sizeof.ola"
	.def	TestSizeofTypes;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestSizeofTypes
TestSizeofTypes:                        # @TestSizeofTypes
.seh_proc TestSizeofTypes
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestSizeofExpressions;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestSizeofExpressions
TestSizeofExpressions:                  # @TestSizeofExpressions
.seh_proc TestSizeofExpressions
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestSizeofArrays;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestSizeofArrays
TestSizeofArrays:                       # @TestSizeofArrays
.seh_proc TestSizeofArrays
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
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
	call	TestSizeofTypes
	call	TestSizeofExpressions
	call	TestSizeofArrays
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestSizeofTypes
	.addrsig_sym TestSizeofExpressions
	.addrsig_sym TestSizeofArrays
