
.text

.extern _Assert
.extern _AssertMsg
_Helper__I__I:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x28, x1
mov x27, #10
str x27, [x29, #-40]
str x28, [x29, #-48]
ldr x28, [x29, #-40]
ldr x27, [x29, #-48]
add x26, x28, x27
str x26, [x29, #-56]
b label2
label1:
label2:
ldr x26, [x29, #-56]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label3:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
mov x1, #5
mov x0, #10
bl _Helper__I__I
mov x28, x0
str x28, [x29, #-32]
mov x1, #20
mov x0, #10
bl _Helper__I__I
mov x28, x0
str x28, [x29, #-40]
mov x1, #100
mov x0, #10
bl _Helper__I__I
mov x28, x0
str x28, [x29, #-48]
ldr x28, [x29, #-32]
cmp x28, #15
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x29, #-40]
cmp x28, #30
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x29, #-48]
cmp x28, #110
cset w28, eq
mov w0, w28
bl _Assert
mov x28, #0
str x28, [x29, #-24]
b label5
label4:
label5:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
