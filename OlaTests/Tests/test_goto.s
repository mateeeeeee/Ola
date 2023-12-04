	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_goto.ola"
	.def	TestGotoNestedLoops;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoNestedLoops
TestGotoNestedLoops:                    # @TestGotoNestedLoops
.seh_proc TestGotoNestedLoops
# %bb.0:                                # %entry
	sub	rsp, 32
	.seh_stackalloc 32
	.seh_endprologue
	mov	qword ptr [rsp + 24], 0
	jmp	.LBB0_2
.LBB0_1:                                # %label.Found
	mov	rcx, qword ptr [rsp + 24]
	mov	rax, qword ptr [rsp + 16]
	imul	rax, rcx
	sub	rax, 5
	sete	cl
	add	rsp, 32
	jmp	Assert                          # TAILCALL
.LBB0_2:                                # %for.body
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	mov	qword ptr [rsp + 16], 0
	mov	rax, qword ptr [rsp + 24]
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB0_3:                                # %for.body1
                                        #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	rcx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rax, qword ptr [rsp + 16]
	mov	qword ptr [rsp], rax            # 8-byte Spill
	imul	rax, rcx
	cmp	rax, 5
	je	.LBB0_1
	jmp	.LBB0_5
.LBB0_4:                                # %for.end4
                                        #   in Loop: Header=BB0_2 Depth=1
	mov	rax, qword ptr [rsp + 24]
	add	rax, 1
	mov	qword ptr [rsp + 24], rax
	cmp	rax, 10
	jl	.LBB0_2
	jmp	.LBB0_1
.LBB0_5:                                # %if.end
                                        #   in Loop: Header=BB0_3 Depth=2
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	add	rax, 1
	mov	qword ptr [rsp + 16], rax
	cmp	rax, 10
	jl	.LBB0_3
	jmp	.LBB0_4
	.seh_endproc
                                        # -- End function
	.def	TestGotoErrorHandling;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoErrorHandling
TestGotoErrorHandling:                  # @TestGotoErrorHandling
.seh_proc TestGotoErrorHandling
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	rax, -1
	mov	qword ptr [rsp], rax
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	TestGotoEndOfFunction;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoEndOfFunction
TestGotoEndOfFunction:                  # @TestGotoEndOfFunction
.seh_proc TestGotoEndOfFunction
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp], 0
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
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
	call	TestGotoNestedLoops
	call	TestGotoErrorHandling
	cmp	rax, -1
	sete	cl
	call	Assert
	call	TestGotoEndOfFunction
	cmp	rax, 0
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestGotoNestedLoops
	.addrsig_sym TestGotoErrorHandling
	.addrsig_sym TestGotoEndOfFunction
