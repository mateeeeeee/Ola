
.text

.extern _Assert
.extern _AssertMsg
_SumArray__I5:
label0:
sub sp, sp, #160
stp x29, x30, [sp, #144]
add x29, sp, #144
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
ldr x27, [x28]
sub x26, x29, #136
add x25, x28, #8
ldr x24, [x25]
add x25, x26, #8
str x27, [x26]
add x27, x28, #16
ldr x23, [x27]
add x27, x26, #16
str x24, [x25]
add x25, x28, #24
ldr x24, [x25]
add x25, x26, #24
str x23, [x27]
add x27, x28, #32
ldr x28, [x27]
add x27, x26, #32
str x24, [x25]
str x28, [x27]
sub x27, x29, #136
sub x28, x29, #88
ldr x25, [x27]
add x24, x27, #8
ldr x26, [x24]
add x24, x28, #8
str x25, [x28]
add x25, x27, #16
ldr x23, [x25]
add x25, x28, #16
str x26, [x24]
add x24, x27, #24
ldr x26, [x24]
add x24, x28, #24
str x23, [x25]
add x25, x27, #32
ldr x27, [x25]
add x25, x28, #32
str x26, [x24]
str x27, [x25]
mov x25, #0
mov x27, #0
b label2
label1:
sub x24, x29, #88
mov x26, #40
mov x28, #0
mul x23, x28, x26
add x28, x24, x23
mov x23, #8
mul x24, x27, x23
add x23, x28, x24
ldr x24, [x23]
add x23, x25, x24
b label3
label2:
cmp x27, #5
cset w24, lt
tst w24, w24
b.ne label1
b label4
label3:
str x27, [x29, #-96]
add x24, x27, #1
mov x25, x23
mov x27, x24
b label2
label4:
mov x0, x25
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #144]
add sp, sp, #160
ret
_TestArrayPassByValue:
label5:
sub sp, sp, #224
stp x29, x30, [sp, #208]
add x29, sp, #208
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
sub x28, x29, #88
add x27, x28, #0
mov x28, #2
str x28, [x27]
sub x28, x29, #88
add x27, x28, #8
mov x28, #4
str x28, [x27]
sub x28, x29, #88
add x27, x28, #16
mov x28, #6
str x28, [x27]
sub x28, x29, #88
add x27, x28, #24
mov x28, #8
str x28, [x27]
sub x28, x29, #88
add x27, x28, #32
mov x28, #10
str x28, [x27]
sub x28, x29, #88
sub x27, x29, #128
ldr x26, [x28]
add x25, x28, #8
ldr x24, [x25]
add x25, x27, #8
str x26, [x27]
add x26, x28, #16
ldr x23, [x26]
add x26, x27, #16
str x24, [x25]
add x25, x28, #24
ldr x24, [x25]
add x25, x27, #24
str x23, [x26]
add x26, x28, #32
ldr x28, [x26]
add x26, x27, #32
str x24, [x25]
str x28, [x26]
mov x0, x27
bl _SumArray__I5
mov x27, x0
cmp x27, #30
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #152
add x26, x27, #0
mov x27, #1
str x27, [x26]
sub x27, x29, #152
add x28, x27, #8
mov x27, #2
str x27, [x28]
sub x27, x29, #152
add x28, x27, #16
mov x27, #3
str x27, [x28]
sub x27, x29, #152
sub x28, x29, #176
ldr x25, [x27]
add x24, x27, #8
ldr x23, [x24]
add x24, x28, #8
str x25, [x28]
add x25, x27, #16
ldr x27, [x25]
add x25, x28, #16
str x23, [x24]
str x27, [x25]
b label7
label6:
ldr x25, [x26]
cmp x25, #1
cset w25, eq
mov w0, w25
bl _Assert
b label8
label7:
mov x25, x28
sub x28, x29, #200
ldr x27, [x25]
add x24, x25, #8
ldr x23, [x24]
add x24, x28, #8
str x27, [x28]
add x27, x25, #16
ldr x25, [x27]
add x27, x28, #16
str x23, [x24]
str x25, [x27]
sub x27, x29, #200
add x25, x27, #0
mov x27, #999
str x27, [x25]
b label6
label8:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #208]
add sp, sp, #224
ret
_ZeroArray__I5ref:
label9:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
mov x27, #0
b label11
label10:
mov x26, #40
mov x25, #0
mul x24, x25, x26
add x25, x28, x24
mov x24, #8
mul x26, x27, x24
add x24, x25, x26
mov x26, #0
str x26, [x24]
b label12
label11:
cmp x27, #5
cset w26, lt
tst w26, w26
b.ne label10
b label13
label12:
str x27, [x29, #-56]
add x26, x27, #1
mov x27, x26
b label11
label13:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestArrayPassByRef:
label14:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
sub x28, x29, #88
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #88
add x27, x28, #8
mov x28, #2
str x28, [x27]
sub x28, x29, #88
add x27, x28, #16
mov x28, #3
str x28, [x27]
sub x28, x29, #88
add x27, x28, #24
mov x28, #4
str x28, [x27]
sub x28, x29, #88
add x27, x28, #32
mov x28, #5
str x28, [x27]
sub x0, x29, #88
bl _ZeroArray__I5ref
mov x28, #0
b label16
label15:
sub x27, x29, #88
mov x26, #40
mov x25, #0
mul x24, x25, x26
add x25, x27, x24
mov x24, #8
mul x27, x28, x24
add x24, x25, x27
ldr x27, [x24]
cmp x27, #0
cset w27, eq
mov w0, w27
bl _Assert
b label17
label16:
cmp x28, #5
cset w27, lt
tst w27, w27
b.ne label15
b label18
label17:
str x28, [x29, #-96]
add x27, x28, #1
mov x28, x27
b label16
label18:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
_ReverseArray__I5ref:
label19:
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
mov x28, x0
mov x27, #0
mov x26, #4
b label20
label20:
cmp x27, x26
cset w25, lt
tst w25, w25
b.ne label21
b label22
label21:
mov x25, #40
mov x24, #0
mul x23, x24, x25
add x24, x28, x23
mov x23, #8
mul x25, x27, x23
add x23, x24, x25
ldr x25, [x23]
mov x24, #40
mov x22, #0
mul x21, x22, x24
add x22, x28, x21
mov x21, #8
mul x24, x26, x21
add x21, x22, x24
ldr x24, [x21]
str x24, [x23]
str x25, [x21]
str x27, [x29, #-72]
add x21, x27, #1
str x26, [x29, #-80]
sub x25, x26, #1
mov x27, x21
mov x26, x25
b label20
label22:
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
_TestArrayReverse:
label23:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
sub x28, x29, #88
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #88
add x26, x28, #8
mov x28, #2
str x28, [x26]
sub x28, x29, #88
add x25, x28, #16
mov x28, #3
str x28, [x25]
sub x28, x29, #88
add x24, x28, #24
mov x28, #4
str x28, [x24]
sub x28, x29, #88
add x23, x28, #32
mov x28, #5
str x28, [x23]
sub x0, x29, #88
bl _ReverseArray__I5ref
ldr x28, [x27]
cmp x28, #5
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x26]
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x25]
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x24]
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
ldr x28, [x23]
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
b label24
label24:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
_TestArrayBubbleSort:
label25:
sub sp, sp, #192
stp x29, x30, [sp, #176]
add x29, sp, #176
str x19, [x29, #-8]
str x20, [x29, #-16]
str x21, [x29, #-24]
str x22, [x29, #-32]
str x23, [x29, #-40]
str x24, [x29, #-48]
str x25, [x29, #-56]
str x26, [x29, #-64]
str x27, [x29, #-72]
str x28, [x29, #-80]
sub x28, x29, #120
add x27, x28, #0
mov x28, #5
str x28, [x27]
sub x28, x29, #120
add x26, x28, #8
mov x28, #3
str x28, [x26]
sub x28, x29, #120
add x25, x28, #16
mov x28, #1
str x28, [x25]
sub x28, x29, #120
add x24, x28, #24
mov x28, #4
str x28, [x24]
sub x28, x29, #120
add x16, x28, #32
str x16, [x29, #-144]
mov x28, #2
ldr x16, [x29, #-144]
str x28, [x16]
mov x16, #0
str x16, [x29, #-152]
b label27
label26:
mov x22, #4
ldr x16, [x29, #-152]
sub x16, x22, x16
str x16, [x29, #-160]
mov x16, #0
str x16, [x29, #-168]
b label32
label27:
ldr x16, [x29, #-152]
cmp x16, #5
cset w20, lt
tst w20, w20
b.ne label26
b label29
label28:
ldr x16, [x29, #-152]
str x16, [x29, #-128]
ldr x16, [x29, #-152]
add x20, x16, #1
mov x16, x20
str x16, [x29, #-152]
b label27
label29:
ldr x20, [x27]
cmp x20, #1
cset w20, eq
mov w0, w20
bl _Assert
ldr x20, [x26]
cmp x20, #2
cset w20, eq
mov w0, w20
bl _Assert
ldr x20, [x25]
cmp x20, #3
cset w20, eq
mov w0, w20
bl _Assert
ldr x20, [x24]
cmp x20, #4
cset w20, eq
mov w0, w20
bl _Assert
ldr x16, [x29, #-144]
ldr x20, [x16]
cmp x20, #5
cset w20, eq
mov w0, w20
bl _Assert
b label35
label30:
sub x20, x29, #120
sub x19, x29, #120
mov x22, #40
mov x21, #0
mul x28, x21, x22
add x21, x20, x28
mov x28, #8
ldr x16, [x29, #-168]
mul x20, x16, x28
add x28, x21, x20
ldr x20, [x28]
mov x21, #40
mov x22, #0
mul x23, x22, x21
add x22, x19, x23
ldr x16, [x29, #-168]
add x23, x16, #1
mov x19, #8
mul x21, x23, x19
add x19, x22, x21
ldr x21, [x19]
cmp x20, x21
cset w21, gt
tst w21, w21
b.ne label34
b label31
label31:
b label33
label32:
ldr x16, [x29, #-168]
ldr x0, [x29, #-160]
cmp x16, x0
cset w21, lt
tst w21, w21
b.ne label30
b label28
label33:
ldr x16, [x29, #-168]
str x16, [x29, #-136]
mov x16, x23
str x16, [x29, #-168]
b label32
label34:
ldr x21, [x28]
ldr x20, [x19]
str x20, [x28]
str x21, [x19]
b label33
label35:
ldr x19, [x29, #-8]
ldr x20, [x29, #-16]
ldr x21, [x29, #-24]
ldr x22, [x29, #-32]
ldr x23, [x29, #-40]
ldr x24, [x29, #-48]
ldr x25, [x29, #-56]
ldr x26, [x29, #-64]
ldr x27, [x29, #-72]
ldr x28, [x29, #-80]
ldp x29, x30, [sp, #176]
add sp, sp, #192
ret
_TestArrayCountMatches:
label36:
sub sp, sp, #144
stp x29, x30, [sp, #128]
add x29, sp, #128
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
sub x28, x29, #112
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #112
add x27, x28, #8
mov x28, #3
str x28, [x27]
sub x28, x29, #112
add x27, x28, #16
mov x28, #5
str x28, [x27]
sub x28, x29, #112
add x27, x28, #24
mov x28, #3
str x28, [x27]
sub x28, x29, #112
add x27, x28, #32
mov x28, #7
str x28, [x27]
sub x28, x29, #112
add x27, x28, #40
mov x28, #3
str x28, [x27]
sub x28, x29, #112
add x27, x28, #48
mov x28, #9
str x28, [x27]
sub x28, x29, #112
add x27, x28, #56
mov x28, #3
str x28, [x27]
mov x28, #0
mov x27, #0
b label39
label37:
sub x26, x29, #112
mov x25, #64
mov x24, #0
mul x23, x24, x25
add x24, x26, x23
mov x23, #8
mul x26, x27, x23
add x23, x24, x26
ldr x26, [x23]
cmp x26, #3
cset w26, eq
tst w26, w26
b.ne label42
b label38
label38:
mov x26, x28
b label43
label39:
cmp x27, #8
cset w23, lt
tst w23, w23
b.ne label37
b label41
label40:
str x27, [x29, #-120]
add x23, x27, #1
mov x28, x26
mov x27, x23
b label39
label41:
cmp x28, #4
cset w23, eq
mov w0, w23
bl _Assert
b label44
label42:
str x28, [x29, #-128]
add x23, x28, #1
mov x26, x23
b label43
label43:
b label40
label44:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #128]
add sp, sp, #144
ret
_TestArrayPrefixSum:
label45:
sub sp, sp, #160
stp x29, x30, [sp, #144]
add x29, sp, #144
str x19, [x29, #-8]
str x20, [x29, #-16]
str x21, [x29, #-24]
str x22, [x29, #-32]
str x23, [x29, #-40]
str x24, [x29, #-48]
str x25, [x29, #-56]
str x26, [x29, #-64]
str x27, [x29, #-72]
str x28, [x29, #-80]
sub x28, x29, #120
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #120
add x26, x28, #8
mov x28, #2
str x28, [x26]
sub x28, x29, #120
add x25, x28, #16
mov x28, #3
str x28, [x25]
sub x28, x29, #120
add x16, x28, #24
str x16, [x29, #-136]
mov x28, #4
ldr x16, [x29, #-136]
str x28, [x16]
sub x28, x29, #120
add x16, x28, #32
str x16, [x29, #-144]
mov x28, #5
ldr x16, [x29, #-144]
str x28, [x16]
mov x28, #1
b label47
label46:
sub x22, x29, #120
mov x21, #40
mov x20, #0
mul x19, x20, x21
add x20, x22, x19
mov x19, #8
mul x22, x28, x19
add x19, x20, x22
sub x22, x29, #120
ldr x20, [x19]
mov x21, #40
mov x23, #0
mul x24, x23, x21
add x23, x22, x24
sub x24, x28, #1
mov x22, #8
mul x21, x24, x22
add x22, x23, x21
ldr x21, [x22]
add x22, x20, x21
str x22, [x19]
b label48
label47:
cmp x28, #5
cset w22, lt
tst w22, w22
b.ne label46
b label49
label48:
str x28, [x29, #-128]
add x22, x28, #1
mov x28, x22
b label47
label49:
ldr x22, [x27]
cmp x22, #1
cset w22, eq
mov w0, w22
bl _Assert
ldr x22, [x26]
cmp x22, #3
cset w22, eq
mov w0, w22
bl _Assert
ldr x22, [x25]
cmp x22, #6
cset w22, eq
mov w0, w22
bl _Assert
ldr x16, [x29, #-136]
ldr x22, [x16]
cmp x22, #10
cset w22, eq
mov w0, w22
bl _Assert
ldr x16, [x29, #-144]
ldr x22, [x16]
cmp x22, #15
cset w22, eq
mov w0, w22
bl _Assert
b label50
label50:
ldr x19, [x29, #-8]
ldr x20, [x29, #-16]
ldr x21, [x29, #-24]
ldr x22, [x29, #-32]
ldr x23, [x29, #-40]
ldr x24, [x29, #-48]
ldr x25, [x29, #-56]
ldr x26, [x29, #-64]
ldr x27, [x29, #-72]
ldr x28, [x29, #-80]
ldp x29, x30, [sp, #144]
add sp, sp, #160
ret
.globl _main
_main:
label51:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestArrayPassByValue
bl _TestArrayPassByRef
bl _TestArrayReverse
bl _TestArrayBubbleSort
bl _TestArrayCountMatches
bl _TestArrayPrefixSum
b label52
label52:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
