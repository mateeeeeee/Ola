	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
# %bb.0:                                # %entry
	mov	rax, qword ptr [rip + GlobalInt]
	ret
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @GlobalInt
GlobalInt:
	.quad	7                               # 0x7

	.addrsig
	.addrsig_sym GlobalInt
