
.text

.extern _Assert
.extern _AssertMsg
_TestNestedDoWhileLoops:
label0:
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
b label1
label1:
mov x26, x27
b label5
label2:
cmp x24, #3
cset w23, lt
tst w23, w23
b.ne label3
b label4
label3:
mov x28, x24
mov x27, x25
b label1
label4:
cmp x24, #3
cset w27, eq
mov w0, w27
bl _Assert
cmp x25, #4
cset w27, eq
mov w0, w27
bl _Assert
b label9
label5:
str x26, [x29, #-64]
add x25, x26, #1
b label6
label6:
cmp x25, #2
cset w27, lt
tst w27, w27
b.ne label7
b label8
label7:
mov x26, x25
b label5
label8:
str x28, [x29, #-56]
add x24, x28, #1
b label2
label9:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label10:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestNestedDoWhileLoops
b label11
label11:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
