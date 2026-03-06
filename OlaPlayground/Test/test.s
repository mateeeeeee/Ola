
.text

.extern _Assert
.extern _AssertMsg
.globl _Optional.int.$Optional
_Optional.int.$Optional:
label0:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
mov w28, #0
strb w28, [x27]
b label1
label1:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Optional.int.$Optional__I
_Optional.int.$Optional__I:
label2:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
str x27, [x29, #-40]
ldr x27, [x29, #-40]
add x26, x28, #0
str x27, [x26]
add x26, x28, #8
mov w28, #1
strb w28, [x26]
b label3
label3:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Optional.int.$HasValue
_Optional.int.$HasValue:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-17]
b label6
label5:
label6:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Optional.int.$Value
_Optional.int.$Value:
label7:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label9
label8:
label9:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Optional.int.$Test
_Optional.int.$Test:
label10:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #8
ldrb w26, [x27]
tst w26, w26
b.ne label11
b label13
label11:
add x26, x28, #0
ldr x28, [x26]
cmp x28, #42
cset w28, eq
mov w0, w28
bl _Assert
b label13
label12:
label13:
b label14
label14:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label15:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #40
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #8
mov w28, #0
strb w28, [x27]
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov w28, #0
strb w28, [x27]
mov x1, #42
sub x0, x29, #56
bl _Optional.int.$Optional__I
sub x0, x29, #40
bl _Optional.int.$HasValue
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Optional.int.$HasValue
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Optional.int.$Value
mov x28, x0
cmp x28, #42
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Optional.int.$Test
sub x0, x29, #40
bl _Optional.int.$Test
mov x28, #0
str x28, [x29, #-24]
b label17
label16:
label17:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
