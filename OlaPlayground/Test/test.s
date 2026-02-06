
.text

.extern _Assert
.extern _AssertMsg
_TestDoWhileLoopInt:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-40]
mov x28, #1
str x28, [x29, #-48]
b label1
label1:
ldr x28, [x29, #-40]
ldr x27, [x29, #-48]
add x26, x28, x27
str x26, [x29, #-40]
ldr x26, [x29, #-48]
str x26, [x29, #-56]
add x27, x26, #1
str x27, [x29, #-48]
b label2
label2:
ldr x27, [x29, #-48]
cmp x27, #5
cset w27, le
tst w27, w27
b.ne label1
b label3
label3:
ldr x27, [x29, #-40]
cmp x27, #15
cset w27, eq
mov w0, w27
bl _Assert
b label4
label4:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopBool:
label5:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
mov w28, #1
strb w28, [x29, #-17]
mov x28, #0
str x28, [x29, #-25]
b label6
label6:
ldr x28, [x29, #-25]
str x28, [x29, #-33]
add x27, x28, #1
str x27, [x29, #-25]
ldr x27, [x29, #-25]
cmp x27, #3
cset w27, eq
tst w27, w27
b.ne label9
b label11
label7:
ldrb w27, [x29, #-17]
tst w27, w27
b.ne label6
b label8
label8:
ldr x27, [x29, #-25]
cmp x27, #3
cset w27, eq
mov w0, w27
bl _Assert
b label12
label9:
mov w27, #0
strb w27, [x29, #-17]
b label11
label10:
label11:
b label7
label12:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestNestedDoWhileLoops:
label13:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #0
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-32]
b label14
label14:
b label17
label15:
ldr x28, [x29, #-24]
cmp x28, #3
cset w28, lt
tst w28, w28
b.ne label14
b label16
label16:
ldr x28, [x29, #-24]
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x29, #-32]
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
b label20
label17:
ldr x28, [x29, #-32]
str x28, [x29, #-40]
add x27, x28, #1
str x27, [x29, #-32]
b label18
label18:
ldr x27, [x29, #-32]
cmp x27, #2
cset w27, lt
tst w27, w27
b.ne label17
b label19
label19:
ldr x27, [x29, #-24]
str x27, [x29, #-48]
add x28, x27, #1
str x28, [x29, #-24]
b label15
label20:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDoWhileLoopWithBreak:
label21:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-40]
mov x28, #1
str x28, [x29, #-48]
b label22
label22:
ldr x28, [x29, #-40]
ldr x27, [x29, #-48]
add x26, x28, x27
str x26, [x29, #-40]
ldr x26, [x29, #-48]
str x26, [x29, #-56]
add x27, x26, #1
str x27, [x29, #-48]
ldr x27, [x29, #-48]
cmp x27, #5
cset w27, gt
tst w27, w27
b.ne label25
b label27
label23:
b label22
label24:
ldr x27, [x29, #-40]
cmp x27, #15
cset w27, eq
mov w0, w27
bl _Assert
b label29
label25:
b label24
label26:
label27:
b label23
label28:
label29:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopWithContinue:
label30:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #0
str x28, [x29, #-40]
mov x28, #0
str x28, [x29, #-48]
b label31
label31:
ldr x28, [x29, #-48]
str x28, [x29, #-56]
add x27, x28, #1
str x27, [x29, #-48]
ldr x27, [x29, #-48]
mov x28, #2
sdiv x26, x27, x28
msub x25, x26, x28, x27
cmp x25, #0
cset w25, eq
tst w25, w25
b.ne label34
b label36
label32:
ldr x25, [x29, #-48]
cmp x25, #5
cset w25, lt
tst w25, w25
b.ne label31
b label33
label33:
ldr x25, [x29, #-40]
cmp x25, #9
cset w25, eq
mov w0, w25
bl _Assert
b label38
label34:
b label32
label35:
label36:
ldr x25, [x29, #-40]
ldr x26, [x29, #-48]
add x28, x25, x26
str x28, [x29, #-40]
b label32
label37:
label38:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestEmptyDoWhileLoop:
label39:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #0
str x28, [x29, #-24]
b label40
label40:
b label41
label41:
ldr x28, [x29, #-24]
add x27, x28, #1
str x27, [x29, #-24]
cmp x27, #2
cset w27, lt
tst w27, w27
b.ne label40
b label42
label42:
ldr x27, [x29, #-24]
cmp x27, #2
cset w27, eq
mov w0, w27
bl _Assert
b label43
label43:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestDoWhileLoopBoundary:
label44:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #5
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-32]
b label45
label45:
ldr x28, [x29, #-32]
str x28, [x29, #-40]
add x27, x28, #1
str x27, [x29, #-32]
b label46
label46:
ldr x27, [x29, #-24]
cmp x27, #5
cset w27, lt
tst w27, w27
b.ne label45
b label47
label47:
ldr x27, [x29, #-32]
cmp x27, #1
cset w27, eq
mov w0, w27
bl _Assert
b label48
label48:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDoWhileLoopWithMultipleVariables:
label49:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #1
str x28, [x29, #-40]
mov x28, #1
str x28, [x29, #-48]
b label50
label50:
ldr x28, [x29, #-40]
str x28, [x29, #-56]
ldr x28, [x29, #-48]
str x28, [x29, #-40]
ldr x28, [x29, #-56]
ldr x27, [x29, #-48]
add x26, x28, x27
str x26, [x29, #-48]
b label51
label51:
ldr x26, [x29, #-48]
cmp x26, #10
cset w26, lt
tst w26, w26
b.ne label50
b label52
label52:
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
cmp x26, #8
cset w26, eq
cmp x27, #13
cset w27, eq
and w28, w26, w27
cmp w28, #0
cset w28, ne
mov w0, w28
bl _Assert
b label53
label53:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopComplexCondition:
label54:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-40]
mov x28, #3
str x28, [x29, #-48]
b label55
label55:
ldr x28, [x29, #-40]
str x28, [x29, #-56]
add x27, x28, #1
str x27, [x29, #-40]
ldr x27, [x29, #-48]
str x27, [x29, #-64]
sub x28, x27, #1
str x28, [x29, #-48]
b label56
label56:
ldr x28, [x29, #-40]
ldr x27, [x29, #-48]
cmp x28, #3
cset w28, lt
cmp x27, #0
cset w27, gt
and w26, w28, w27
cmp w26, #0
cset w26, ne
tst w26, w26
b.ne label55
b label57
label57:
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
cmp x26, #3
cset w26, eq
cmp x27, #0
cset w27, eq
and w28, w26, w27
cmp w28, #0
cset w28, ne
mov w0, w28
bl _Assert
b label58
label58:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopChangingCondition:
label59:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
str x28, [x29, #-40]
mov x28, #0
str x28, [x29, #-48]
b label60
label60:
ldr x28, [x29, #-40]
str x28, [x29, #-56]
add x27, x28, #1
str x27, [x29, #-40]
ldr x27, [x29, #-40]
cmp x27, #3
cset w27, eq
tst w27, w27
b.ne label63
b label65
label61:
ldr x27, [x29, #-40]
cmp x27, #5
cset w27, lt
tst w27, w27
b.ne label60
b label62
label62:
ldr x27, [x29, #-48]
cmp x27, #13
cset w27, eq
mov w0, w27
bl _Assert
b label66
label63:
mov x27, #10
str x27, [x29, #-40]
b label65
label64:
label65:
ldr x27, [x29, #-48]
ldr x28, [x29, #-40]
add x26, x27, x28
str x26, [x29, #-48]
b label61
label66:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopMultipleExits:
label67:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #0
str x28, [x29, #-24]
mov w28, #0
strb w28, [x29, #-25]
b label68
label68:
ldr x28, [x29, #-24]
str x28, [x29, #-33]
add x27, x28, #1
str x27, [x29, #-24]
ldr x27, [x29, #-24]
cmp x27, #5
cset w27, eq
tst w27, w27
b.ne label71
b label73
label69:
b label68
label70:
ldr x27, [x29, #-24]
cmp x27, #5
cset w27, eq
mov w0, w27
bl _Assert
ldrb w27, [x29, #-25]
mov w0, w27
bl _Assert
b label79
label71:
mov w27, #1
strb w27, [x29, #-25]
b label70
label72:
label73:
ldr x27, [x29, #-24]
cmp x27, #10
cset w27, gt
tst w27, w27
b.ne label75
b label77
label74:
label75:
b label70
label76:
label77:
b label69
label78:
label79:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label80:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestDoWhileLoopInt
bl _TestDoWhileLoopBool
bl _TestNestedDoWhileLoops
bl _TestDoWhileLoopWithBreak
bl _TestDoWhileLoopWithContinue
bl _TestEmptyDoWhileLoop
bl _TestDoWhileLoopBoundary
bl _TestDoWhileLoopWithMultipleVariables
bl _TestDoWhileLoopComplexCondition
bl _TestDoWhileLoopChangingCondition
bl _TestDoWhileLoopMultipleExits
mov x28, #0
str x28, [x29, #-24]
b label82
label81:
label82:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
