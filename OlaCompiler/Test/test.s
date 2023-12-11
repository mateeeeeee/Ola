	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	modifyArray;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function modifyArray
modifyArray:                            # @modifyArray
.seh_proc modifyArray
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rax], 100
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	modifyArray2;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function modifyArray2
modifyArray2:                           # @modifyArray2
.seh_proc modifyArray2
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp + 16], r8
	mov	qword ptr [rsp], 100
# %bb.1:                                # %exit
	add	rsp, 24
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
	mov	qword ptr [rsp + 40], 1
	mov	qword ptr [rsp + 48], 2
	mov	qword ptr [rsp + 56], 3
	mov	r8, qword ptr [rsp + 56]
	mov	rcx, qword ptr [rsp + 40]
	mov	rdx, qword ptr [rsp + 48]
	call	modifyArray2
	cmp	qword ptr [rsp + 40], 1
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	call	modifyArray
	cmp	qword ptr [rsp + 40], 100
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 64], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym modifyArray
	.addrsig_sym modifyArray2
