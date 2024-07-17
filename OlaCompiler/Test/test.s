	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	TestIfElse;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElse
TestIfElse:                             # @TestIfElse
# %bb.0:                                # %entry
	mov	eax, 10
	ret
                                        # -- End function
	.def	TestWhile;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestWhile
TestWhile:                              # @TestWhile
.seh_proc TestWhile
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
	jmp	.LBB1_1
.LBB1_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rsp + 16]       # 8-byte Reload
	mov	qword ptr [rsp], rcx            # 8-byte Spill
	xor	eax, eax
                                        # kill: def $rax killed $eax
	cmp	rcx, 10
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jge	.LBB1_5
# %bb.2:                                # %while.body
                                        #   in Loop: Header=BB1_1 Depth=1
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	cmp	rax, 5
	jne	.LBB1_4
# %bb.3:                                # %if.then
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	shl	rax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jmp	.LBB1_5
.LBB1_4:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	add	rax, 1
	mov	qword ptr [rsp + 16], rax       # 8-byte Spill
	jmp	.LBB1_1
.LBB1_5:                                # %exit
	mov	rax, qword ptr [rsp + 8]        # 8-byte Reload
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	TestIfElse
	cmp	rax, 10
	sete	cl
	call	Assert
	call	TestWhile
	cmp	rax, 10
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
	.addrsig_sym TestIfElse
	.addrsig_sym TestWhile
