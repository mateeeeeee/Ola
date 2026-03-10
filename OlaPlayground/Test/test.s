
.text

.extern _Assert
.extern _AssertMsg
_Factorial__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
cmp x28, #1
cset w27, le
tst w27, w27
b.ne label1
b label2
label1:
mov x27, #1
b label3
label2:
sub x26, x28, #1
mov x0, x26
bl _Factorial__I
mov x26, x0
mul x25, x28, x26
mov x27, x25
b label3
label3:
mov x0, x27
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestFactorial:
label4:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x0, #0
bl _Factorial__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #1
bl _Factorial__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #5
bl _Factorial__I
mov x28, x0
cmp x28, #120
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #6
bl _Factorial__I
mov x28, x0
cmp x28, #720
cset w28, eq
mov w0, w28
bl _Assert
b label5
label5:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_Fibonacci__I:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
cmp x28, #0
cset w27, le
tst w27, w27
b.ne label7
b label8
label7:
mov x27, #0
b label11
label8:
cmp x28, #1
cset w26, eq
tst w26, w26
b.ne label9
b label10
label9:
mov x27, #1
b label11
label10:
sub x26, x28, #1
mov x0, x26
bl _Fibonacci__I
mov x26, x0
sub x25, x28, #2
mov x0, x25
bl _Fibonacci__I
mov x25, x0
add x28, x26, x25
mov x27, x28
b label11
label11:
mov x0, x27
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestFibonacci:
label12:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x0, #0
bl _Fibonacci__I
mov x28, x0
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #1
bl _Fibonacci__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #2
bl _Fibonacci__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #7
bl _Fibonacci__I
mov x28, x0
cmp x28, #13
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #10
bl _Fibonacci__I
mov x28, x0
cmp x28, #55
cset w28, eq
mov w0, w28
bl _Assert
b label13
label13:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_SumRange__I:
label14:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
cmp x28, #0
cset w27, le
tst w27, w27
b.ne label15
b label16
label15:
mov x27, #0
b label17
label16:
sub x26, x28, #1
mov x0, x26
bl _SumRange__I
mov x26, x0
add x25, x28, x26
mov x27, x25
b label17
label17:
mov x0, x27
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestSumRange:
label18:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x0, #0
bl _SumRange__I
mov x28, x0
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #1
bl _SumRange__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #5
bl _SumRange__I
mov x28, x0
cmp x28, #15
cset w28, eq
mov w0, w28
bl _Assert
mov x0, #10
bl _SumRange__I
mov x28, x0
cmp x28, #55
cset w28, eq
mov w0, w28
bl _Assert
b label19
label19:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_Power__I__I:
label20:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
cmp x27, #0
cset w26, eq
tst w26, w26
b.ne label21
b label22
label21:
mov x26, #1
b label23
label22:
sub x25, x27, #1
mov x1, x25
mov x0, x28
bl _Power__I__I
mov x25, x0
mul x27, x28, x25
mov x26, x27
b label23
label23:
mov x0, x26
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestPower:
label24:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x1, #0
mov x0, #2
bl _Power__I__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #1
mov x0, #2
bl _Power__I__I
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
mov x0, #2
bl _Power__I__I
mov x28, x0
cmp x28, #1024
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #4
mov x0, #3
bl _Power__I__I
mov x28, x0
cmp x28, #81
cset w28, eq
mov w0, w28
bl _Assert
b label25
label25:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_GCD__I__I:
label26:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
mov x26, x27
mov x27, x28
b label27
label27:
cmp x26, #0
cset w28, eq
tst w28, w28
b.ne label28
b label29
label28:
b label30
label29:
sdiv x28, x27, x26
msub x25, x28, x26, x27
mov x28, x26
mov x26, x25
mov x27, x28
b label27
label30:
mov x0, x27
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestGCD:
label31:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
mov x1, #8
mov x0, #12
bl _GCD__I__I
mov x28, x0
cmp x28, #4
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #75
mov x0, #100
bl _GCD__I__I
mov x28, x0
cmp x28, #25
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #13
mov x0, #17
bl _GCD__I__I
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #5
mov x0, #0
bl _GCD__I__I
mov x28, x0
cmp x28, #5
cset w28, eq
mov w0, w28
bl _Assert
b label32
label32:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_IsPalindrome__I10__I__I:
label33:
sub sp, sp, #336
stp x29, x30, [sp, #320]
add x29, sp, #320
str x20, [x29, #-8]
str x21, [x29, #-16]
str x22, [x29, #-24]
str x23, [x29, #-32]
str x24, [x29, #-40]
str x25, [x29, #-48]
str x26, [x29, #-56]
str x27, [x29, #-64]
str x28, [x29, #-72]
mov x28, x0
mov x27, x1
mov x26, x2
ldr x25, [x28]
sub x24, x29, #320
add x23, x28, #8
ldr x22, [x23]
add x23, x24, #8
str x25, [x24]
add x25, x28, #16
ldr x21, [x25]
add x25, x24, #16
str x22, [x23]
add x23, x28, #24
ldr x22, [x23]
add x23, x24, #24
str x21, [x25]
add x25, x28, #32
ldr x21, [x25]
add x25, x24, #32
str x22, [x23]
add x23, x28, #40
ldr x22, [x23]
add x23, x24, #40
str x21, [x25]
add x25, x28, #48
ldr x21, [x25]
add x25, x24, #48
str x22, [x23]
add x23, x28, #56
ldr x22, [x23]
add x23, x24, #56
str x21, [x25]
add x25, x28, #64
ldr x21, [x25]
add x25, x24, #64
str x22, [x23]
add x23, x28, #72
ldr x28, [x23]
add x23, x24, #72
str x21, [x25]
str x28, [x23]
sub x23, x29, #320
sub x28, x29, #160
ldr x25, [x23]
add x21, x23, #8
ldr x24, [x21]
add x21, x28, #8
str x25, [x28]
add x25, x23, #16
ldr x22, [x25]
add x25, x28, #16
str x24, [x21]
add x21, x23, #24
ldr x24, [x21]
add x21, x28, #24
str x22, [x25]
add x25, x23, #32
ldr x22, [x25]
add x25, x28, #32
str x24, [x21]
add x21, x23, #40
ldr x24, [x21]
add x21, x28, #40
str x22, [x25]
add x25, x23, #48
ldr x22, [x25]
add x25, x28, #48
str x24, [x21]
add x21, x23, #56
ldr x24, [x21]
add x21, x28, #56
str x22, [x25]
add x25, x23, #64
ldr x22, [x25]
add x25, x28, #64
str x24, [x21]
add x21, x23, #72
ldr x23, [x21]
add x21, x28, #72
str x22, [x25]
str x23, [x21]
cmp x27, x26
cset w21, ge
tst w21, w21
b.ne label34
b label35
label34:
mov w21, #1
b label38
label35:
sub x23, x29, #160
sub x25, x29, #160
mov x22, #80
mov x28, #0
mul x24, x28, x22
add x28, x23, x24
mov x24, #8
mul x23, x27, x24
add x24, x28, x23
ldr x23, [x24]
mov x24, #80
mov x28, #0
mul x22, x28, x24
add x28, x25, x22
mov x22, #8
mul x25, x26, x22
add x22, x28, x25
ldr x25, [x22]
cmp x23, x25
cset w25, ne
tst w25, w25
b.ne label36
b label37
label36:
mov w21, #0
b label38
label37:
sub x25, x29, #160
sub x23, x29, #240
ldr x22, [x25]
add x28, x25, #8
ldr x24, [x28]
add x28, x23, #8
str x22, [x23]
add x22, x25, #16
ldr x20, [x22]
add x22, x23, #16
str x24, [x28]
add x28, x25, #24
ldr x24, [x28]
add x28, x23, #24
str x20, [x22]
add x22, x25, #32
ldr x20, [x22]
add x22, x23, #32
str x24, [x28]
add x28, x25, #40
ldr x24, [x28]
add x28, x23, #40
str x20, [x22]
add x22, x25, #48
ldr x20, [x22]
add x22, x23, #48
str x24, [x28]
add x28, x25, #56
ldr x24, [x28]
add x28, x23, #56
str x20, [x22]
add x22, x25, #64
ldr x20, [x22]
add x22, x23, #64
str x24, [x28]
add x28, x25, #72
ldr x25, [x28]
add x28, x23, #72
str x20, [x22]
str x25, [x28]
add x28, x27, #1
sub x27, x26, #1
mov x2, x27
mov x1, x28
mov x0, x23
bl _IsPalindrome__I10__I__I
mov w23, w0
mov w21, w23
b label38
label38:
mov w0, w21
ldr x20, [x29, #-8]
ldr x21, [x29, #-16]
ldr x22, [x29, #-24]
ldr x23, [x29, #-32]
ldr x24, [x29, #-40]
ldr x25, [x29, #-48]
ldr x26, [x29, #-56]
ldr x27, [x29, #-64]
ldr x28, [x29, #-72]
ldp x29, x30, [sp, #320]
add sp, sp, #336
ret
_TestIsPalindrome:
label39:
sub sp, sp, #384
stp x29, x30, [sp, #368]
add x29, sp, #368
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
sub x28, x29, #128
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #128
add x27, x28, #8
mov x28, #2
str x28, [x27]
sub x28, x29, #128
add x27, x28, #16
mov x28, #3
str x28, [x27]
sub x28, x29, #128
add x27, x28, #24
mov x28, #2
str x28, [x27]
sub x28, x29, #128
add x27, x28, #32
mov x28, #1
str x28, [x27]
sub x28, x29, #128
add x27, x28, #40
mov x28, #0
str x28, [x27]
sub x28, x29, #128
add x27, x28, #48
mov x28, #0
str x28, [x27]
sub x28, x29, #128
add x27, x28, #56
mov x28, #0
str x28, [x27]
sub x28, x29, #128
add x27, x28, #64
mov x28, #0
str x28, [x27]
sub x28, x29, #128
add x27, x28, #72
mov x28, #0
str x28, [x27]
sub x28, x29, #128
sub x27, x29, #208
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
ldr x23, [x26]
add x26, x27, #32
str x24, [x25]
add x25, x28, #40
ldr x24, [x25]
add x25, x27, #40
str x23, [x26]
add x26, x28, #48
ldr x23, [x26]
add x26, x27, #48
str x24, [x25]
add x25, x28, #56
ldr x24, [x25]
add x25, x27, #56
str x23, [x26]
add x26, x28, #64
ldr x23, [x26]
add x26, x27, #64
str x24, [x25]
add x25, x28, #72
ldr x28, [x25]
add x25, x27, #72
str x23, [x26]
str x28, [x25]
mov x2, #4
mov x1, #0
mov x0, x27
bl _IsPalindrome__I10__I__I
mov w27, w0
cmp w27, #1
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #288
add x25, x27, #0
mov x27, #1
str x27, [x25]
sub x27, x29, #288
add x25, x27, #8
mov x27, #2
str x27, [x25]
sub x27, x29, #288
add x25, x27, #16
mov x27, #3
str x27, [x25]
sub x27, x29, #288
add x25, x27, #24
mov x27, #4
str x27, [x25]
sub x27, x29, #288
add x25, x27, #32
mov x27, #5
str x27, [x25]
sub x27, x29, #288
add x25, x27, #40
mov x27, #0
str x27, [x25]
sub x27, x29, #288
add x25, x27, #48
mov x27, #0
str x27, [x25]
sub x27, x29, #288
add x25, x27, #56
mov x27, #0
str x27, [x25]
sub x27, x29, #288
add x25, x27, #64
mov x27, #0
str x27, [x25]
sub x27, x29, #288
add x25, x27, #72
mov x27, #0
str x27, [x25]
sub x27, x29, #288
sub x25, x29, #368
ldr x28, [x27]
add x26, x27, #8
ldr x23, [x26]
add x26, x25, #8
str x28, [x25]
add x28, x27, #16
ldr x24, [x28]
add x28, x25, #16
str x23, [x26]
add x26, x27, #24
ldr x23, [x26]
add x26, x25, #24
str x24, [x28]
add x28, x27, #32
ldr x24, [x28]
add x28, x25, #32
str x23, [x26]
add x26, x27, #40
ldr x23, [x26]
add x26, x25, #40
str x24, [x28]
add x28, x27, #48
ldr x24, [x28]
add x28, x25, #48
str x23, [x26]
add x26, x27, #56
ldr x23, [x26]
add x26, x25, #56
str x24, [x28]
add x28, x27, #64
ldr x24, [x28]
add x28, x25, #64
str x23, [x26]
add x26, x27, #72
ldr x27, [x26]
add x26, x25, #72
str x24, [x28]
str x27, [x26]
mov x2, #4
mov x1, #0
mov x0, x25
bl _IsPalindrome__I10__I__I
mov w25, w0
cmp w25, #0
cset w25, eq
mov w0, w25
bl _Assert
b label40
label40:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #368]
add sp, sp, #384
ret
.globl _main
_main:
label41:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestFactorial
bl _TestFibonacci
bl _TestSumRange
bl _TestPower
bl _TestGCD
bl _TestIsPalindrome
b label42
label42:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
