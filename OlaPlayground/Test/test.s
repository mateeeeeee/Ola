	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	min__I__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function min__I__I
min__I__I:                              # @min__I__I
.seh_proc min__I__I
# %bb.0:                                # %entry
	sub	rsp, 32
	.seh_stackalloc 32
	.seh_endprologue
	mov	qword ptr [rsp + 24], rcx
	mov	qword ptr [rsp + 16], rdx
	mov	rax, qword ptr [rsp + 24]
	cmp	rax, qword ptr [rsp + 16]
	jge	.LBB0_2
# %bb.1:                                # %if.then
	mov	rax, qword ptr [rsp + 24]
	mov	qword ptr [rsp], rax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	mov	rax, qword ptr [rsp + 16]
	mov	qword ptr [rsp], rax
.LBB0_3:                                # %if.end
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
# %bb.4:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 32
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 3
	mov	edx, 4
	call	min__I__I
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym min__I__I
