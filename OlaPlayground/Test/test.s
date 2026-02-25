	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	S$Init__I__I;
	.scl	2;
	.type	32;
	.endef
	.globl	S$Init__I__I                    # -- Begin function S$Init__I__I
	.p2align	4, 0x90
S$Init__I__I:                           # @"S$Init__I__I"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx + 8], r8
	ret
                                        # -- End function
	.def	S$SetX__I;
	.scl	2;
	.type	32;
	.endef
	.globl	S$SetX__I                       # -- Begin function S$SetX__I
	.p2align	4, 0x90
S$SetX__I:                              # @"S$SetX__I"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
	ret
                                        # -- End function
	.def	S$SetY__I;
	.scl	2;
	.type	32;
	.endef
	.globl	S$SetY__I                       # -- Begin function S$SetY__I
	.p2align	4, 0x90
S$SetY__I:                              # @"S$SetY__I"
# %bb.0:                                # %entry
	mov	qword ptr [rcx + 8], rdx
	ret
                                        # -- End function
	.def	S$GetX;
	.scl	2;
	.type	32;
	.endef
	.globl	S$GetX                          # -- Begin function S$GetX
	.p2align	4, 0x90
S$GetX:                                 # @"S$GetX"
# %bb.0:                                # %entry
	mov	rax, rcx
	ret
                                        # -- End function
	.def	S$GetY;
	.scl	2;
	.type	32;
	.endef
	.globl	S$GetY                          # -- Begin function S$GetY
	.p2align	4, 0x90
S$GetY:                                 # @"S$GetY"
# %bb.0:                                # %entry
	mov	rax, rcx
	add	rax, 8
	ret
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
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	ecx, ecx
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
