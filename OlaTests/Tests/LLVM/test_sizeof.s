	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_sizeof.ola"
	.def	TestSizeofTypes;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestSizeofTypes
TestSizeofTypes:                        # @TestSizeofTypes
.seh_proc TestSizeofTypes
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestSizeofExpressions;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@40091eb851eb851f         # -- Begin function TestSizeofExpressions
	.section	.rdata,"dr",discard,__real@40091eb851eb851f
	.p2align	3, 0x0
__real@40091eb851eb851f:
	.quad	0x40091eb851eb851f              # double 3.1400000000000001
	.text
	.p2align	4, 0x90
TestSizeofExpressions:                  # @TestSizeofExpressions
.seh_proc TestSizeofExpressions
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 42
	movsd	xmm0, qword ptr [rip + __real@40091eb851eb851f] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	mov	byte ptr [rsp + 39], 1
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestSizeofArrays;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestSizeofArrays
TestSizeofArrays:                       # @TestSizeofArrays
.seh_proc TestSizeofArrays
# %bb.0:                                # %entry
	sub	rsp, 168
	.seh_stackalloc 168
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 168
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
	call	TestSizeofTypes
	call	TestSizeofExpressions
	call	TestSizeofArrays
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestSizeofTypes
	.addrsig_sym TestSizeofExpressions
	.addrsig_sym TestSizeofArrays
	.globl	_fltused
