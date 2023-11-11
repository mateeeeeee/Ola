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
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	rax, qword ptr [rip + arr2d+8]
	mov	qword ptr [rsp], rax
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @arr2d
arr2d:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.p2align	4, 0x0                          # @arr1d
arr1d:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	4                               # 0x4

	.addrsig
	.addrsig_sym arr2d
