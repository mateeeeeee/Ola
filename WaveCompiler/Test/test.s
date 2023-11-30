	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.wv"
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
	mov	byte ptr [rsp + 43], 77
	mov	byte ptr [rsp + 44], 97
	mov	byte ptr [rsp + 45], 116
	mov	byte ptr [rsp + 46], 101
	mov	byte ptr [rsp + 47], 0
	lea	rcx, [rsp + 43]
	call	PrintString
	mov	qword ptr [rsp + 32], 24
	mov	rax, qword ptr [rsp + 32]
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
__StringLiteral0:                       # @__StringLiteral0
	.asciz	"Mate"

	.addrsig
	.addrsig_sym PrintString
