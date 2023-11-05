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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	byte ptr [rsp + 48], 0
	mov	byte ptr [rsp + 49], 0
	mov	byte ptr [rsp + 50], 0
	mov	byte ptr [rsp + 51], 0
	mov	byte ptr [rsp + 52], 0
	mov	byte ptr [rsp + 53], 0
	mov	byte ptr [rsp + 54], 0
	mov	byte ptr [rsp + 55], 0
	mov	byte ptr [rsp + 56], 0
	mov	byte ptr [rsp + 57], 0
	mov	byte ptr [rsp + 58], 0
	mov	byte ptr [rsp + 59], 0
	mov	byte ptr [rsp + 60], 0
	mov	byte ptr [rsp + 61], 0
	mov	byte ptr [rsp + 62], 0
	mov	byte ptr [rsp + 63], 0
	lea	rcx, [rsp + 48]
	mov	edx, 16
	call	ReadString
	lea	rax, [rsp + 48]
	mov	qword ptr [rsp + 40], rax
	mov	rcx, qword ptr [rsp + 40]
	call	PrintString
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintString
	.addrsig_sym ReadString
