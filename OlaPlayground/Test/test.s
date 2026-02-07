
.const

_INT0:
.quad 4591870180066957722


_INT1:
.quad 4607092346807469998


_INT2:
.quad 4616741309009111286


_INT3:
.quad 4616763827007248138


.text

.extern _Assert
.extern _AssertMsg
_TestWhileLoopInt:
label0:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #1
mov x27, #0
b label1
label1:
cmp x28, #5
cset w26, le
tst w26, w26
b.ne label2
b label3
label2:
add x26, x27, x28
str x28, [x29, #-40]
add x25, x28, #1
mov x28, x25
mov x27, x26
b label1
label3:
cmp x27, #15
cset w27, eq
mov w0, w27
bl _Assert
b label4
label4:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestWhileLoopBool:
label5:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, #0
mov w27, #1
b label6
label6:
tst w27, w27
b.ne label7
b label9
label7:
str x28, [x29, #-56]
add x26, x28, #1
cmp x26, #3
cset w25, eq
tst w25, w25
b.ne label10
b label8
label8:
mov w25, w27
b label11
label9:
cmp x28, #3
cset w24, eq
mov w0, w24
bl _Assert
b label12
label10:
mov w25, #0
b label11
label11:
mov x28, x26
mov w27, w25
b label6
label12:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestNestedWhileLoops:
label13:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #0
mov x27, #0
b label14
label14:
cmp x27, #3
cset w26, lt
tst w26, w26
b.ne label15
b label16
label15:
mov x26, x28
b label17
label16:
cmp x27, #3
cset w25, eq
mov w0, w25
bl _Assert
cmp x28, #2
cset w25, eq
mov w0, w25
bl _Assert
b label20
label17:
cmp x26, #2
cset w25, lt
tst w25, w25
b.ne label18
b label19
label18:
str x26, [x29, #-40]
add x25, x26, #1
mov x26, x25
b label17
label19:
str x27, [x29, #-48]
add x25, x27, #1
mov x28, x26
mov x27, x25
b label14
label20:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestWhileLoopWithBreak:
label21:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, #1
mov x27, #0
b label22
label22:
b label23
label23:
add x26, x27, x28
str x28, [x29, #-56]
add x25, x28, #1
cmp x25, #5
cset w24, le
tst w24, w24
b.ne label25
b label24
label24:
cmp x26, #15
cset w24, eq
mov w0, w24
bl _Assert
b label26
label25:
mov x28, x25
mov x27, x26
b label22
label26:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestWhileLoopWithContinue:
label27:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x21, [x29, #-8]
str x22, [x29, #-16]
str x23, [x29, #-24]
str x24, [x29, #-32]
str x25, [x29, #-40]
str x26, [x29, #-48]
str x27, [x29, #-56]
str x28, [x29, #-64]
mov x26, #0
mov x25, #0
b label28
label28:
cmp x26, #5
cset w24, lt
tst w24, w24
b.ne label29
b label31
label29:
str x26, [x29, #-72]
add x24, x26, #1
mov x23, #2
sdiv x22, x24, x23
msub x21, x22, x23, x24
cmp x21, #0
cset w21, eq
tst w21, w21
b.ne label32
b label30
label30:
b label33
label31:
cmp x25, #9
cset w21, eq
mov w0, w21
bl _Assert
b label34
label32:
add x21, x25, x24
b label33
label33:
mov x26, x27
mov x25, x28
b label28
label34:
ldr x21, [x29, #-8]
ldr x22, [x29, #-16]
ldr x23, [x29, #-24]
ldr x24, [x29, #-32]
ldr x25, [x29, #-40]
ldr x26, [x29, #-48]
ldr x27, [x29, #-56]
ldr x28, [x29, #-64]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_TestWhileLoopMultipleExits:
label35:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov w28, #0
mov x27, #0
b label36
label36:
cmp x27, #5
cset w26, lt
cmp w28, #0
cset w25, eq
and w24, w26, w25
cmp w24, #0
cset w24, ne
tst w24, w24
b.ne label37
b label39
label37:
str x27, [x29, #-56]
add x24, x27, #1
cmp x24, #3
cset w25, eq
tst w25, w25
b.ne label40
b label38
label38:
mov w25, w28
b label41
label39:
cmp x27, #3
cset w26, eq
mov w0, w26
bl _Assert
mov w0, w28
bl _Assert
b label42
label40:
mov w25, #1
b label41
label41:
mov w28, w25
mov x27, x24
b label36
label42:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestWhileLoopExternalDeclaration:
label43:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #0
mov x27, #0
b label44
label44:
cmp x27, #5
cset w26, lt
tst w26, w26
b.ne label45
b label46
label45:
add x26, x28, x27
str x27, [x29, #-40]
add x25, x27, #1
mov x28, x26
mov x27, x25
b label44
label46:
cmp x28, #10
cset w27, eq
mov w0, w27
bl _Assert
b label47
label47:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestWhileLoopWithCalculation:
label48:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #0
mov x27, #10
b label49
label49:
cmp x27, #0
cset w26, gt
tst w26, w26
b.ne label50
b label51
label50:
sub x26, x27, #2
str x28, [x29, #-40]
add x25, x28, #1
mov x28, x25
mov x27, x26
b label49
label51:
cmp x28, #5
cset w27, eq
mov w0, w27
bl _Assert
b label52
label52:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestWhileLoopFloatCondition:
label53:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
str d26, [x29, #-32]
str d27, [x29, #-40]
str d28, [x29, #-48]
str d29, [x29, #-56]
str d30, [x29, #-64]
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d30, x28
mov x28, #0
fmov d29, x28
b label54
label54:
adrp x28, _INT1@PAGE
ldr x28, [x28, _INT1@PAGEOFF]
fmov d28, x28
fcmp d30, d28
cset w28, lt
tst w28, w28
b.ne label55
b label56
label55:
fadd d28, d29, d30
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d27, x28
fadd d26, d30, d27
fmov d30, d26
fmov d29, d28
b label54
label56:
adrp x28, _INT2@PAGE
ldr x28, [x28, _INT2@PAGEOFF]
fmov d30, x28
fcmp d29, d30
cset w28, gt
adrp x27, _INT3@PAGE
ldr x27, [x27, _INT3@PAGEOFF]
fmov d30, x27
fcmp d29, d30
cset w27, lt
and w26, w28, w27
cmp w26, #0
cset w26, ne
mov w0, w26
bl _Assert
b label57
label57:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldr d26, [x29, #-32]
ldr d27, [x29, #-40]
ldr d28, [x29, #-48]
ldr d29, [x29, #-56]
ldr d30, [x29, #-64]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label58:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestWhileLoopInt
bl _TestWhileLoopBool
bl _TestNestedWhileLoops
bl _TestWhileLoopWithBreak
bl _TestWhileLoopWithContinue
bl _TestWhileLoopMultipleExits
bl _TestWhileLoopExternalDeclaration
bl _TestWhileLoopWithCalculation
bl _TestWhileLoopFloatCondition
b label59
label59:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
