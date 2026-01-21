
.text

.extern _Assert
.extern _AssertMsg
.globl _TestLICM__I__I__I
_TestLICM__I__I__I:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x27, x1
mov x26, x2
mul x25, x28, x27
mov x27, #0
mov x28, #0
b label2
label1:
add x24, x27, x25
b label3
label2:
cmp x28, x26
cset w23, lt
tst w23, w23
b.ne label1
b label4
label3:
str x28, [x29, #-56]
add x23, x28, #1
mov x27, x24
mov x28, x23
b label2
label4:
mov x0, x27
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestNestedLoops__I__I__I:
label5:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x28, x1
mov x28, x2
mov x28, #0
mov x27, #0
b label7
label6:
mov x26, x28
mov x25, #0
b label10
label7:
cmp x27, #2
cset w24, lt
tst w24, w24
b.ne label6
b label12
label8:
str x27, [x29, #-56]
add x24, x27, #1
mov x28, x26
mov x27, x24
b label7
label9:
add x24, x26, #10
b label11
label10:
cmp x25, #3
cset w23, lt
tst w23, w23
b.ne label9
b label8
label11:
str x25, [x29, #-64]
add x23, x25, #1
mov x26, x24
mov x25, x23
b label10
label12:
mov x0, x28
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_SimpleSum__I:
label13:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x28, #0
mov x27, #0
b label15
label14:
add x26, x28, x27
b label16
label15:
cmp x27, #5
cset w25, lt
tst w25, w25
b.ne label14
b label17
label16:
str x27, [x29, #-40]
add x25, x27, #1
mov x28, x26
mov x27, x25
b label15
label17:
mov x0, x28
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label18:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x2, #5
mov x1, #4
mov x0, #3
bl _TestLICM__I__I__I
mov x28, x0
cmp x28, #60
cset w28, eq
mov w0, w28
bl _Assert
mov x2, #3
mov x1, #2
mov x0, #5
bl _TestNestedLoops__I__I__I
mov x28, x0
cmp x28, #60
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #5
bl _SimpleSum__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
b label19
label19:
mov x0, #0
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
