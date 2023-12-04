	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_string.ola"
	.def	PassStringLiteral;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassStringLiteral
PassStringLiteral:                      # @PassStringLiteral
# %bb.0:                                # %entry
	mov	al, byte ptr [rcx]
	sub	al, 76
	sete	cl
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	PassStringVariable;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassStringVariable
PassStringVariable:                     # @PassStringVariable
# %bb.0:                                # %entry
	mov	al, byte ptr [rcx]
	sub	al, 86
	sete	cl
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	byte ptr [rsp + 50], 108
	mov	byte ptr [rsp + 51], 111
	mov	byte ptr [rsp + 52], 99
	mov	byte ptr [rsp + 53], 97
	mov	byte ptr [rsp + 54], 108
	mov	byte ptr [rsp + 55], 0
	mov	ecx, 1
	call	Assert
	cmp	byte ptr [rsp + 50], 108
	sete	cl
	call	Assert
	lea	rcx, [rip + __StringLiteral1]
	call	PassStringLiteral
	lea	rcx, [rip + __StringLiteral2]
	call	PassStringVariable
	mov	byte ptr [rsp + 44], 49
	mov	byte ptr [rsp + 45], 50
	mov	byte ptr [rsp + 46], 51
	mov	byte ptr [rsp + 47], 52
	mov	byte ptr [rsp + 48], 53
	mov	byte ptr [rsp + 49], 0
	lea	rcx, [rsp + 44]
	call	StringToInt
	cmp	rax, 12345
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.data
globalString:                           # @globalString
	.asciz	"global"

	.section	.rdata,"dr"
__StringLiteral0:                       # @__StringLiteral0
	.asciz	"local"

__StringLiteral1:                       # @__StringLiteral1
	.asciz	"Literal"

__StringLiteral2:                       # @__StringLiteral2
	.asciz	"Variable"

__StringLiteral3:                       # @__StringLiteral3
	.asciz	"12345"

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym StringToInt
	.addrsig_sym PassStringLiteral
	.addrsig_sym PassStringVariable
	.addrsig_sym __StringLiteral1
	.addrsig_sym __StringLiteral2
