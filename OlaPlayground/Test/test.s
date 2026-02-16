
.text

_factorial_helper__I__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
mov x26, x28
mov x28, x27
b label1
label1:
cmp x26, #1
cset w27, le
tst w27, w27
b.ne label2
b label3
label2:
b label4
label3:
sub x27, x26, #1
mul x25, x26, x28
mov x26, x27
mov x28, x25
b label1
label4:
mov x0, x28
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_factorial__I:
label5:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x28, x0
mov x1, #1
mov x0, #5
bl _factorial_helper__I__I
mov x28, x0
b label6
label6:
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _main
_main:
label7:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x0, #5
bl _factorial__I
mov x28, x0
b label8
label8:
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
