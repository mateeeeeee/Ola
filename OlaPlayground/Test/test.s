
.text

_test__I__I:
label0:
sub sp, sp, #128
stp x29, x30, [sp, #112]
add x29, sp, #112
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
mov x27, x1
add x26, x28, x27
cmp x26, #0
cset w26, gt
tst w26, w26
b.ne label1
b label2
label1:
add x26, x28, x27
add x25, x26, x26
mov x24, x25
mov x25, x26
b label3
label2:
add x25, x28, x27
mov x27, #3
mul x28, x25, x27
mov x24, x28
mov x28, x25
b label3
label3:
b label5
label4:
label5:
mov x0, x24
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #112]
add sp, sp, #128
ret
.globl _main
_main:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov x1, #20
mov x0, #10
bl _test__I__I
mov x28, x0
b label8
label7:
label8:
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
