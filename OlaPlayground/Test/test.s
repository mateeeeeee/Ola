
.text

.extern _Assert
.extern _AssertMsg
_TestEmptyDoWhileLoop:
label0:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
b label1
label1:
mov w0, #1
bl _Assert
b label2
label2:
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
_getI__I:
label3:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x28, x0
b label5
label4:
label5:
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestSimpleLoopUnroll:
label6:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x22, [x29, #-8]
str x23, [x29, #-16]
str x24, [x29, #-24]
str x25, [x29, #-32]
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
mov x0, #0
bl _getI__I
mov x28, x0
mov x0, #1
bl _getI__I
mov x27, x0
mov x0, #2
bl _getI__I
mov x26, x0
mov x0, #3
bl _getI__I
mov x25, x0
mov x0, #4
bl _getI__I
mov x24, x0
mov x23, #0
add x22, x23, x28
add x23, x22, x27
add x22, x23, x26
add x23, x22, x25
add x22, x23, x24
b label7
label7:
cmp x22, #10
cset w22, eq
mov w0, w22
bl _Assert
b label8
label8:
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label9:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestEmptyDoWhileLoop
bl _TestSimpleLoopUnroll
b label11
label10:
label11:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
