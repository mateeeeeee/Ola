
.text

.extern _Assert
.extern _AssertMsg
_TestDoWhileLoopWithMultipleVariables:
label0:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, #1
mov x27, #1
b label1
label1:
add x26, x27, x28
b label2
label2:
cmp x26, #10
cset w25, lt
tst w25, w25
b.eq label3
mov x25, x28
mov x24, x27
mov x23, x24
mov x28, x26
mov x27, x25
b label1
label3:
cmp x28, #8
cset w27, eq
cmp x26, #13
cset w26, eq
and w28, w27, w26
cmp w28, #0
cset w28, ne
mov w0, w28
bl _Assert
b label4
label4:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
.globl _main
_main:
label5:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
bl _TestDoWhileLoopWithMultipleVariables
b label7
label6:
label7:
mov x0, #0
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
