
.data

_VTable_Animal:
.quad _Animal$Speak
.p2align 3


_VTable_Dog:
.quad _Dog$Speak
.p2align 3


.text

.extern _Assert
.extern _AssertMsg
.globl _Animal$Animal
_Animal$Animal:
label0:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
mov x28, #0
str x28, [x27]
b label1
label1:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Animal$Animal__I
_Animal$Animal__I:
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
add x26, x28, #8
str x27, [x26]
b label3
label3:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Animal$GetLegs
_Animal$GetLegs:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label6
label5:
label6:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Animal$Speak
_Animal$Speak:
label7:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov x28, x0
mov x28, #0
str x28, [x29, #-24]
b label9
label8:
label9:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Dog$Dog
_Dog$Dog:
label10:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
mov x0, x28
bl _Animal$Animal
add x27, x28, #16
mov x28, #0
str x28, [x27]
b label11
label11:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Dog$Dog__I__I
_Dog$Dog__I__I:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
mov x26, x2
str x27, [x29, #-40]
str x26, [x29, #-48]
ldr x26, [x29, #-40]
mov x1, x26
mov x0, x28
bl _Animal$Animal__I
ldr x26, [x29, #-48]
add x27, x28, #16
str x26, [x27]
b label13
label13:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Dog$Speak
_Dog$Speak:
label14:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #16
ldr x28, [x27]
str x28, [x29, #-24]
b label16
label15:
label16:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label17:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x0, #24
bl ___ola_new
mov x28, x0
adrp x27, _VTable_Dog@PAGE
add x27, x27, _VTable_Dog@PAGEOFF
add x26, x28, #0
str x27, [x26]
add x26, x28, #8
mov x27, #0
str x27, [x26]
add x27, x28, #16
mov x26, #0
str x26, [x27]
mov x2, #10
mov x1, #4
mov x0, x28
bl _Dog$Dog__I__I
str x28, [x29, #-48]
ldr x28, [x29, #-48]
ldr x28, [x29, #-48]
str x28, [x29, #-56]
ldr x28, [x29, #-56]
add x26, x28, #0
mov x0, x26
bl _Animal$GetLegs
mov x26, x0
cmp x26, #4
cset w26, eq
mov w0, w26
bl _Assert
ldr x26, [x29, #-56]
add x28, x26, #0
add x26, x28, #0
ldr x27, [x26]
add x26, x27, #0
ldr x27, [x26]
mov x0, x28
mov x16, x27
blr x16
mov x27, x0
cmp x27, #10
cset w27, eq
mov w0, w27
bl _Assert
ldr x27, [x29, #-56]
add x28, x27, #0
mov x0, x28
bl _Animal$GetLegs
mov x28, x0
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x29, #-48]
add x27, x28, #0
add x28, x27, #0
ldr x26, [x28]
add x28, x26, #0
ldr x26, [x28]
mov x0, x27
mov x16, x26
blr x16
mov x26, x0
cmp x26, #10
cset w26, eq
mov w0, w26
bl _Assert
ldr x26, [x29, #-48]
mov x0, x26
bl ___ola_delete
mov x26, #0
str x26, [x29, #-40]
b label19
label18:
label19:
ldr x26, [x29, #-40]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.extern ___ola_new
.extern ___ola_delete
