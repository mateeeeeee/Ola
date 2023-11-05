	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	square;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function square
square:                                 # @square
# %bb.0:                                # %entry
	mov	rax, rcx
	imul	rax, rax
	ret
                                        # -- End function
	.def	add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add
add:                                    # @add
# %bb.0:                                # %entry
	mov	rax, rdx
	add	rax, rcx
	ret
                                        # -- End function
	.def	isEven;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isEven
isEven:                                 # @isEven
# %bb.0:                                # %entry
	mov	al, cl
	test	al, 1
	sete	al
	ret
                                        # -- End function
	.def	fma;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function fma
fma:                                    # @fma
# %bb.0:                                # %entry
	mov	rax, rdx
	imul	rax, rcx
	add	rax, r8
	ret
                                        # -- End function
	.def	isInRange;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isInRange
isInRange:                              # @isInRange
# %bb.0:                                # %entry
	mov	rax, rcx
	sub	rax, rdx
	setge	al
	sub	rcx, r8
	setle	cl
	and	al, cl
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
	mov	ecx, 5
	call	square
	cmp	rax, 25
	sete	cl
	call	Assert
	mov	ecx, 8
	call	isEven
	mov	cl, al
	call	Assert
	mov	rcx, -4
	call	square
	cmp	rax, 16
	sete	cl
	call	Assert
	mov	ecx, 7
	call	isEven
	mov	cl, al
	xor	cl, -1
	call	Assert
	mov	ecx, 5
	mov	edx, 12
	call	add
	cmp	rax, 17
	sete	cl
	call	Assert
	mov	ecx, 2
	mov	edx, 3
	mov	r8d, 4
	call	fma
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	ecx, 5
	mov	edx, 1
	mov	r8d, 10
	call	isInRange
	mov	cl, al
	call	Assert
	mov	ecx, 6
	mov	edx, 2
	mov	r8d, 8
	call	fma
	cmp	rax, 20
	sete	cl
	call	Assert
	mov	ecx, 5
	mov	edx, 6
	mov	r8d, 10
	call	isInRange
	mov	cl, al
	xor	cl, -1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym square
	.addrsig_sym add
	.addrsig_sym isEven
	.addrsig_sym fma
	.addrsig_sym isInRange
