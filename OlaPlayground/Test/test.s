
.data

_VTable_Base:
.quad _Base$GetValue
.p2align 3


_VTable_Derived:
.quad _Derived$GetValue
.p2align 3


.text

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
.globl _Derived$GetValue
_Derived$GetValue:
label3:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov x28, x0
mov x28, #10
str x28, [x29, #-24]
b label5
label4:
label5:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label6:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
sub x28, x29, #64
adrp x27, _VTable_Derived@PAGE
add x27, x27, _VTable_Derived@PAGEOFF
add x26, x28, #0
str x27, [x26]
sub x26, x29, #64
add x27, x26, #8
mov x26, #1
str x26, [x27]
sub x26, x29, #64
add x27, x26, #16
mov x26, #10
str x26, [x27]
sub x26, x29, #64
add x27, x26, #0
ldr x26, [x27]
add x27, x26, #0
ldr x26, [x27]
sub x0, x29, #64
bl _Derived$GetValue
mov x26, x0
str x26, [x29, #-72]
ldr x26, [x29, #-72]
str x26, [x29, #-40]
b label8
label7:
label8:
ldr x26, [x29, #-40]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
