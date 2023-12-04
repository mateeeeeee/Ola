	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_for.ola"
	.def	TestForLoopInt;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopInt
TestForLoopInt:                         # @TestForLoopInt
.seh_proc TestForLoopInt
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB0_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rcx, qword ptr [rsp + 16]
	mov	rax, rcx
	add	rax, rdx
	mov	qword ptr [rsp], rax            # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rsp + 16], rcx
	cmp	rcx, 6
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %for.cond.for.end_crit_edge
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 15
	sete	cl
	add	rsp, 24
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestForLoopBoolCondition;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopBoolCondition
TestForLoopBoolCondition:               # @TestForLoopBoolCondition
.seh_proc TestForLoopBoolCondition
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], 0
.LBB1_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rsp]
	add	rax, 1
	mov	qword ptr [rsp], rax
	cmp	rax, 3
	jl	.LBB1_1
# %bb.2:                                # %for.end
	mov	rax, qword ptr [rsp]
	sub	rax, 3
	sete	cl
	pop	rax
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestForLoopMultipleExpressions;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopMultipleExpressions
TestForLoopMultipleExpressions:         # @TestForLoopMultipleExpressions
.seh_proc TestForLoopMultipleExpressions
# %bb.0:                                # %entry
	sub	rsp, 32
	.seh_stackalloc 32
	.seh_endprologue
	mov	qword ptr [rsp + 24], 1
	mov	qword ptr [rsp + 16], 5
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB2_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	r8, qword ptr [rsp + 8]         # 8-byte Reload
	mov	rdx, qword ptr [rsp + 16]
	mov	rcx, qword ptr [rsp + 24]
	mov	rax, rdx
	add	rax, rcx
	add	rax, r8
	mov	qword ptr [rsp], rax            # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rsp + 24], rcx
	add	rdx, -1
	mov	qword ptr [rsp + 16], rdx
	cmp	rcx, 4
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jl	.LBB2_1
# %bb.2:                                # %for.cond.for.end_crit_edge
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 18
	sete	cl
	add	rsp, 32
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	TestNestedForLoops;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNestedForLoops
TestNestedForLoops:                     # @TestNestedForLoops
.seh_proc TestNestedForLoops
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 40], 0
.LBB3_1:                                # %for.body
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_3 Depth 2
	cmp	qword ptr [rsp + 40], 2
	jl	.LBB3_3
	jmp	.LBB3_4
.LBB3_2:                                # %for.end
	mov	rax, qword ptr [rsp + 48]
	sub	rax, 3
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]
	sub	rax, 2
	sete	cl
	add	rsp, 56
	jmp	Assert                          # TAILCALL
.LBB3_3:                                # %for.body1
                                        #   Parent Loop BB3_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	rax, qword ptr [rsp + 40]
	add	rax, 1
	mov	qword ptr [rsp + 40], rax
	cmp	rax, 2
	jl	.LBB3_3
.LBB3_4:                                # %for.end4
                                        #   in Loop: Header=BB3_1 Depth=1
	mov	rax, qword ptr [rsp + 48]
	add	rax, 1
	mov	qword ptr [rsp + 48], rax
	cmp	rax, 3
	jl	.LBB3_1
	jmp	.LBB3_2
	.seh_endproc
                                        # -- End function
	.def	TestForLoopWithBreak;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopWithBreak
TestForLoopWithBreak:                   # @TestForLoopWithBreak
.seh_proc TestForLoopWithBreak
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 24], rax       # 8-byte Spill
.LBB4_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rsp + 24]       # 8-byte Reload
	mov	rcx, qword ptr [rsp + 32]
	mov	qword ptr [rsp], rcx            # 8-byte Spill
	mov	rax, rcx
	add	rax, rdx
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	cmp	rcx, 3
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
	jne	.LBB4_3
.LBB4_2:                                # %for.end
	mov	rax, qword ptr [rsp + 16]       # 8-byte Reload
	sub	rax, 6
	sete	cl
	add	rsp, 40
	jmp	Assert                          # TAILCALL
.LBB4_3:                                # %if.end
                                        #   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rcx, qword ptr [rsp]            # 8-byte Reload
	add	rcx, 1
	mov	qword ptr [rsp + 32], rcx
	cmp	rcx, 6
	mov	rcx, rax
	mov	qword ptr [rsp + 24], rcx       # 8-byte Spill
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
	jl	.LBB4_1
	jmp	.LBB4_2
	.seh_endproc
                                        # -- End function
	.def	TestForLoopWithContinue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopWithContinue
TestForLoopWithContinue:                # @TestForLoopWithContinue
.seh_proc TestForLoopWithContinue
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB5_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rdx, qword ptr [rsp + 16]
	mov	rax, rdx
	add	rax, rcx
	cmp	rdx, 3
	cmove	rax, rcx
	mov	qword ptr [rsp], rax            # 8-byte Spill
	mov	rcx, qword ptr [rsp + 16]
	add	rcx, 1
	mov	qword ptr [rsp + 16], rcx
	cmp	rcx, 6
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jl	.LBB5_1
# %bb.2:                                # %for.end
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 12
	sete	cl
	add	rsp, 24
	jmp	Assert                          # TAILCALL
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
	call	TestForLoopInt
	call	TestForLoopBoolCondition
	call	TestForLoopMultipleExpressions
	call	TestNestedForLoops
	call	TestForLoopWithBreak
	call	TestForLoopWithContinue
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestForLoopInt
	.addrsig_sym TestForLoopBoolCondition
	.addrsig_sym TestForLoopMultipleExpressions
	.addrsig_sym TestNestedForLoops
	.addrsig_sym TestForLoopWithBreak
	.addrsig_sym TestForLoopWithContinue
