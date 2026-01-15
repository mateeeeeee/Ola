
.text

.extern _Assert
.extern _AssertMsg
.globl _B$B__I
_B$B__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
add x26, x28, #0
str x27, [x26]
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _D$D__I
_D$D__I:
label2:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
add x26, x27, x27
b label4
label3:
add x25, x28, #16
str x27, [x25]
b label5
label4:
add x25, x28, #0
str x26, [x25]
b label3
label5:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _D$D__I__I
_D$D__I__I:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
mov x26, x2
mov x1, x27
mov x0, x28
bl _D$D__I
add x27, x28, #16
ldr x28, [x27]
mul x25, x28, x26
str x25, [x27]
b label7
label7:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label8:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
sub x28, x29, #64
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #64
add x26, x28, #16
mov x28, #0
str x28, [x26]
mov x1, #5
sub x0, x29, #64
bl _D$D__I
ldr x28, [x26]
cmp x28, #5
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x27]
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #80
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #80
add x26, x28, #16
mov x28, #0
str x28, [x26]
b label10
label9:
ldr x28, [x26]
cmp x28, #6
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x27]
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
b label11
label10:
mov x1, #2
sub x0, x29, #80
bl _D$D__I
ldr x28, [x26]
mov x25, #3
mul x24, x28, x25
str x24, [x26]
b label9
label11:
mov x0, #0
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
