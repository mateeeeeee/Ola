	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add
add:                                    # @add
.seh_proc add
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	add	rcx, rdx
	mov	qword ptr [rsp], rcx
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	ecx, 3
	mov	edx, 1
	call	add
	mov	qword ptr [rsp + 40], rax
	mov	rcx, qword ptr [rsp + 40]
	call	PrintInteger
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInteger
	.addrsig_sym add
