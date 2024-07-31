	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_logical.ola"
	.def	TestUnaryLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestUnaryLogicalOperators
TestUnaryLogicalOperators:              # @TestUnaryLogicalOperators
.seh_proc TestUnaryLogicalOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	byte ptr [rsp + 39], 1
	mov	byte ptr [rsp + 38], 0
	mov	al, byte ptr [rsp + 39]
	not	al
	and	al, 1
	mov	byte ptr [rsp + 37], al
	mov	al, byte ptr [rsp + 38]
	not	al
	and	al, 1
	mov	byte ptr [rsp + 36], al
	mov	cl, byte ptr [rsp + 37]
	xor	cl, 1
	call	Assert
	mov	cl, byte ptr [rsp + 36]
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestBinaryLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBinaryLogicalOperators
TestBinaryLogicalOperators:             # @TestBinaryLogicalOperators
.seh_proc TestBinaryLogicalOperators
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	byte ptr [rsp + 55], 1
	mov	byte ptr [rsp + 54], 0
	mov	al, byte ptr [rsp + 55]
	mov	byte ptr [rsp + 53], al
	mov	al, byte ptr [rsp + 55]
	mov	cl, byte ptr [rsp + 54]
	and	al, cl
	and	al, 1
	mov	byte ptr [rsp + 52], al
	mov	al, byte ptr [rsp + 54]
	mov	cl, byte ptr [rsp + 55]
	and	al, cl
	and	al, 1
	mov	byte ptr [rsp + 51], al
	mov	al, byte ptr [rsp + 54]
	mov	byte ptr [rsp + 50], al
	mov	cl, byte ptr [rsp + 53]
	call	Assert
	mov	cl, byte ptr [rsp + 52]
	xor	cl, 1
	call	Assert
	mov	cl, byte ptr [rsp + 51]
	xor	cl, 1
	call	Assert
	mov	cl, byte ptr [rsp + 50]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 55]
	mov	byte ptr [rsp + 49], al
	mov	al, byte ptr [rsp + 55]
	mov	cl, byte ptr [rsp + 54]
	or	al, cl
	and	al, 1
	mov	byte ptr [rsp + 48], al
	mov	al, byte ptr [rsp + 54]
	mov	cl, byte ptr [rsp + 55]
	or	al, cl
	and	al, 1
	mov	byte ptr [rsp + 47], al
	mov	al, byte ptr [rsp + 54]
	mov	byte ptr [rsp + 46], al
	mov	cl, byte ptr [rsp + 49]
	call	Assert
	mov	cl, byte ptr [rsp + 48]
	call	Assert
	mov	cl, byte ptr [rsp + 47]
	call	Assert
	mov	cl, byte ptr [rsp + 46]
	xor	cl, 1
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestBinaryLogicalOperatorsImplicitCasts;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBinaryLogicalOperatorsImplicitCasts
TestBinaryLogicalOperatorsImplicitCasts: # @TestBinaryLogicalOperatorsImplicitCasts
.seh_proc TestBinaryLogicalOperatorsImplicitCasts
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 42
	movabs	rax, 4614253070214989087
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	test	rax, rax
	setne	al
	cvttsd2si	ecx, qword ptr [rsp + 40]
                                        # kill: def $cl killed $cl killed $ecx
	and	al, cl
	mov	byte ptr [rsp + 39], al
	mov	cl, byte ptr [rsp + 39]
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	test	rax, rax
	setne	al
	cvttsd2si	ecx, qword ptr [rsp + 40]
                                        # kill: def $cl killed $cl killed $ecx
	or	al, cl
	mov	byte ptr [rsp + 38], al
	mov	cl, byte ptr [rsp + 38]
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	test	rax, rax
	setne	byte ptr [rsp + 37]
	mov	cl, byte ptr [rsp + 37]
	call	Assert
	cvttsd2si	eax, qword ptr [rsp + 40]
                                        # kill: def $al killed $al killed $eax
	mov	byte ptr [rsp + 36], al
	mov	cl, byte ptr [rsp + 36]
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestLogicalOperatorsImplicitCasts;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestLogicalOperatorsImplicitCasts
TestLogicalOperatorsImplicitCasts:      # @TestLogicalOperatorsImplicitCasts
.seh_proc TestLogicalOperatorsImplicitCasts
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 42
	movabs	rax, 4614253070214989087
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	test	rax, rax
	sete	byte ptr [rsp + 39]
	mov	cl, byte ptr [rsp + 39]
	xor	cl, 1
	call	Assert
	cvttsd2si	eax, qword ptr [rsp + 40]
                                        # kill: def $al killed $al killed $eax
	mov	rcx, qword ptr [rsp + 48]
	test	rcx, rcx
	setne	cl
	and	al, cl
	mov	byte ptr [rsp + 38], al
	mov	cl, byte ptr [rsp + 38]
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	test	rax, rax
	setne	al
	cvttsd2si	ecx, qword ptr [rsp + 40]
                                        # kill: def $cl killed $cl killed $ecx
	or	al, cl
	mov	byte ptr [rsp + 37], al
	mov	cl, byte ptr [rsp + 37]
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
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
	call	TestUnaryLogicalOperators
	call	TestBinaryLogicalOperators
	call	TestBinaryLogicalOperatorsImplicitCasts
	call	TestLogicalOperatorsImplicitCasts
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestUnaryLogicalOperators
	.addrsig_sym TestBinaryLogicalOperators
	.addrsig_sym TestBinaryLogicalOperatorsImplicitCasts
	.addrsig_sym TestLogicalOperatorsImplicitCasts
	.globl	_fltused
