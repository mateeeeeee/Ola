
.const

_INT0:
.quad 4607632778762754458


_INT1:
.quad 4612136378390124954


_INT2:
.quad 4626322717216342016


_INT3:
.quad 4621819117588971520


_INT4:
.quad 4591870180066957722


.text

.extern _Assert
.extern _AssertMsg
_Max__I__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
cmp x28, x27
cset w26, gt
tst w26, w26
b.ne label1
b label2
label1:
mov x26, x28
b label3
label2:
mov x26, x27
b label3
label3:
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_Max__F__F:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
str d28, [x29, #-16]
str d29, [x29, #-24]
str d30, [x29, #-32]
fmov d30, d0
fmov d29, d1
fcmp d30, d29
cset w28, gt
tst w28, w28
b.ne label5
b label6
label5:
fmov d28, d30
b label7
label6:
fmov d28, d29
b label7
label7:
fmov d0, d28
ldr x28, [x29, #-8]
ldr d28, [x29, #-16]
ldr d29, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_Min__I__I:
label8:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
mov x28, x1
cmp x28, #3
cset w27, ge
tst w27, w27
b.ne label9
b label10
label9:
mov x27, #3
b label11
label10:
mov x27, x28
b label11
label11:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_Min__F__F:
label12:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
str d30, [x29, #-16]
fmov d30, d0
fmov d30, d1
b label13
label13:
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d0, x28
ldr x28, [x29, #-8]
ldr d30, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _main
_main:
label14:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
str d29, [x29, #-48]
str d30, [x29, #-56]
b label15
label15:
mov w0, #1
bl _Assert
b label16
label16:
mov w0, #1
bl _Assert
b label17
label17:
mov w0, #1
bl _Assert
b label18
label18:
mov w0, #1
bl _Assert
b label19
label19:
mov w0, #1
bl _Assert
b label20
label20:
mov w0, #1
bl _Assert
mov x1, #7
mov x0, #3
bl _Max__I__I
mov x28, x0
cmp x28, #7
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #5
mov x0, #10
bl _Max__I__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d1, x28
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d0, x28
bl _Max__F__F
fmov d30, d0
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d29, x28
fcmp d30, d29
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #7
mov x0, #3
bl _Min__I__I
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d1, x28
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d0, x28
bl _Min__F__F
fmov d29, d0
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d30, x28
fcmp d29, d30
cset w28, eq
mov w0, w28
bl _Assert
b label21
label21:
mov w0, #1
bl _Assert
b label22
label22:
mov w0, #1
bl _Assert
b label29
label23:
cmp w28, #1
cset w27, eq
mov w0, w27
bl _Assert
b label24
label24:
mov w0, #1
bl _Assert
b label25
label25:
mov w0, #1
bl _Assert
b label26
label26:
mov w0, #1
bl _Assert
mov x1, #2
mov x0, #1
bl _Max__I__I
mov x27, x0
mov x1, #4
mov x0, #3
bl _Min__I__I
mov x26, x0
b label28
label27:
cmp x25, #5
cset w24, eq
mov w0, w24
bl _Assert
adrp x24, _INT2@PAGE
ldr x24, [x24, _INT2@PAGEOFF]
fmov d1, x24
adrp x24, _INT3@PAGE
ldr x24, [x24, _INT3@PAGEOFF]
fmov d0, x24
bl _Max__F__F
fmov d30, d0
adrp x24, _INT2@PAGE
ldr x24, [x24, _INT2@PAGEOFF]
fmov d29, x24
fcmp d30, d29
cset w24, eq
mov w0, w24
bl _Assert
b label30
label28:
add x25, x27, x26
b label27
label29:
mov x26, #0
scvtf d29, x26
adrp x26, _INT4@PAGE
ldr x26, [x26, _INT4@PAGEOFF]
fmov d30, x26
fcmp d30, d29
cset w28, gt
b label23
label30:
mov x0, #0
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldr d29, [x29, #-48]
ldr d30, [x29, #-56]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
