
.const

_INT0:
.quad 4614253070214989087


_INT1:
.quad 4607182418800017408


_INT2:
.quad 4611686018427387904


.text

.extern _Assert
.extern _AssertMsg
_TestSizeofTypes:
label0:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
b label1
label1:
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
_TestSizeofExpressions:
label2:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
str d30, [x29, #-16]
mov x28, #42
str x28, [x29, #-24]
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d30, x28
str d30, [x29, #-32]
mov w28, #1
strb w28, [x29, #-33]
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
b label3
label3:
ldr x28, [x29, #-8]
ldr d30, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestSizeofArrays:
label4:
sub sp, sp, #144
stp x29, x30, [sp, #128]
add x29, sp, #128
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
b label5
label5:
ldp x29, x30, [sp, #128]
add sp, sp, #144
ret
_TestSizeofInExpressions:
label6:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
mov x28, #17
str x28, [x29, #-24]
ldr x28, [x29, #-24]
cmp x28, #17
cset w28, eq
mov w0, w28
bl _Assert
mov x28, #40
str x28, [x29, #-32]
ldr x28, [x29, #-32]
cmp x28, #40
cset w28, eq
mov w0, w28
bl _Assert
mov w28, #1
strb w28, [x29, #-33]
ldrb w28, [x29, #-33]
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
b label7
label7:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestSizeofInitializedArrays:
label8:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
sub x28, x29, #56
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov x28, #2
str x28, [x27]
sub x28, x29, #56
add x27, x28, #16
mov x28, #3
str x28, [x27]
mov w0, #1
bl _Assert
sub x28, x29, #72
add x27, x28, #0
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d30, x28
str d30, [x27]
sub x27, x29, #72
add x28, x27, #8
adrp x27, _INT2@PAGE
ldr x27, [x27, _INT2@PAGEOFF]
fmov d30, x27
str d30, [x28]
mov w0, #1
bl _Assert
sub x28, x29, #80
add x27, x28, #0
mov w28, #1
strb w28, [x27]
sub x28, x29, #80
add x27, x28, #1
mov w28, #0
strb w28, [x27]
sub x28, x29, #80
add x27, x28, #2
mov w28, #1
strb w28, [x27]
sub x28, x29, #80
add x27, x28, #3
mov w28, #0
strb w28, [x27]
sub x28, x29, #80
add x27, x28, #4
mov w28, #1
strb w28, [x27]
mov w0, #1
bl _Assert
b label9
label9:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_TestSizeofAutoArrays:
label10:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #48
add x27, x28, #0
mov x28, #10
str x28, [x27]
sub x28, x29, #48
add x27, x28, #8
mov x28, #20
str x28, [x27]
sub x28, x29, #48
add x27, x28, #16
mov x28, #30
str x28, [x27]
sub x28, x29, #48
add x27, x28, #24
mov x28, #40
str x28, [x27]
mov w0, #1
bl _Assert
b label11
label11:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestSizeofInConditions:
label12:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
b label13
label13:
mov w0, #1
bl _Assert
b label15
label14:
label15:
b label16
label16:
mov w0, #1
bl _Assert
b label18
label17:
label18:
b label19
label19:
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
_TestSizeofInLoops:
label20:
sub sp, sp, #128
stp x29, x30, [sp, #112]
add x29, sp, #112
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
sub x28, x29, #80
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #80
add x27, x28, #8
mov x28, #2
str x28, [x27]
sub x28, x29, #80
add x27, x28, #16
mov x28, #3
str x28, [x27]
sub x28, x29, #80
add x27, x28, #24
mov x28, #4
str x28, [x27]
mov x28, #0
str x28, [x29, #-88]
mov x28, #8
str x28, [x29, #-96]
mov x28, #0
str x28, [x29, #-104]
b label22
label21:
ldr x25, [x29, #-104]
sub x27, x29, #80
ldr x26, [x29, #-88]
mov x28, #32
mov x24, #0
mul x23, x24, x28
add x24, x27, x23
mov x23, #8
mul x27, x25, x23
add x23, x24, x27
ldr x27, [x23]
add x23, x26, x27
str x23, [x29, #-88]
b label23
label22:
ldr x28, [x29, #-96]
ldr x27, [x29, #-104]
mov x26, #32
sdiv x25, x26, x28
cmp x27, x25
cset w25, lt
tst w25, w25
b.ne label21
b label24
label23:
ldr x23, [x29, #-104]
str x23, [x29, #-112]
add x27, x23, #1
str x27, [x29, #-104]
b label22
label24:
ldr x25, [x29, #-88]
cmp x25, #10
cset w25, eq
mov w0, w25
bl _Assert
b label25
label25:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #112]
add sp, sp, #128
ret
_TestSizeofComparisons:
label26:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
b label27
label27:
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
_TestSizeofVariousArrays:
label28:
sub sp, sp, #160
stp x29, x30, [sp, #144]
add x29, sp, #144
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
mov w0, #1
bl _Assert
b label29
label29:
ldp x29, x30, [sp, #144]
add sp, sp, #160
ret
.globl _main
_main:
label30:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestSizeofTypes
bl _TestSizeofExpressions
bl _TestSizeofArrays
bl _TestSizeofInExpressions
bl _TestSizeofInitializedArrays
bl _TestSizeofAutoArrays
bl _TestSizeofInConditions
bl _TestSizeofInLoops
bl _TestSizeofComparisons
bl _TestSizeofVariousArrays
mov x28, #0
str x28, [x29, #-24]
b label32
label31:
label32:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
