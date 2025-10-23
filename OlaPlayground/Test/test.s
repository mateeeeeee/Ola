.intel_syntax noprefix

.section .rodata

__StringLiteral0:
.string "abc.txt"


__StringLiteral1:
.string "w"


.section .bss

SEEK_SET_VALUE:
.zero 8
SEEK_CUR_VALUE:
.zero 8
SEEK_END_VALUE:
.zero 8
MODE_READ:
.zero 8
MODE_WRITE:
.zero 8
MODE_APPEND:
.zero 8
MODE_READ_WRITE:
.zero 8
MODE_WRITE_READ:
.zero 8
MODE_APPEND_READ:
.zero 8
MODE_READ_BINARY:
.zero 8
MODE_WRITE_BINARY:
.zero 8
MODE_APPEND_BINARY:
.zero 8
.section .text

.extern FileOpen

.extern FileClose

.extern FileIsOpen

.extern FileReadInt

.extern FileReadFloat

.extern FileReadChar

.extern FileReadLine

.extern FileRead

.extern FileWriteInt

.extern FileWriteFloat

.extern FileWriteChar

.extern FileWriteString

.extern FileWriteLine

.extern FileWrite

.extern FileTell

.extern FileSeek

.extern FileRewind

.extern FileEOF

.extern FileError

.extern FileClearError

.extern FileFlush

.extern FileExists

.extern FileDelete

.extern FileRename

.extern FileSize

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 56
mov qword ptr [rbp - 8], r14
lea r14, [rip + __StringLiteral1]
mov rdx, r14
lea r14, [rip + __StringLiteral0]
mov rcx, r14
call FileOpen
mov r14, rax
mov qword ptr [rbp - 24], r14
mov qword ptr [rbp - 16], 0
jmp label2
label1:
label2:
mov r14, qword ptr [rbp - 16]
mov rax, r14
mov r14, qword ptr [rbp - 8]
mov rsp, rbp
pop rbp
ret
