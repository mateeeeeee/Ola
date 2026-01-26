
.const

_INT0:
.quad 4611686018427387904


_INT1:
.quad 4607182418800017408


_INT2:
.quad 4613937818241073152


_INT3:
.quad 4618441417868443648


_INT4:
.quad 4616189618054758400


_INT5:
.quad 4619567317775286272


.text

.extern _Assert
.extern _AssertMsg
_Add__I__I:
label0:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
str x27, [x29, #-16]
mov x27, x0
mov x28, x1
str x27, [x29, #-24]
str x28, [x29, #-32]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
add x28, x27, x28
str x28, [x29, #-40]
b label2
label1:
label2:
ldr x28, [x29, #-40]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_AddThreeNumbers__I__I__I:
label3:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x28, [x29, #-8]
str x27, [x29, #-16]
str x26, [x29, #-24]
mov x26, x0
mov x27, x1
mov x28, x2
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
ldr x26, [x29, #-40]
ldr x28, [x29, #-48]
ldr x27, [x29, #-56]
add x28, x26, x28
add x28, x28, x27
str x28, [x29, #-64]
b label5
label4:
label5:
ldr x28, [x29, #-64]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldr x26, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_AddFourNumbers__I__I__I__I:
label6:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x28, [x29, #-8]
str x27, [x29, #-16]
str x26, [x29, #-24]
str x25, [x29, #-32]
mov x25, x0
mov x26, x1
mov x27, x2
mov x28, x3
str x25, [x29, #-40]
str x26, [x29, #-48]
str x27, [x29, #-56]
str x28, [x29, #-64]
ldr x25, [x29, #-40]
ldr x28, [x29, #-48]
ldr x26, [x29, #-56]
ldr x27, [x29, #-64]
add x28, x25, x28
add x28, x28, x26
add x28, x28, x27
str x28, [x29, #-72]
b label8
label7:
label8:
ldr x28, [x29, #-72]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldr x26, [x29, #-24]
ldr x25, [x29, #-32]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_AddSixNumbers__I__I__I__I__I__I:
label9:
sub sp, sp, #128
stp x29, x30, [sp, #112]
add x29, sp, #112
str x28, [x29, #-8]
str x27, [x29, #-16]
str x26, [x29, #-24]
str x25, [x29, #-32]
str x24, [x29, #-40]
str x23, [x29, #-48]
mov x23, x0
mov x24, x1
mov x25, x2
mov x26, x3
mov x27, x4
mov x28, x5
str x23, [x29, #-56]
str x24, [x29, #-64]
str x25, [x29, #-72]
str x26, [x29, #-80]
str x27, [x29, #-88]
str x28, [x29, #-96]
ldr x28, [x29, #-56]
ldr x25, [x29, #-64]
ldr x26, [x29, #-72]
ldr x23, [x29, #-80]
ldr x24, [x29, #-88]
ldr x27, [x29, #-96]
add x28, x28, x25
add x28, x28, x26
add x28, x28, x23
add x28, x28, x24
add x28, x28, x27
str x28, [x29, #-104]
b label11
label10:
label11:
ldr x28, [x29, #-104]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldr x26, [x29, #-24]
ldr x25, [x29, #-32]
ldr x24, [x29, #-40]
ldr x23, [x29, #-48]
ldp x29, x30, [sp, #112]
add sp, sp, #128
ret
_AddTenNumbers__I__I__I__I__I__I__I__I__I__I:
label12:
sub sp, sp, #192
stp x29, x30, [sp, #176]
add x29, sp, #176
str x24, [x29, #-8]
str x23, [x29, #-16]
str x22, [x29, #-24]
str x28, [x29, #-32]
str x26, [x29, #-40]
str x21, [x29, #-48]
str x25, [x29, #-56]
str x20, [x29, #-64]
str x27, [x29, #-72]
str x19, [x29, #-80]
mov x19, x0
mov x27, x1
mov x20, x2
mov x25, x3
mov x21, x4
mov x26, x5
mov x28, x6
mov x22, x7
ldr x23, [x29, #16]
ldr x24, [x29, #24]
str x19, [x29, #-88]
str x27, [x29, #-96]
str x20, [x29, #-104]
str x25, [x29, #-112]
str x21, [x29, #-120]
str x26, [x29, #-128]
str x28, [x29, #-136]
str x22, [x29, #-144]
str x23, [x29, #-152]
str x24, [x29, #-160]
ldr x19, [x29, #-88]
ldr x28, [x29, #-96]
ldr x20, [x29, #-104]
ldr x21, [x29, #-112]
ldr x22, [x29, #-120]
ldr x23, [x29, #-128]
ldr x24, [x29, #-136]
ldr x25, [x29, #-144]
ldr x26, [x29, #-152]
ldr x27, [x29, #-160]
add x28, x19, x28
add x28, x28, x20
add x28, x28, x21
add x28, x28, x22
add x28, x28, x23
add x28, x28, x24
add x28, x28, x25
add x28, x28, x26
add x28, x28, x27
str x28, [x29, #-168]
b label14
label13:
label14:
ldr x28, [x29, #-168]
mov x0, x28
ldr x24, [x29, #-8]
ldr x23, [x29, #-16]
ldr x22, [x29, #-24]
ldr x28, [x29, #-32]
ldr x26, [x29, #-40]
ldr x21, [x29, #-48]
ldr x25, [x29, #-56]
ldr x20, [x29, #-64]
ldr x27, [x29, #-72]
ldr x19, [x29, #-80]
ldp x29, x30, [sp, #176]
add sp, sp, #192
ret
_AlternatingSum__I__I__I__I__I__I:
label15:
sub sp, sp, #128
stp x29, x30, [sp, #112]
add x29, sp, #112
str x28, [x29, #-8]
str x27, [x29, #-16]
str x26, [x29, #-24]
str x25, [x29, #-32]
str x24, [x29, #-40]
str x23, [x29, #-48]
mov x23, x0
mov x24, x1
mov x25, x2
mov x26, x3
mov x27, x4
mov x28, x5
str x23, [x29, #-56]
str x24, [x29, #-64]
str x25, [x29, #-72]
str x26, [x29, #-80]
str x27, [x29, #-88]
str x28, [x29, #-96]
ldr x28, [x29, #-56]
ldr x25, [x29, #-64]
ldr x26, [x29, #-72]
ldr x23, [x29, #-80]
ldr x24, [x29, #-88]
ldr x27, [x29, #-96]
sub x28, x28, x25
add x28, x28, x26
sub x28, x28, x23
add x28, x28, x24
sub x28, x28, x27
str x28, [x29, #-104]
b label17
label16:
label17:
ldr x28, [x29, #-104]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldr x26, [x29, #-24]
ldr x25, [x29, #-32]
ldr x24, [x29, #-40]
ldr x23, [x29, #-48]
ldp x29, x30, [sp, #112]
add sp, sp, #128
ret
_AddFloats__F__F:
label18:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
fmov d29, d0
fmov d30, d1
str d29, [x29, #-8]
str d30, [x29, #-16]
ldr d29, [x29, #-8]
ldr d30, [x29, #-16]
fadd d30, d29, d30
str d30, [x29, #-24]
b label20
label19:
label20:
ldr d30, [x29, #-24]
fmov d0, d30
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_AddIntAndFloat__I__F__F:
label21:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
mov x28, x0
fmov d29, d1
fmov d30, d2
str x28, [x29, #-24]
str d29, [x29, #-32]
str d30, [x29, #-40]
ldr x28, [x29, #-24]
ldr d28, [x29, #-32]
ldr d29, [x29, #-40]
scvtf d30, x28
fadd d30, d30, d28
fadd d30, d30, d29
str d30, [x29, #-48]
b label23
label22:
label23:
ldr d30, [x29, #-48]
fmov d0, d30
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_ConditionSum__F__F__F__F__B:
label24:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x28, [x29, #-8]
fmov d27, d0
fmov d28, d1
fmov d29, d2
fmov d30, d3
mov w28, w4
str d27, [x29, #-24]
str d28, [x29, #-32]
str d29, [x29, #-40]
str d30, [x29, #-48]
strb w28, [x29, #-49]
ldrb w28, [x29, #-49]
ldr d27, [x29, #-24]
ldr d30, [x29, #-32]
ldr d28, [x29, #-40]
ldr d29, [x29, #-48]
fadd d30, d27, d30
fadd d29, d28, d29
tst w28, w28
fmov d29, d29
fcsel d29, d30, d29, ne
str d29, [x29, #-57]
b label26
label25:
label26:
ldr d30, [x29, #-57]
fmov d0, d30
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_AddBooleans__B__B__B__B:
label27:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x28, [x29, #-8]
str x27, [x29, #-16]
str x26, [x29, #-24]
str x25, [x29, #-32]
mov w25, w0
mov w26, w1
mov w27, w2
mov w28, w3
strb w25, [x29, #-33]
strb w26, [x29, #-34]
strb w27, [x29, #-35]
strb w28, [x29, #-36]
ldrb w25, [x29, #-33]
ldrb w28, [x29, #-34]
ldrb w26, [x29, #-35]
ldrb w27, [x29, #-36]
add w28, w25, w28
add w28, w28, w26
add w28, w28, w27
uxtb x28, w28
str x28, [x29, #-44]
b label29
label28:
label29:
ldr x28, [x29, #-44]
mov x0, x28
ldr x28, [x29, #-8]
ldr x27, [x29, #-16]
ldr x26, [x29, #-24]
ldr x25, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestIntCalls:
label30:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x1, #2
mov x0, #1
bl _Add__I__I
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
mov x2, #3
mov x1, #2
mov x0, #1
bl _AddThreeNumbers__I__I__I
mov x28, x0
cmp x28, #6
cset w28, eq
mov w0, w28
bl _Assert
mov x3, #4
mov x2, #3
mov x1, #2
mov x0, #1
bl _AddFourNumbers__I__I__I__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
mov x5, #6
mov x4, #5
mov x3, #4
mov x2, #3
mov x1, #2
mov x0, #1
bl _AddSixNumbers__I__I__I__I__I__I
mov x28, x0
cmp x28, #21
cset w28, eq
mov w0, w28
bl _Assert
mov x5, #6
mov x4, #5
mov x3, #4
mov x2, #3
mov x1, #2
mov x0, #1
bl _AlternatingSum__I__I__I__I__I__I
mov x27, x0
mov x28, #-3
cmp x27, x28
cset w28, eq
mov w0, w28
bl _Assert
b label31
label31:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestFloatCalls:
label32:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d1, x28
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d0, x28
bl _AddFloats__F__F
fmov d29, d0
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d30, x28
fcmp d29, d30
cset w28, eq
mov w0, w28
bl _Assert
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d2, x28
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d1, x28
mov x0, #1
bl _AddIntAndFloat__I__F__F
fmov d29, d0
adrp x28, _INT3@PAGE
ldr x28, [x28, _INT3@PAGEOFF]
fmov d30, x28
fcmp d29, d30
cset w28, eq
mov w0, w28
bl _Assert
mov w4, #1
adrp x28, _INT4@PAGE
ldr x28, [x28, _INT4@PAGEOFF]
fmov d3, x28
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d2, x28
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d1, x28
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d0, x28
bl _ConditionSum__F__F__F__F__B
fmov d30, d0
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d29, x28
fcmp d30, d29
cset w28, eq
mov w0, w28
bl _Assert
mov w4, #0
adrp x28, _INT4@PAGE
ldr x28, [x28, _INT4@PAGEOFF]
fmov d3, x28
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d2, x28
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d1, x28
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d0, x28
bl _ConditionSum__F__F__F__F__B
fmov d29, d0
adrp x28, _INT5@PAGE
ldr x28, [x28, _INT5@PAGEOFF]
fmov d30, x28
fcmp d29, d30
cset w28, eq
mov w0, w28
bl _Assert
mov x28, #10
str x28, [x29, #-24]
mov x28, #9
str x28, [x29, #-32]
mov x7, #8
mov x6, #7
mov x5, #6
mov x4, #5
mov x3, #4
mov x2, #3
mov x1, #2
mov x0, #1
bl _AddTenNumbers__I__I__I__I__I__I__I__I__I__I
mov x28, x0
cmp x28, #55
cset w28, eq
mov w0, w28
bl _Assert
b label33
label33:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestBoolCalls:
label34:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov w3, #0
mov w2, #1
mov w1, #0
mov w0, #1
bl _AddBooleans__B__B__B__B
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
b label35
label35:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _main
_main:
label36:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestIntCalls
bl _TestFloatCalls
bl _TestBoolCalls
mov x28, #0
str x28, [x29, #-24]
b label38
label37:
label38:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
