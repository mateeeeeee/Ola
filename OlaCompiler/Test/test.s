	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	f__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__I
f__I:                                   # @f__I
.seh_proc f__I
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rcx
	mov	qword ptr [rsp], 1
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	f__F;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__F
f__F:                                   # @f__F
.seh_proc f__F
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	movsd	qword ptr [rsp + 8], xmm0
	mov	qword ptr [rsp], -1
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	f__F__F;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__F__F
f__F__F:                                # @f__F__F
.seh_proc f__F__F
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	movsd	qword ptr [rsp + 16], xmm0
	movsd	qword ptr [rsp + 8], xmm1
	mov	qword ptr [rsp], -1
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	f__F__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__F__I
f__F__I:                                # @f__F__I
.seh_proc f__F__I
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	movsd	qword ptr [rsp + 16], xmm0
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	f__I__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__I__I
f__I__I:                                # @f__I__I
.seh_proc f__I__I
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], rcx
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp], 1
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::f__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::f__I"                       # -- Begin function D::f__I
	.p2align	4, 0x90
"D::f__I":                              # @"D::f__I"
.seh_proc "D::f__I"
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rdx
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::f__F";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::f__F"                       # -- Begin function D::f__F
	.p2align	4, 0x90
"D::f__F":                              # @"D::f__F"
.seh_proc "D::f__F"
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	movsd	qword ptr [rsp + 8], xmm1
	mov	rax, qword ptr [rcx + 16]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::f__F__F";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::f__F__F"                    # -- Begin function D::f__F__F
	.p2align	4, 0x90
"D::f__F__F":                           # @"D::f__F__F"
.seh_proc "D::f__F__F"
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	movsd	qword ptr [rsp + 16], xmm1
	movsd	qword ptr [rsp + 8], xmm2
	mov	rax, qword ptr [rcx + 16]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::f__F__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::f__F__I"                    # -- Begin function D::f__F__I
	.p2align	4, 0x90
"D::f__F__I":                           # @"D::f__F__I"
.seh_proc "D::f__F__I"
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	movsd	qword ptr [rsp + 16], xmm1
	mov	qword ptr [rsp + 8], r8
	mov	rax, qword ptr [rcx + 8]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::f__I__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::f__I__I"                    # -- Begin function D::f__I__I
	.p2align	4, 0x90
"D::f__I__I":                           # @"D::f__I__I"
.seh_proc "D::f__I__I"
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], rdx
	mov	qword ptr [rsp + 8], r8
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@3ff0000000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	ecx, 1
	call	f__I
	cmp	rax, 0
	setg	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	call	f__F
	cmp	rax, 0
	setl	cl
	call	Assert
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	movaps	xmm0, xmm1
	call	f__F__F
	cmp	rax, 0
	setl	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	mov	edx, 1
	call	f__F__I
	cmp	rax, 0
	sete	cl
	call	Assert
	mov	edx, 1
	mov	rcx, rdx
	call	f__I__I
	cmp	rax, 0
	setg	cl
	call	Assert
	mov	qword ptr [rsp + 40], 1
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 56], -1
	lea	rcx, [rsp + 40]
	mov	edx, 1
	call	"D::f__I"
	cmp	rax, 0
	setg	cl
	call	Assert
	lea	rcx, [rsp + 40]
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	call	"D::f__F"
	cmp	rax, 0
	setl	cl
	call	Assert
	lea	rcx, [rsp + 40]
	movsd	xmm2, qword ptr [rip + __real@3ff0000000000000] # xmm2 = mem[0],zero
	movaps	xmm1, xmm2
	call	"D::f__F__F"
	cmp	rax, 0
	setl	cl
	call	Assert
	lea	rcx, [rsp + 40]
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	mov	r8d, 1
	call	"D::f__F__I"
	cmp	rax, 0
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	mov	r8d, 1
	mov	rdx, r8
	call	"D::f__I__I"
	cmp	rax, 0
	setg	cl
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
	.addrsig_sym f__I
	.addrsig_sym f__F
	.addrsig_sym f__F__F
	.addrsig_sym f__F__I
	.addrsig_sym f__I__I
	.addrsig_sym "D::f__I"
	.addrsig_sym "D::f__F"
	.addrsig_sym "D::f__F__F"
	.addrsig_sym "D::f__F__I"
	.addrsig_sym "D::f__I__I"
	.globl	_fltused
