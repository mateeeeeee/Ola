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
	mov	qword ptr [rsp + 56], 0
	lea	rax, [rip + int2d]
	mov	qword ptr [rsp + 48], rax
	lea	rax, [rip + int2d]
	add	rax, 8
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rax]
	call	PrintInteger
	mov	rax, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rax + 8]
	call	PrintInteger
	mov	rax, qword ptr [rsp + 40]
	mov	rcx, qword ptr [rax]
	call	PrintInteger
	mov	rax, qword ptr [rsp + 40]
	mov	rcx, qword ptr [rax + 8]
	call	PrintInteger
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 64], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @int2d
int2d:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.addrsig
	.addrsig_sym PrintInteger
	.addrsig_sym int2d
