.intel_syntax noprefix

.text

.globl main

main:
label0:
push rbp
mov rbp, rsp
sub rsp, 17
mov qword ptr [rbp-16], 0
mov r15, qword ptr [rbp-16]
cmp r15, 0
setg r15b
mov byte ptr [rbp-17], r15b
mov r15b, byte ptr [rbp-17]
cmp r15b, 0
sete r15b
test r15b, r15b
jne label1
jmp label3
label1:
mov qword ptr [rbp-8], 10
jmp label7
label2:
jmp label7
label3:
mov qword ptr [rbp-8], 15
jmp label7
label4:
jmp label7
label5:
mov qword ptr [rbp-8], 5
jmp label7
label6:
jmp label7
label7:
mov r15, qword ptr [rbp-8]
mov rax, r15
mov rsp, rbp
pop rbp
ret

