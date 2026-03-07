
.text

.extern _Assert
.extern _AssertMsg
.globl _Stack.int.$Stack
_Stack.int.$Stack:
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
mov x28, #0
str x28, [x27]
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Stack.int.$Size
_Stack.int.$Size:
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
.globl _Stack.int.$Empty
_Stack.int.$Empty:
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
.globl _Stack.int.$Top
_Stack.int.$Top:
label8:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
add x27, x28, #8
ldr x26, [x27]
add x27, x28, #0
ldr x28, [x27]
sub x27, x26, #1
mov x26, #8
mul x25, x27, x26
add x26, x28, x25
ldr x25, [x26]
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
.globl _Stack.int.$Push__I
_Stack.int.$Push__I:
label11:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x22, [x29, #-8]
str x23, [x29, #-16]
str x24, [x29, #-24]
str x25, [x29, #-32]
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
mov x28, x0
mov x27, x1
str x27, [x29, #-72]
add x27, x28, #8
ldr x26, [x27]
add x27, x28, #16
ldr x25, [x27]
cmp x26, x25
cset w25, lt
tst w25, w25
b.ne label12
b label15
label12:
add x25, x28, #8
ldr x26, [x25]
add x25, x28, #0
ldr x27, [x25]
ldr x25, [x29, #-72]
mov x24, #8
mul x23, x26, x24
add x24, x27, x23
str x25, [x24]
add x24, x28, #8
ldr x25, [x24]
add x24, x25, #1
add x25, x28, #8
str x24, [x25]
b label23
label13:
label14:
label15:
add x25, x28, #16
ldr x24, [x25]
add x25, x28, #16
ldr x23, [x25]
cmp x24, #0
cset w24, gt
mov x25, #2
mul x27, x23, x25
tst w24, w24
mov x24, #4
csel x24, x27, x24, ne
str x24, [x29, #-80]
ldr x24, [x29, #-80]
mov x27, #8
mul x25, x24, x27
mov x0, x25
bl ___ola_new
mov x25, x0
str x25, [x29, #-88]
mov x25, #0
str x25, [x29, #-96]
b label17
label16:
ldr x25, [x29, #-96]
ldr x27, [x29, #-88]
ldr x24, [x29, #-96]
add x23, x28, #0
ldr x26, [x23]
mov x23, #8
mul x22, x24, x23
add x23, x26, x22
ldr x22, [x23]
mov x23, #8
mul x26, x25, x23
add x23, x27, x26
str x22, [x23]
b label18
label17:
ldr x23, [x29, #-96]
add x22, x28, #8
ldr x26, [x22]
cmp x23, x26
cset w26, lt
tst w26, w26
b.ne label16
b label19
label18:
ldr x26, [x29, #-96]
add x23, x26, #1
str x23, [x29, #-96]
b label17
label19:
add x23, x28, #8
ldr x26, [x23]
ldr x23, [x29, #-88]
ldr x22, [x29, #-72]
mov x27, #8
mul x25, x26, x27
add x27, x23, x25
str x22, [x27]
add x27, x28, #0
ldr x22, [x27]
cmp x22, #0
cset w22, ne
tst w22, w22
b.ne label20
b label22
label20:
add x22, x28, #0
ldr x27, [x22]
mov x0, x27
bl ___ola_delete
b label22
label21:
label22:
ldr x27, [x29, #-88]
add x22, x28, #0
str x27, [x22]
ldr x22, [x29, #-80]
add x27, x28, #16
str x22, [x27]
add x27, x28, #8
ldr x22, [x27]
add x27, x22, #1
add x22, x28, #8
str x27, [x22]
b label23
label23:
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.extern ___ola_new
.extern ___ola_delete
.globl _Stack.int.$Pop
_Stack.int.$Pop:
label24:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
add x27, x28, #8
ldr x26, [x27]
sub x27, x26, #1
add x26, x28, #8
str x27, [x26]
b label25
label25:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Stack.int.$Clear
_Stack.int.$Clear:
label26:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
mov x28, #0
str x28, [x27]
b label27
label27:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestPushTop:
label28:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #40
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x0, x29, #40
bl _Stack.int.$Stack
sub x0, x29, #40
bl _Stack.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #20
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #30
sub x0, x29, #40
bl _Stack.int.$Push__I
sub x0, x29, #40
bl _Stack.int.$Size
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #30
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Clear
b label29
label29:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestPop:
label30:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #40
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x0, x29, #40
bl _Stack.int.$Stack
mov x1, #1
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #2
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #3
sub x0, x29, #40
bl _Stack.int.$Push__I
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Size
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
b label31
label31:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestLIFO:
label32:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #40
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #40
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x0, x29, #40
bl _Stack.int.$Stack
mov x1, #100
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #200
sub x0, x29, #40
bl _Stack.int.$Push__I
mov x1, #300
sub x0, x29, #40
bl _Stack.int.$Push__I
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #300
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #200
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Top
mov x28, x0
cmp x28, #100
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #40
bl _Stack.int.$Pop
sub x0, x29, #40
bl _Stack.int.$Empty
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
.globl _main
_main:
label34:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestPushTop
bl _TestPop
bl _TestLIFO
mov x28, #0
str x28, [x29, #-24]
b label36
label35:
label36:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
