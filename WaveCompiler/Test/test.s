	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	PassStringLiteral;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassStringLiteral
PassStringLiteral:                      # @PassStringLiteral
.seh_proc PassStringLiteral
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	cmp	byte ptr [rcx], 76
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	PassStringVariable;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassStringVariable
PassStringVariable:                     # @PassStringVariable
.seh_proc PassStringVariable
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	cmp	byte ptr [rcx], 86
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	byte ptr [rsp + 58], 108
	mov	byte ptr [rsp + 59], 111
	mov	byte ptr [rsp + 60], 99
	mov	byte ptr [rsp + 61], 97
	mov	byte ptr [rsp + 62], 108
	mov	byte ptr [rsp + 63], 0
	mov	ecx, 1
	call	Assert
	lea	rax, [rsp + 58]
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 48]
	cmp	byte ptr [rax], 108
	sete	cl
	call	Assert
	lea	rcx, [rip + __StringLiteral1]
	call	PassStringLiteral
	lea	rcx, [rip + __StringLiteral2]
	call	PassStringVariable
	mov	byte ptr [rsp + 42], 49
	mov	byte ptr [rsp + 43], 50
	mov	byte ptr [rsp + 44], 51
	mov	byte ptr [rsp + 45], 52
	mov	byte ptr [rsp + 46], 53
	mov	byte ptr [rsp + 47], 0
	lea	rcx, [rsp + 42]
	call	StringToInteger
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 12345
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 64], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
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
	.addrsig_sym StringToInteger
	.addrsig_sym PassStringLiteral
	.addrsig_sym PassStringVariable
	.addrsig_sym __StringLiteral1
	.addrsig_sym __StringLiteral2
