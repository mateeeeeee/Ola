
.text

_add__F__F:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #24]
add x29, sp, #24
str d29, [x29, #-8]
str d30, [x29, #-16]
str d31, [x29, #-24]
fmov d31, d0
fmov d30, d1
str d31, [x29, #-40]
str d30, [x29, #-48]
ldr d30, [x29, #-40]
ldr d31, [x29, #-48]
fdiv d29, d30, d31
str d29, [x29, #-56]
b label2
label1:
label2:
ldr d29, [x29, #-56]
fmov d0, d29
ldr d29, [x29, #-8]
ldr d30, [x29, #-16]
ldr d31, [x29, #-24]
ldp x29, x30, [sp, #24]
add sp, sp, #80
ret
.globl _main
_main:
label3:
sub sp, sp, #64
stp x29, x30, [sp, #16]
add x29, sp, #16
str x30, [x29, #-8]
str d30, [x29, #-16]
str d31, [x29, #-24]
mov x30, #28
scvtf d31, x30
mov x30, #4
scvtf d30, x30
fmov d1, d30
fmov d0, d31
bl _add__F__F
fmov d31, d0
str d31, [x29, #-48]
ldr d31, [x29, #-48]
fcvtzs x30, d31
str x30, [x29, #-40]
b label5
label4:
label5:
ldr x30, [x29, #-40]
mov x0, x30
ldr x30, [x29, #-8]
ldr d30, [x29, #-16]
ldr d31, [x29, #-24]
ldp x29, x30, [sp, #16]
add sp, sp, #64
ret
