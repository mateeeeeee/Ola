
.data

_VTable_Abstract:
.byte 0
.byte 0
.byte 0
.byte 0
.byte 0
.byte 0
.byte 0
.byte 0
.p2align 3


_VTable_Base:
.quad _Base$GetX
.quad _Base$GetSumX
.p2align 3


_VTable_Derived:
.quad _Derived$GetX
.quad _Derived$GetSumX
.p2align 3


.text

.extern _Assert
.extern _AssertMsg
.extern _Abstract$GetX
.globl _Base$GetX
_Base$GetX:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label2
label1:
label2:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Base$GetSumX
_Base$GetSumX:
label3:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
str x26, [x29, #-40]
b label5
label4:
label5:
ldr x26, [x29, #-40]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Derived$GetX
_Derived$GetX:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #16
ldr x28, [x27]
str x28, [x29, #-24]
b label8
label7:
label8:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Derived$GetSumX
_Derived$GetSumX:
label9:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
mov x0, x28
bl _Base$GetX
mov x28, x0
add x27, x26, x28
str x27, [x29, #-40]
b label11
label10:
label11:
ldr x27, [x29, #-40]
mov x0, x27
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestBase__Abstractref:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
str x28, [x29, #-40]
ldr x28, [x29, #-40]
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
cmp x26, #1
cset w26, eq
mov w0, w26
bl _Assert
b label13
label13:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDerived__Abstractref:
label14:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
str x28, [x29, #-40]
ldr x28, [x29, #-40]
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
cmp x26, #10
cset w26, eq
mov w0, w26
bl _Assert
b label15
label15:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDerived2__Baseref:
label16:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
str x28, [x29, #-40]
ldr x28, [x29, #-40]
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
cmp x26, #10
cset w26, eq
mov w0, w26
bl _Assert
add x26, x28, #0
ldr x27, [x26]
add x26, x27, #8
ldr x27, [x26]
mov x0, x28
mov x16, x27
blr x16
mov x27, x0
cmp x27, #11
cset w27, eq
mov w0, w27
bl _Assert
b label17
label17:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label18:
sub sp, sp, #176
stp x29, x30, [sp, #160]
add x29, sp, #160
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
sub x28, x29, #72
adrp x27, _VTable_Base@PAGE
add x27, x27, _VTable_Base@PAGEOFF
add x26, x28, #0
str x27, [x26]
sub x26, x29, #72
add x27, x26, #8
mov x26, #1
str x26, [x27]
sub x26, x29, #72
sub x27, x29, #112
ldr x28, [x26]
add x25, x26, #8
ldr x26, [x25]
add x25, x27, #8
str x28, [x27]
str x26, [x25]
sub x0, x29, #72
bl _TestBase__Abstractref
sub x25, x29, #96
adrp x26, _VTable_Derived@PAGE
add x26, x26, _VTable_Derived@PAGEOFF
add x28, x25, #0
str x26, [x28]
sub x28, x29, #96
add x26, x28, #8
mov x28, #1
str x28, [x26]
sub x28, x29, #96
add x26, x28, #16
mov x28, #10
str x28, [x26]
sub x28, x29, #96
sub x26, x29, #136
ldr x25, [x28]
add x27, x28, #8
ldr x24, [x27]
add x27, x26, #8
str x25, [x26]
add x25, x28, #16
ldr x28, [x25]
add x25, x26, #16
str x24, [x27]
str x28, [x25]
sub x0, x29, #96
bl _TestDerived__Abstractref
sub x25, x29, #96
sub x28, x29, #160
ldr x27, [x25]
add x24, x25, #8
ldr x26, [x24]
add x24, x28, #8
str x27, [x28]
add x27, x25, #16
ldr x25, [x27]
add x27, x28, #16
str x26, [x24]
str x25, [x27]
sub x0, x29, #96
bl _TestDerived2__Baseref
mov x27, #0
str x27, [x29, #-56]
b label20
label19:
label20:
ldr x27, [x29, #-56]
mov x0, x27
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #160]
add sp, sp, #176
ret
