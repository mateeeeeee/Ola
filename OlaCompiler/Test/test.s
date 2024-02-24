.intel_syntax noprefix

.section .rodata

.section .bss

.section .data

.section .text
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 17
and rsp, -16
mov qword ptr [rbp - 0], 17
mov rax, qword ptr [rbp - 0]
jmp main_End
main_End:
mov rsp, rbp
pop rbp
ret

