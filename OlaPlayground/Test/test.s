
.text

.extern _Assert
.extern _AssertMsg
.globl _Vector.int.$Vector
_Vector.int.$Vector:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #0
mov x26, #0
str x26, [x27]
add x26, x28, #8
mov x27, #0
str x27, [x26]
add x27, x28, #16
mov x28, #0
str x28, [x27]
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Vector__I
_Vector.int.$Vector__I:
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
lsl x26, x27, #3
mov x0, x26
bl ___ola_new
mov x26, x0
add x25, x28, #0
str x26, [x25]
add x25, x28, #8
mov x26, #0
str x26, [x25]
add x26, x28, #16
str x27, [x26]
b label3
label3:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.extern ___ola_new
.globl _Vector.int.$Size
_Vector.int.$Size:
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
b label5
label5:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Capacity
_Vector.int.$Capacity:
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
b label7
label7:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Empty
_Vector.int.$Empty:
label8:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
cmp x28, #0
cset w28, eq
b label9
label9:
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Vector.int.$Get__I
_Vector.int.$Get__I:
label10:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
add x26, x28, #0
ldr x28, [x26]
mov x26, #8
mul x25, x27, x26
add x26, x28, x25
ldr x25, [x26]
b label11
label11:
mov x0, x25
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Set__I__I
_Vector.int.$Set__I__I:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
mov x27, x1
mov x26, x2
add x25, x28, #0
ldr x28, [x25]
mov x25, #8
mul x24, x27, x25
add x25, x28, x24
str x26, [x25]
b label13
label13:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Vector.int.$Front
_Vector.int.$Front:
label14:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label15
label15:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Back
_Vector.int.$Back:
label16:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
add x27, x28, #8
ldr x26, [x27]
add x27, x28, #0
ldr x28, [x27]
sub x27, x26, #1
mov x26, #8
mul x25, x27, x26
add x26, x28, x25
ldr x25, [x26]
b label17
label17:
mov x0, x25
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$PushBack__I
_Vector.int.$PushBack__I:
label18:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x19, [x29, #-8]
str x20, [x29, #-16]
str x21, [x29, #-24]
str x22, [x29, #-32]
str x23, [x29, #-40]
str x24, [x29, #-48]
str x25, [x29, #-56]
str x26, [x29, #-64]
str x27, [x29, #-72]
str x28, [x29, #-80]
mov x28, x0
mov x27, x1
add x16, x28, #8
str x16, [x29, #-88]
ldr x16, [x29, #-88]
ldr x25, [x16]
add x24, x28, #16
ldr x23, [x24]
cmp x25, x23
cset w23, lt
tst w23, w23
b.ne label19
b label20
label19:
ldr x16, [x29, #-88]
ldr x23, [x16]
add x25, x28, #0
ldr x22, [x25]
mov x25, #8
mul x21, x23, x25
add x25, x22, x21
str x27, [x25]
ldr x16, [x29, #-88]
ldr x25, [x16]
add x21, x25, #1
ldr x16, [x29, #-88]
str x21, [x16]
b label28
label20:
ldr x21, [x24]
ldr x25, [x24]
cmp x21, #0
cset w21, gt
add x22, x25, x25
tst w21, w21
mov x21, #4
csel x21, x22, x21, ne
lsl x22, x21, #3
mov x0, x22
bl ___ola_new
mov x22, x0
add x25, x28, #0
mov x23, #0
b label22
label21:
ldr x20, [x25]
mov x19, #8
mul x26, x23, x19
add x19, x20, x26
ldr x26, [x19]
mov x19, #8
mul x20, x23, x19
add x19, x22, x20
str x26, [x19]
b label23
label22:
ldr x16, [x29, #-88]
ldr x19, [x16]
cmp x23, x19
cset w19, lt
tst w19, w19
b.ne label21
b label24
label23:
add x19, x23, #1
mov x23, x19
b label22
label24:
ldr x16, [x29, #-88]
ldr x19, [x16]
mov x23, #8
mul x25, x19, x23
add x23, x22, x25
str x27, [x23]
add x23, x28, #0
ldr x27, [x23]
cmp x27, #0
cset w27, ne
tst w27, w27
b.ne label26
b label25
label25:
b label27
label26:
add x27, x28, #0
ldr x23, [x27]
mov x0, x23
bl ___ola_delete
b label27
label27:
add x23, x28, #0
str x22, [x23]
str x21, [x24]
ldr x16, [x29, #-88]
ldr x21, [x16]
add x24, x21, #1
ldr x16, [x29, #-88]
str x24, [x16]
b label28
label28:
ldr x19, [x29, #-8]
ldr x20, [x29, #-16]
ldr x21, [x29, #-24]
ldr x22, [x29, #-32]
ldr x23, [x29, #-40]
ldr x24, [x29, #-48]
ldr x25, [x29, #-56]
ldr x26, [x29, #-64]
ldr x27, [x29, #-72]
ldr x28, [x29, #-80]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.extern ___ola_delete
.globl _Vector.int.$PopBack
_Vector.int.$PopBack:
label29:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
sub x26, x28, #1
str x26, [x27]
b label30
label30:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Vector.int.$Clear
_Vector.int.$Clear:
label31:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
mov x28, #0
str x28, [x27]
b label32
label32:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Vector.int.$Destroy
_Vector.int.$Destroy:
label33:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #0
ldr x26, [x27]
cmp x26, #0
cset w26, ne
tst w26, w26
b.ne label35
b label34
label34:
b label36
label35:
ldr x26, [x27]
mov x0, x26
bl ___ola_delete
b label36
label36:
mov x26, #0
str x26, [x27]
add x26, x28, #8
mov x27, #0
str x27, [x26]
add x27, x28, #16
mov x28, #0
str x28, [x27]
b label37
label37:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label38:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x21, [x29, #-8]
str x22, [x29, #-16]
str x23, [x29, #-24]
str x24, [x29, #-32]
str x25, [x29, #-40]
str x26, [x29, #-48]
str x27, [x29, #-56]
str x28, [x29, #-64]
sub x28, x29, #88
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #88
add x26, x28, #8
mov x28, #0
str x28, [x26]
sub x28, x29, #88
add x25, x28, #16
mov x28, #0
str x28, [x25]
mov x1, #10
sub x0, x29, #88
bl _Vector.int.$PushBack__I
b label43
label39:
cmp x28, #1
cset w25, eq
mov w0, w25
bl _Assert
b label41
label40:
cmp x25, #10
cset w24, eq
mov w0, w24
bl _Assert
sub x0, x29, #88
bl _Vector.int.$Destroy
b label44
label41:
ldr x24, [x27]
mov x23, #8
mov x22, #0
mul x21, x22, x23
add x22, x24, x21
ldr x25, [x22]
b label40
label42:
ldr x28, [x29, #-96]
b label39
label43:
ldr x25, [x26]
str x25, [x29, #-96]
b label42
label44:
mov x0, #0
ldr x21, [x29, #-8]
ldr x22, [x29, #-16]
ldr x23, [x29, #-24]
ldr x24, [x29, #-32]
ldr x25, [x29, #-40]
ldr x26, [x29, #-48]
ldr x27, [x29, #-56]
ldr x28, [x29, #-64]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
