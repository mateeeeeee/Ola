	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_implicitcasts.ola"
	.def	TestImplicitCastAssignInit;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestImplicitCastAssignInit
TestImplicitCastAssignInit:             # @TestImplicitCastAssignInit
.seh_proc TestImplicitCastAssignInit
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
                                        # implicit-def: $cl
	call	Assert
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	Assert
	mov	cl, 1
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestImplicitCastParamBool;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestImplicitCastParamBool
TestImplicitCastParamBool:              # @TestImplicitCastParamBool
# %bb.0:                                # %entry
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestImplicitCastParamInt;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestImplicitCastParamInt
TestImplicitCastParamInt:               # @TestImplicitCastParamInt
# %bb.0:                                # %entry
	sub	rcx, 1
	sete	cl
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestImplicitCastParamFloat;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@3ff0000000000000         # -- Begin function TestImplicitCastParamFloat
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.text
	.p2align	4, 0x90
TestImplicitCastParamFloat:             # @TestImplicitCastParamFloat
# %bb.0:                                # %entry
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	cmpeqsd	xmm0, xmm1
	movq	rax, xmm0
                                        # kill: def $eax killed $eax killed $rax
	and	eax, 1
	mov	cl, al
	jmp	Assert                          # TAILCALL
                                        # -- End function
	.def	TestImplicitCastParam;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestImplicitCastParam
TestImplicitCastParam:                  # @TestImplicitCastParam
.seh_proc TestImplicitCastParam
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	cl, 1
	mov	byte ptr [rsp + 39], cl         # 1-byte Spill
	call	TestImplicitCastParamBool
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	TestImplicitCastParamBool
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	TestImplicitCastParamBool
	mov	cl, byte ptr [rsp + 39]         # 1-byte Reload
	call	TestImplicitCastParamBool
	mov	ecx, 1
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	call	TestImplicitCastParamInt
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	TestImplicitCastParamInt
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	TestImplicitCastParamInt
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	TestImplicitCastParamInt
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0      # 8-byte Spill
	call	TestImplicitCastParamFloat
	movsd	xmm0, qword ptr [rsp + 48]      # 8-byte Reload
                                        # xmm0 = mem[0],zero
	call	TestImplicitCastParamFloat
	movsd	xmm0, qword ptr [rsp + 48]      # 8-byte Reload
                                        # xmm0 = mem[0],zero
	call	TestImplicitCastParamFloat
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	add	rsp, 56
	jmp	TestImplicitCastParamFloat      # TAILCALL
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
	call	TestImplicitCastAssignInit
	call	TestImplicitCastParam
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestImplicitCastAssignInit
	.addrsig_sym TestImplicitCastParamBool
	.addrsig_sym TestImplicitCastParamInt
	.addrsig_sym TestImplicitCastParamFloat
	.addrsig_sym TestImplicitCastParam
	.globl	_fltused
