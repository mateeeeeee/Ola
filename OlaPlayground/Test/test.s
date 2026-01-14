
.text

.extern _Assert
.extern _AssertMsg
_TestDoWhileLoopInt:
label0:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, #0
mov x27, #1
b label1
label1:
add x26, x28, x27
str x27, [x29, #-56]
add x25, x27, #1
b label2
label2:
cmp x25, #5
cset w24, le
tst w24, w24
mov x28, x26
mov x27, x25
b.ne label1
b label3
label3:
cmp x26, #15
cset w26, eq
mov w0, w26
bl _Assert
b label4
label4:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopBool:
label5:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov w28, #1
mov x27, #0
b label6
label6:
str x27, [x29, #-56]
add x26, x27, #1
cmp x26, #3
cset w25, eq
tst w25, w25
b.ne label9
mov w24, w28
b label10
label7:
tst w24, w24
mov w28, w24
mov x27, x26
b.ne label6
b label8
label8:
mov w0, w25
bl _Assert
b label11
label9:
mov w24, #0
b label10
label10:
b label7
label11:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestNestedDoWhileLoops:
label12:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, #0
mov x27, #0
b label13
label13:
mov x26, x27
b label16
label14:
cmp x25, #3
cset w24, lt
tst w24, w24
mov x28, x25
mov x27, x24
b.ne label13
b label15
label15:
cmp x25, #3
cset w27, eq
mov w0, w27
bl _Assert
cmp x24, #4
cset w27, eq
mov w0, w27
bl _Assert
b label19
label16:
str x26, [x29, #-64]
add x24, x26, #1
b label17
label17:
cmp x24, #2
cset w27, lt
tst w27, w27
mov x26, x24
b.ne label16
b label18
label18:
str x28, [x29, #-56]
add x25, x28, #1
b label14
label19:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopWithBreak:
label20:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, #0
mov x27, #1
b label21
label21:
add x26, x28, x27
str x27, [x29, #-56]
add x25, x27, #1
cmp x25, #5
cset w24, gt
tst w24, w24
b.ne label23
b label22
label22:
mov x28, x26
mov x27, x25
b label21
label23:
cmp x26, #15
cset w26, eq
mov w0, w26
bl _Assert
b label24
label24:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopWithContinue:
label25:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, #0
mov x27, #0
b label26
label26:
str x27, [x29, #-56]
add x26, x27, #1
mov x25, #2
sdiv x24, x26, x25
msub x23, x24, x25, x26
cmp x23, #0
cset w23, eq
tst w23, w23
b.ne label29
b label30
label27:
cmp x26, #5
cset w23, lt
tst w23, w23
mov x28, x23
mov x27, x26
b.ne label26
b label28
label28:
cmp x23, #9
cset w27, eq
mov w0, w27
bl _Assert
b label31
label29:
mov x23, x28
b label27
label30:
add x27, x28, x26
mov x23, x27
b label27
label31:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestEmptyDoWhileLoop:
label32:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
b label33
label33:
b label34
label34:
add x27, x28, #1
cmp x27, #2
cset w26, lt
tst w26, w26
mov x28, x27
b.ne label33
b label35
label35:
cmp x27, #2
cset w27, eq
mov w0, w27
bl _Assert
b label36
label36:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestDoWhileLoopBoundary:
label37:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, #0
b label38
label38:
str x28, [x29, #-24]
add x27, x28, #1
b label39
label39:
cmp x27, #1
cset w27, eq
mov w0, w27
bl _Assert
b label40
label40:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestDoWhileLoopWithMultipleVariables:
label41:
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
b label42
label42:
ldr x28, [x29, #-40]
str x28, [x29, #-56]
ldr x28, [x29, #-48]
str x28, [x29, #-40]
ldr x28, [x29, #-56]
ldr x27, [x29, #-48]
add x26, x28, x27
str x26, [x29, #-48]
b label43
label43:
ldr x26, [x29, #-48]
cmp x26, #10
cset w26, lt
tst w26, w26
b.ne label42
b label44
label44:
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
b label45
label45:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestDoWhileLoopComplexCondition:
label46:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x22, [x29, #-8]
str x23, [x29, #-16]
str x24, [x29, #-24]
str x25, [x29, #-32]
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
mov x28, #0
mov x27, #3
b label47
label47:
str x28, [x29, #-72]
add x26, x28, #1
str x27, [x29, #-80]
sub x25, x27, #1
b label48
label48:
cmp x26, #3
cset w24, lt
cmp x25, #0
cset w23, gt
and w22, w24, w23
cmp w22, #0
cset w22, ne
tst w22, w22
mov x28, x26
mov x27, x25
b.ne label47
b label49
label49:
cmp x26, #3
cset w26, eq
cmp x25, #0
cset w25, eq
and w27, w26, w25
cmp w27, #0
cset w27, ne
mov w0, w27
bl _Assert
b label50
label50:
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_TestDoWhileLoopChangingCondition:
label51:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, #0
mov x27, #0
b label52
label52:
str x28, [x29, #-40]
add x26, x28, #1
cmp x26, #3
cset w25, eq
tst w25, w25
b.ne label55
mov x25, x26
b label56
label53:
cmp x25, #5
cset w26, lt
tst w26, w26
mov x28, x25
mov x27, x28
b.ne label52
b label54
label54:
cmp x28, #13
cset w26, eq
mov w0, w26
bl _Assert
b label57
label55:
mov x25, #10
b label56
label56:
add x28, x27, x25
b label53
label57:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDoWhileLoopMultipleExits:
label58:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, #0
b label59
label59:
str x28, [x29, #-40]
add x27, x28, #1
cmp x27, #5
cset w26, eq
tst w26, w26
b.ne label62
b label63
label60:
mov x28, x27
b label59
label61:
mov w0, w26
bl _Assert
mov w0, w26
bl _Assert
b label65
label62:
mov w26, #1
b label61
label63:
cmp x27, #10
cset w27, gt
tst w27, w27
b.ne label64
b label60
label64:
mov w26, #0
b label61
label65:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label66:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
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
b label67
label67:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
