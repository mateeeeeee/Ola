
.const

_INT0:
.quad 4612811918334230528


_INT1:
.quad 4617315517961601024


.text

.extern _Assert
.extern _AssertMsg
.globl _MathHelper.int.$Double__I
_MathHelper.int.$Double__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
mov x27, x1
str x27, [x29, #-24]
ldr x27, [x29, #-24]
mov x2, #2
mov x1, x27
mov x0, x28
bl _MathHelper.int.$Multiply__I__I
mov x28, x0
str x28, [x29, #-32]
b label2
label1:
label2:
ldr x28, [x29, #-32]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _MathHelper.int.$Triple__I
_MathHelper.int.$Triple__I:
label3:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
mov x27, x1
str x27, [x29, #-24]
ldr x27, [x29, #-24]
mov x2, #3
mov x1, x27
mov x0, x28
bl _MathHelper.int.$Multiply__I__I
mov x28, x0
str x28, [x29, #-32]
b label5
label4:
label5:
ldr x28, [x29, #-32]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _MathHelper.int.$Multiply__I__I
_MathHelper.int.$Multiply__I__I:
label6:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x28, x1
mov x27, x2
str x28, [x29, #-40]
str x27, [x29, #-48]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
mul x26, x27, x28
str x26, [x29, #-56]
b label8
label7:
label8:
ldr x26, [x29, #-56]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _MathHelper.float.$Double__F
_MathHelper.float.$Double__F:
label9:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d29, [x29, #-24]
str d30, [x29, #-32]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
mov x27, #2
scvtf d29, x27
fmov d2, d29
fmov d1, d30
mov x0, x28
bl _MathHelper.float.$Multiply__F__F
fmov d30, d0
str d30, [x29, #-48]
b label11
label10:
label11:
ldr d30, [x29, #-48]
fmov d0, d30
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d29, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _MathHelper.float.$Triple__F
_MathHelper.float.$Triple__F:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d29, [x29, #-24]
str d30, [x29, #-32]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
mov x27, #3
scvtf d29, x27
fmov d2, d29
fmov d1, d30
mov x0, x28
bl _MathHelper.float.$Multiply__F__F
fmov d30, d0
str d30, [x29, #-48]
b label14
label13:
label14:
ldr d30, [x29, #-48]
fmov d0, d30
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d29, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _MathHelper.float.$Multiply__F__F
_MathHelper.float.$Multiply__F__F:
label15:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x28, [x29, #-8]
str d28, [x29, #-16]
str d29, [x29, #-24]
str d30, [x29, #-32]
mov x28, x0
fmov d30, d1
fmov d29, d2
str d30, [x29, #-40]
str d29, [x29, #-48]
ldr d29, [x29, #-40]
ldr d30, [x29, #-48]
fmul d28, d29, d30
str d28, [x29, #-56]
b label17
label16:
label17:
ldr d28, [x29, #-56]
fmov d0, d28
ldr x28, [x29, #-8]
ldr d28, [x29, #-16]
ldr d29, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label18:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x28, [x29, #-8]
str d29, [x29, #-16]
str d30, [x29, #-24]
mov x1, #5
sub x0, x29, #48
bl _MathHelper.int.$Double__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #4
sub x0, x29, #48
bl _MathHelper.int.$Triple__I
mov x28, x0
cmp x28, #12
cset w28, eq
mov w0, w28
bl _Assert
mov x2, #7
mov x1, #3
sub x0, x29, #48
bl _MathHelper.int.$Multiply__I__I
mov x28, x0
cmp x28, #21
cset w28, eq
mov w0, w28
bl _Assert
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d1, x28
sub x0, x29, #56
bl _MathHelper.float.$Double__F
fmov d30, d0
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d29, x28
fcmp d30, d29
cset w28, eq
mov w0, w28
bl _Assert
mov x28, #0
str x28, [x29, #-40]
b label20
label19:
label20:
ldr x28, [x29, #-40]
mov x0, x28
ldr x28, [x29, #-8]
ldr d29, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
