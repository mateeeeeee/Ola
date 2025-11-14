
.text

_add__I__I:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #24]
add x29, sp, #24
str x27, [x29, #-8]
str x28, [x29, #-16]
str x30, [x29, #-24]
mov x30, x0
mov x28, x1
str x30, [x29, #-40]
str x28, [x29, #-48]
ldr x28, [x29, #-40]
ldr x30, [x29, #-48]
add x27, x28, x30
str x27, [x29, #-56]
b label2
label1:
label2:
ldr x27, [x29, #-56]
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr x30, [x29, #-24]
ldp x29, x30, [sp, #24]
add sp, sp, #80
ret
.globl _main
_main:
label3:
sub sp, sp, #48
stp x29, x30, [sp, #8]
add x29, sp, #8
str x30, [x29, #-8]
mov x1, #3
mov x0, #2
bl _add__I__I
mov x30, x0
str x30, [x29, #-24]
b label5
label4:
label5:
ldr x30, [x29, #-24]
mov x0, x30
ldr x30, [x29, #-8]
ldp x29, x30, [sp, #8]
add sp, sp, #48
ret
