
.data

_VTable_Base:
.quad _Base$GetValue
.quad _Base$GetDoubleValue
.p2align 3


_VTable_Derived:
.quad _Derived$GetValue
.quad _Derived$GetDoubleValue
.p2align 3


.text

.extern _Assert
.extern _AssertMsg
.globl _Base$GetValue
_Base$GetValue:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov x28, x0
mov x28, #1
str x28, [x29, #-24]
b label2
label1:
label2:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Base$GetDoubleValue
_Base$GetDoubleValue:
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
mov x28, #2
mul x27, x26, x28
str x27, [x29, #-40]
b label5
label4:
label5:
ldr x27, [x29, #-40]
mov x0, x27
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Derived$GetValue
_Derived$GetValue:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov x28, x0
mov x28, #10
str x28, [x29, #-24]
b label8
label7:
label8:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Derived$GetDoubleValue
_Derived$GetDoubleValue:
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
mov x28, #2
mul x27, x26, x28
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
_TestVirtualDispatch__Baseref__I:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
str x28, [x29, #-40]
ldr x28, [x29, #-40]
str x27, [x29, #-48]
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
ldr x28, [x29, #-48]
cmp x26, x28
cset w28, eq
mov w0, w28
bl _Assert
b label13
label13:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestVirtualDispatchDouble__Baseref__I:
label14:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
str x28, [x29, #-40]
ldr x28, [x29, #-40]
str x27, [x29, #-48]
add x27, x28, #0
ldr x26, [x27]
add x27, x26, #8
ldr x26, [x27]
mov x0, x28
mov x16, x26
blr x16
mov x26, x0
ldr x28, [x29, #-48]
cmp x26, x28
cset w28, eq
mov w0, w28
bl _Assert
b label15
label15:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label16:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
sub x28, x29, #48
adrp x27, _VTable_Base@PAGE
add x27, x27, _VTable_Base@PAGEOFF
add x26, x28, #0
str x27, [x26]
sub x26, x29, #48
add x27, x26, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
sub x0, x29, #48
mov x16, x26
blr x16
mov x26, x0
cmp x26, #1
cset w26, eq
mov w0, w26
bl _Assert
sub x26, x29, #48
add x27, x26, #0
ldr x26, [x27]
add x27, x26, #8
ldr x26, [x27]
sub x0, x29, #48
mov x16, x26
blr x16
mov x26, x0
cmp x26, #2
cset w26, eq
mov w0, w26
bl _Assert
sub x26, x29, #48
sub x27, x29, #64
ldr x28, [x26]
str x28, [x27]
mov x1, #1
sub x0, x29, #48
bl _TestVirtualDispatch__Baseref__I
sub x28, x29, #48
sub x27, x29, #72
ldr x26, [x28]
str x26, [x27]
mov x1, #2
sub x0, x29, #48
bl _TestVirtualDispatchDouble__Baseref__I
sub x26, x29, #56
adrp x27, _VTable_Derived@PAGE
add x27, x27, _VTable_Derived@PAGEOFF
add x28, x26, #0
str x27, [x28]
sub x28, x29, #56
add x27, x28, #0
ldr x28, [x27]
add x27, x28, #0
ldr x28, [x27]
sub x0, x29, #56
mov x16, x28
blr x16
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #56
add x27, x28, #0
ldr x28, [x27]
add x27, x28, #8
ldr x28, [x27]
sub x0, x29, #56
mov x16, x28
blr x16
mov x28, x0
cmp x28, #20
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #56
sub x27, x29, #80
ldr x26, [x28]
str x26, [x27]
mov x1, #10
sub x0, x29, #56
bl _TestVirtualDispatch__Baseref__I
sub x26, x29, #56
sub x27, x29, #88
ldr x28, [x26]
str x28, [x27]
mov x1, #20
sub x0, x29, #56
bl _TestVirtualDispatchDouble__Baseref__I
mov x28, #0
str x28, [x29, #-40]
b label18
label17:
label18:
ldr x28, [x29, #-40]
mov x0, x28
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
