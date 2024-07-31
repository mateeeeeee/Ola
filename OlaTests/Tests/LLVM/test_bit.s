	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_bit.ola"
	.def	TestIntBitwiseAnd;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseAnd
TestIntBitwiseAnd:                      # @TestIntBitwiseAnd
.seh_proc TestIntBitwiseAnd
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 40], 3
	mov	rax, qword ptr [rsp + 48]
	and	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 1
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	and	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 1
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIntBitwiseOr;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseOr
TestIntBitwiseOr:                       # @TestIntBitwiseOr
.seh_proc TestIntBitwiseOr
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 40], 3
	mov	rax, qword ptr [rsp + 48]
	or	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 7
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	or	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 7
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIntBitwiseXor;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseXor
TestIntBitwiseXor:                      # @TestIntBitwiseXor
.seh_proc TestIntBitwiseXor
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 40], 3
	mov	rax, qword ptr [rsp + 48]
	xor	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 6
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	xor	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 6
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIntBitwiseNot;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntBitwiseNot
TestIntBitwiseNot:                      # @TestIntBitwiseNot
.seh_proc TestIntBitwiseNot
# %bb.0:                                # %entry
	sub	rsp, 120
	.seh_stackalloc 120
	.seh_endprologue
	mov	qword ptr [rsp + 112], 5
	mov	rax, qword ptr [rsp + 112]
	xor	rax, -1
	mov	qword ptr [rsp + 104], rax
	cmp	qword ptr [rsp + 104], -6
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 96], -1
	mov	rax, qword ptr [rsp + 96]
	xor	rax, -1
	mov	qword ptr [rsp + 88], rax
	cmp	qword ptr [rsp + 88], 0
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 80], 0
	mov	rax, qword ptr [rsp + 80]
	xor	rax, -1
	mov	qword ptr [rsp + 72], rax
	cmp	qword ptr [rsp + 72], -1
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 64], 255
	mov	rax, qword ptr [rsp + 64]
	xor	rax, -1
	mov	qword ptr [rsp + 56], rax
	cmp	qword ptr [rsp + 56], -256
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 65535
	mov	rax, qword ptr [rsp + 48]
	xor	rax, -1
	mov	qword ptr [rsp + 40], rax
	cmp	qword ptr [rsp + 40], -65536
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 120
	ret
	.seh_endproc
                                        # -- End function
	.def	TestBoolBitOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBoolBitOperators
TestBoolBitOperators:                   # @TestBoolBitOperators
.seh_proc TestBoolBitOperators
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	byte ptr [rsp + 39], 1
	mov	byte ptr [rsp + 38], 0
	movzx	eax, byte ptr [rsp + 39]
	movzx	ecx, byte ptr [rsp + 38]
	and	eax, ecx
	and	eax, 1
                                        # kill: def $al killed $al killed $eax
	mov	byte ptr [rsp + 37], al
	mov	cl, byte ptr [rsp + 37]
	xor	cl, 1
	call	Assert
	movzx	eax, byte ptr [rsp + 39]
	movzx	ecx, byte ptr [rsp + 38]
	and	eax, ecx
	and	eax, 1
                                        # kill: def $al killed $al killed $eax
	mov	byte ptr [rsp + 39], al
	mov	cl, byte ptr [rsp + 39]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 39]
	mov	cl, byte ptr [rsp + 38]
	or	al, cl
	and	al, 1
	mov	byte ptr [rsp + 36], al
	mov	cl, byte ptr [rsp + 36]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 39]
	mov	cl, byte ptr [rsp + 38]
	or	al, cl
	and	al, 1
	mov	byte ptr [rsp + 39], al
	mov	cl, byte ptr [rsp + 39]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 39]
	mov	cl, byte ptr [rsp + 38]
	xor	al, cl
	and	al, 1
	mov	byte ptr [rsp + 35], al
	mov	cl, byte ptr [rsp + 35]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 39]
	mov	cl, byte ptr [rsp + 38]
	xor	al, cl
	and	al, 1
	mov	byte ptr [rsp + 39], al
	mov	cl, byte ptr [rsp + 39]
	xor	cl, 1
	call	Assert
	mov	al, byte ptr [rsp + 39]
	not	al
	and	al, 1
	mov	byte ptr [rsp + 34], al
	mov	cl, byte ptr [rsp + 34]
	call	Assert
	mov	al, byte ptr [rsp + 38]
	not	al
	and	al, 1
	mov	byte ptr [rsp + 33], al
	mov	cl, byte ptr [rsp + 33]
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
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
	call	TestIntBitwiseAnd
	call	TestIntBitwiseOr
	call	TestIntBitwiseXor
	call	TestIntBitwiseNot
	call	TestBoolBitOperators
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIntBitwiseAnd
	.addrsig_sym TestIntBitwiseOr
	.addrsig_sym TestIntBitwiseXor
	.addrsig_sym TestIntBitwiseNot
	.addrsig_sym TestBoolBitOperators
