
.text

.extern _Assert
.extern _AssertMsg
.globl _Queue.int.$Queue
_Queue.int.$Queue:
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
mov x26, #0
str x26, [x27]
add x26, x28, #24
mov x28, #0
str x28, [x26]
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Queue.int.$Size
_Queue.int.$Size:
label2:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label4
label3:
label4:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Queue.int.$Empty
_Queue.int.$Empty:
label5:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
cmp x28, #0
cset w28, eq
strb w28, [x29, #-17]
b label7
label6:
label7:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Queue.int.$Front
_Queue.int.$Front:
label8:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
add x27, x28, #24
ldr x26, [x27]
add x27, x28, #0
ldr x28, [x27]
mov x27, #8
mul x25, x26, x27
add x27, x28, x25
ldr x25, [x27]
str x25, [x29, #-40]
b label10
label9:
label10:
ldr x25, [x29, #-40]
mov x0, x25
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Queue.int.$Back
_Queue.int.$Back:
label11:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
add x27, x28, #24
ldr x26, [x27]
add x27, x28, #8
ldr x25, [x27]
add x27, x28, #16
ldr x24, [x27]
add x27, x28, #0
ldr x28, [x27]
add x27, x26, x25
sub x25, x27, #1
sdiv x27, x25, x24
msub x26, x27, x24, x25
mov x27, #8
mul x25, x26, x27
add x27, x28, x25
ldr x25, [x27]
str x25, [x29, #-56]
b label13
label12:
label13:
ldr x25, [x29, #-56]
mov x0, x25
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _Queue.int.$Push__I
_Queue.int.$Push__I:
label14:
sub sp, sp, #128
stp x29, x30, [sp, #112]
add x29, sp, #112
str x21, [x29, #-8]
str x22, [x29, #-16]
str x23, [x29, #-24]
str x24, [x29, #-32]
str x25, [x29, #-40]
str x26, [x29, #-48]
str x27, [x29, #-56]
str x28, [x29, #-64]
mov x28, x0
mov x27, x1
str x27, [x29, #-72]
add x27, x28, #8
ldr x26, [x27]
add x27, x28, #16
ldr x25, [x27]
cmp x26, x25
cset w25, eq
tst w25, w25
b.ne label15
b label17
label15:
add x25, x28, #16
ldr x26, [x25]
add x25, x28, #16
ldr x27, [x25]
cmp x26, #0
cset w26, gt
mov x25, #2
mul x24, x27, x25
tst w26, w26
mov x26, #4
csel x26, x24, x26, ne
str x26, [x29, #-80]
ldr x26, [x29, #-80]
mov x24, #8
mul x25, x26, x24
mov x0, x25
bl ___ola_new
mov x25, x0
str x25, [x29, #-88]
mov x25, #0
str x25, [x29, #-96]
b label19
label16:
label17:
add x25, x28, #24
ldr x24, [x25]
add x25, x28, #8
ldr x26, [x25]
add x25, x28, #16
ldr x27, [x25]
add x25, x24, x26
sdiv x26, x25, x27
msub x24, x26, x27, x25
str x24, [x29, #-104]
ldr x24, [x29, #-104]
add x26, x28, #0
ldr x25, [x26]
ldr x26, [x29, #-72]
mov x27, #8
mul x23, x24, x27
add x27, x25, x23
str x26, [x27]
add x27, x28, #8
ldr x26, [x27]
add x27, x26, #1
add x26, x28, #8
str x27, [x26]
b label25
label18:
ldr x26, [x29, #-96]
ldr x27, [x29, #-88]
add x23, x28, #24
ldr x25, [x23]
ldr x23, [x29, #-96]
add x24, x28, #16
ldr x22, [x24]
add x24, x28, #0
ldr x21, [x24]
add x24, x25, x23
sdiv x23, x24, x22
msub x25, x23, x22, x24
mov x23, #8
mul x24, x25, x23
add x23, x21, x24
ldr x24, [x23]
mov x23, #8
mul x21, x26, x23
add x23, x27, x21
str x24, [x23]
b label20
label19:
ldr x23, [x29, #-96]
add x24, x28, #8
ldr x21, [x24]
cmp x23, x21
cset w21, lt
tst w21, w21
b.ne label18
b label21
label20:
ldr x21, [x29, #-96]
add x23, x21, #1
str x23, [x29, #-96]
b label19
label21:
add x23, x28, #0
ldr x21, [x23]
cmp x21, #0
cset w21, ne
tst w21, w21
b.ne label22
b label24
label22:
add x21, x28, #0
ldr x23, [x21]
mov x0, x23
bl ___ola_delete
b label24
label23:
label24:
ldr x23, [x29, #-88]
add x21, x28, #0
str x23, [x21]
ldr x21, [x29, #-80]
add x23, x28, #16
str x21, [x23]
add x23, x28, #24
mov x21, #0
str x21, [x23]
b label17
label25:
ldr x21, [x29, #-8]
ldr x22, [x29, #-16]
ldr x23, [x29, #-24]
ldr x24, [x29, #-32]
ldr x25, [x29, #-40]
ldr x26, [x29, #-48]
ldr x27, [x29, #-56]
ldr x28, [x29, #-64]
ldp x29, x30, [sp, #112]
add sp, sp, #128
ret
.extern ___ola_new
.extern ___ola_delete
.globl _Queue.int.$Pop
_Queue.int.$Pop:
label26:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
add x27, x28, #24
ldr x26, [x27]
add x27, x28, #16
ldr x25, [x27]
add x27, x26, #1
sdiv x26, x27, x25
msub x24, x26, x25, x27
add x26, x28, #24
str x24, [x26]
add x26, x28, #8
ldr x24, [x26]
sub x26, x24, #1
add x24, x28, #8
str x26, [x24]
b label27
label27:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Queue.int.$Clear
_Queue.int.$Clear:
label28:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #8
mov x26, #0
str x26, [x27]
add x26, x28, #24
mov x28, #0
str x28, [x26]
b label29
label29:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestPushFront:
label30:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #48
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x0, x29, #48
bl _Queue.int.$Queue
sub x0, x29, #48
bl _Queue.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #20
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #30
sub x0, x29, #48
bl _Queue.int.$Push__I
sub x0, x29, #48
bl _Queue.int.$Size
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Back
mov x28, x0
cmp x28, #30
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Clear
b label31
label31:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestPop:
label32:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #48
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x0, x29, #48
bl _Queue.int.$Queue
mov x1, #1
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #2
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #3
sub x0, x29, #48
bl _Queue.int.$Push__I
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Size
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
b label33
label33:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestFIFO:
label34:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #48
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x0, x29, #48
bl _Queue.int.$Queue
mov x1, #100
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #200
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #300
sub x0, x29, #48
bl _Queue.int.$Push__I
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #100
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #200
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #300
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
b label35
label35:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestWrapAround:
label36:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #48
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #48
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x0, x29, #48
bl _Queue.int.$Queue
mov x1, #1
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #2
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #3
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #4
sub x0, x29, #48
bl _Queue.int.$Push__I
sub x0, x29, #48
bl _Queue.int.$Pop
sub x0, x29, #48
bl _Queue.int.$Pop
mov x1, #5
sub x0, x29, #48
bl _Queue.int.$Push__I
mov x1, #6
sub x0, x29, #48
bl _Queue.int.$Push__I
sub x0, x29, #48
bl _Queue.int.$Size
mov x28, x0
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Front
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Back
mov x28, x0
cmp x28, #6
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Queue.int.$Clear
b label37
label37:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _main
_main:
label38:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestPushFront
bl _TestPop
bl _TestFIFO
bl _TestWrapAround
mov x28, #0
str x28, [x29, #-24]
b label40
label39:
label40:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
