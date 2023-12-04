	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_increment.ola"
	.def	TestPreIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestPreIncrementDecrement
TestPreIncrementDecrement:              # @TestPreIncrementDecrement
.seh_proc TestPreIncrementDecrement
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
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestPostIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestPostIncrementDecrement
TestPostIncrementDecrement:             # @TestPostIncrementDecrement
.seh_proc TestPostIncrementDecrement
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
	call	TestPreIncrementDecrement
	call	TestPostIncrementDecrement
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestPreIncrementDecrement
	.addrsig_sym TestPostIncrementDecrement
