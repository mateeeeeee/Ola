	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
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
	mov	byte ptr [rsp + 32], 0
	mov	byte ptr [rsp + 33], 0
	mov	byte ptr [rsp + 34], 0
	mov	byte ptr [rsp + 35], 0
	mov	byte ptr [rsp + 36], 0
	mov	byte ptr [rsp + 37], 0
	mov	byte ptr [rsp + 38], 0
	mov	byte ptr [rsp + 39], 0
	mov	byte ptr [rsp + 40], 0
	mov	byte ptr [rsp + 41], 0
	mov	byte ptr [rsp + 42], 0
	mov	byte ptr [rsp + 43], 0
	mov	byte ptr [rsp + 44], 0
	mov	byte ptr [rsp + 45], 0
	mov	byte ptr [rsp + 46], 0
	mov	byte ptr [rsp + 47], 0
	lea	rcx, [rsp + 32]
	mov	edx, 16
	call	ReadString
	lea	rcx, [rsp + 32]
	call	PrintString
	mov	byte ptr [rsp + 32], 76
	lea	rcx, [rsp + 32]
	call	PrintString
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintString
	.addrsig_sym ReadString
