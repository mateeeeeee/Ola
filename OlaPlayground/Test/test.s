
.text

.extern _Assert
.extern _AssertMsg
_TestPtrBasic:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x0, #8
bl ___ola_alloc
mov x28, x0
add x27, x28, #0
mov x26, #42
str x26, [x27]
ldr x26, [x27]
cmp x26, #42
cset w26, eq
mov w0, w26
bl _Assert
mov x0, x28
bl ___ola_free
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.extern ___ola_alloc
.extern ___ola_free
_TestPtrNull:
label2:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #0
str x28, [x29, #-24]
ldr x28, [x29, #-24]
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #8
bl ___ola_alloc
mov x28, x0
str x28, [x29, #-24]
ldr x28, [x29, #-24]
cmp x28, #0
cset w28, ne
mov w0, w28
bl _Assert
ldr x28, [x29, #-24]
add x27, x28, #0
mov x28, #10
str x28, [x27]
ldr x28, [x29, #-24]
add x27, x28, #0
ldr x28, [x27]
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x29, #-24]
mov x0, x28
bl ___ola_free
b label3
label3:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestPtrArray:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x0, #40
bl ___ola_alloc
mov x28, x0
mov x27, #8
mov x26, #0
mul x25, x26, x27
add x26, x28, x25
mov x25, #0
str x25, [x26]
mov x25, #8
add x26, x28, x25
mov x25, #1
str x25, [x26]
mov x25, #8
mov x26, #2
mul x27, x26, x25
add x26, x28, x27
mov x27, #4
str x27, [x26]
mov x27, #8
mov x26, #3
mul x25, x26, x27
add x26, x28, x25
mov x25, #9
str x25, [x26]
mov x25, #8
mov x26, #4
mul x27, x26, x25
add x26, x28, x27
mov x27, #16
str x27, [x26]
b label5
label5:
add x27, x28, #0
ldr x26, [x27]
cmp x26, #0
cset w26, eq
mov w0, w26
bl _Assert
add x26, x28, #8
ldr x27, [x26]
cmp x27, #1
cset w27, eq
mov w0, w27
bl _Assert
add x27, x28, #16
ldr x26, [x27]
cmp x26, #4
cset w26, eq
mov w0, w26
bl _Assert
add x26, x28, #24
ldr x27, [x26]
cmp x27, #9
cset w27, eq
mov w0, w27
bl _Assert
add x27, x28, #32
ldr x26, [x27]
cmp x26, #16
cset w26, eq
mov w0, w26
bl _Assert
mov x0, x28
bl ___ola_free
b label6
label6:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestPtrPassToFunction:
label7:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x0, #8
bl ___ola_alloc
mov x28, x0
b label11
label8:
cmp x27, #99
cset w26, eq
mov w0, w26
bl _Assert
mov x0, x28
bl ___ola_free
b label12
label9:
ldr x27, [x29, #-48]
b label8
label10:
ldr x26, [x25]
str x26, [x29, #-48]
b label9
label11:
ldr x26, [x29, #-40]
add x25, x26, #0
mov x26, #99
str x26, [x25]
b label10
label12:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_AllocAndInit__I__I:
label13:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x28, x1
mov x0, #24
bl ___ola_alloc
mov x28, x0
mov x27, #8
mov x26, #0
mul x25, x26, x27
add x26, x28, x25
mov x25, #7
str x25, [x26]
mov x25, #8
add x26, x28, x25
mov x25, #7
str x25, [x26]
mov x25, #8
mov x26, #2
mul x27, x26, x25
add x26, x28, x27
mov x27, #7
str x27, [x26]
b label14
label14:
mov x0, x28
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestPtrReturn:
label15:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x1, #7
mov x0, #3
bl _AllocAndInit__I__I
mov x28, x0
add x27, x28, #0
ldr x26, [x27]
cmp x26, #7
cset w26, eq
mov w0, w26
bl _Assert
add x26, x28, #8
ldr x27, [x26]
cmp x27, #7
cset w27, eq
mov w0, w27
bl _Assert
add x27, x28, #16
ldr x26, [x27]
cmp x26, #7
cset w26, eq
mov w0, w26
bl _Assert
mov x0, x28
bl ___ola_free
b label16
label16:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label17:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestPtrBasic
bl _TestPtrNull
bl _TestPtrArray
bl _TestPtrPassToFunction
bl _TestPtrReturn
b label18
label18:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
