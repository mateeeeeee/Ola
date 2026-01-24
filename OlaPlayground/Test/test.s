
.text

.extern _Assert
.extern _AssertMsg
.globl _Base$GetX
_Base$GetX:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label1
label1:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Base$GetSum
_Base$GetSum:
label2:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
b label4
label3:
ldr x27, [x29, #-40]
b label5
label4:
add x26, x28, #0
ldr x28, [x26]
str x28, [x29, #-40]
b label3
label5:
mov x0, x27
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Derived$GetY
_Derived$GetY:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label7
label7:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Derived$GetSum
_Derived$GetSum:
label8:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
b label11
label9:
mov x0, x28
bl _Base$GetSum
mov x26, x0
add x25, x27, x26
b label12
label10:
ldr x27, [x29, #-40]
b label9
label11:
add x26, x28, #8
ldr x27, [x26]
str x27, [x29, #-40]
b label10
label12:
mov x0, x25
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _ExtendedDerived$GetZ
_ExtendedDerived$GetZ:
label13:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #16
ldr x28, [x27]
str x28, [x29, #-24]
b label14
label14:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _ExtendedDerived$GetSum
_ExtendedDerived$GetSum:
label15:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
b label18
label16:
mov x0, x28
bl _Derived$GetSum
mov x26, x0
add x25, x27, x26
b label19
label17:
ldr x27, [x29, #-40]
b label16
label18:
add x26, x28, #16
ldr x27, [x26]
str x27, [x29, #-40]
b label17
label19:
mov x0, x25
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_PassBase__Base:
label20:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
ldr x27, [x28]
sub x28, x29, #56
str x27, [x28]
sub x28, x29, #56
sub x27, x29, #40
ldr x26, [x28]
str x26, [x27]
b label23
label21:
cmp x26, #1
cset w27, eq
mov w0, w27
bl _Assert
sub x0, x29, #40
bl _Base$GetSum
mov x27, x0
cmp x27, #1
cset w27, eq
mov w0, w27
bl _Assert
b label24
label22:
ldr x26, [x29, #-48]
b label21
label23:
sub x27, x29, #40
add x26, x27, #0
ldr x27, [x26]
str x27, [x29, #-48]
b label22
label24:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_PassBaseRef__Baseref:
label25:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
b label28
label26:
cmp x27, #1
cset w26, eq
mov w0, w26
bl _Assert
mov x0, x28
bl _Base$GetSum
mov x26, x0
cmp x26, #1
cset w26, eq
mov w0, w26
bl _Assert
b label29
label27:
ldr x27, [x29, #-40]
b label26
label28:
add x26, x28, #0
ldr x27, [x26]
str x27, [x29, #-40]
b label27
label29:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_PassDerivedRef__Derivedref:
label30:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
b label36
label31:
cmp x27, #1
cset w26, eq
mov w0, w26
bl _Assert
b label34
label32:
cmp x26, #2
cset w25, eq
mov w0, w25
bl _Assert
mov x0, x28
bl _Derived$GetSum
mov x25, x0
cmp x25, #3
cset w25, eq
mov w0, w25
bl _Assert
b label37
label33:
ldr x26, [x29, #-40]
b label32
label34:
add x25, x28, #8
ldr x26, [x25]
str x26, [x29, #-40]
b label33
label35:
ldr x27, [x29, #-48]
b label31
label36:
add x26, x28, #0
ldr x27, [x26]
str x27, [x29, #-48]
b label35
label37:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestAssignment:
label38:
sub sp, sp, #256
stp x29, x30, [sp, #240]
add x29, sp, #240
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
sub x28, x29, #96
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #96
add x26, x28, #8
mov x28, #2
str x28, [x26]
sub x28, x29, #104
ldr x26, [x27]
add x16, x28, #0
str x16, [x29, #-216]
ldr x16, [x29, #-216]
str x26, [x16]
b label53
label39:
ldr x16, [x29, #-224]
cmp x16, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #104
bl _Base$GetSum
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #104
sub x25, x29, #200
ldr x24, [x28]
str x24, [x25]
mov x0, x25
bl _PassBase__Base
sub x0, x29, #104
bl _PassBaseRef__Baseref
sub x25, x29, #128
add x24, x25, #8
mov x25, #2
str x25, [x24]
sub x25, x29, #128
add x16, x25, #0
str x16, [x29, #-232]
mov x25, #1
ldr x16, [x29, #-232]
str x25, [x16]
sub x25, x29, #128
add x23, x25, #16
mov x25, #3
str x25, [x23]
sub x0, x29, #128
bl _ExtendedDerived$GetSum
mov x25, x0
cmp x25, #6
cset w25, eq
mov w0, w25
bl _Assert
b label51
label40:
cmp x25, #3
cset w22, eq
mov w0, w22
bl _Assert
sub x22, x29, #136
ldr x16, [x29, #-232]
ldr x21, [x16]
add x20, x22, #0
str x21, [x20]
b label49
label41:
cmp x22, #1
cset w19, eq
mov w0, w19
bl _Assert
sub x0, x29, #136
bl _Base$GetSum
mov x19, x0
cmp x19, #1
cset w19, eq
mov w0, w19
bl _Assert
sub x19, x29, #136
sub x26, x29, #208
ldr x27, [x19]
str x27, [x26]
mov x0, x26
bl _PassBase__Base
sub x0, x29, #136
bl _PassBaseRef__Baseref
sub x26, x29, #152
add x27, x26, #0
str x21, [x27]
sub x27, x29, #152
ldr x26, [x24]
add x19, x27, #8
str x26, [x19]
b label47
label42:
cmp x26, #1
cset w27, eq
mov w0, w27
bl _Assert
b label45
label43:
cmp x27, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #152
bl _Derived$GetSum
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #152
bl _PassDerivedRef__Derivedref
b label54
label44:
ldr x27, [x29, #-160]
b label43
label45:
ldr x28, [x19]
str x28, [x29, #-160]
b label44
label46:
ldr x26, [x29, #-168]
b label42
label47:
sub x28, x29, #152
add x26, x28, #0
ldr x28, [x26]
str x28, [x29, #-168]
b label46
label48:
ldr x22, [x29, #-176]
b label41
label49:
ldr x19, [x20]
str x19, [x29, #-176]
b label48
label50:
ldr x25, [x29, #-184]
b label40
label51:
ldr x21, [x23]
str x21, [x29, #-184]
b label50
label52:
ldr x16, [x29, #-192]
str x16, [x29, #-224]
b label39
label53:
ldr x16, [x29, #-216]
ldr x24, [x16]
str x24, [x29, #-192]
b label52
label54:
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
ldp x29, x30, [sp, #240]
add sp, sp, #256
ret
_TestReferenceAssignment:
label55:
sub sp, sp, #240
stp x29, x30, [sp, #224]
add x29, sp, #224
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
sub x28, x29, #96
add x27, x28, #0
mov x28, #1
str x28, [x27]
sub x28, x29, #96
add x27, x28, #8
mov x28, #2
str x28, [x27]
sub x28, x29, #96
str x28, [x29, #-104]
ldr x16, [x29, #-104]
str x16, [x29, #-208]
b label70
label56:
ldr x16, [x29, #-216]
cmp x16, #1
cset w26, eq
mov w0, w26
bl _Assert
ldr x0, [x29, #-208]
bl _Base$GetSum
mov x26, x0
cmp x26, #1
cset w26, eq
mov w0, w26
bl _Assert
sub x26, x29, #128
add x25, x26, #8
mov x26, #2
str x26, [x25]
sub x26, x29, #128
add x25, x26, #0
mov x26, #1
str x26, [x25]
sub x26, x29, #128
add x25, x26, #16
mov x26, #3
str x26, [x25]
sub x26, x29, #128
str x26, [x29, #-136]
ldr x26, [x29, #-136]
b label68
label57:
cmp x25, #1
cset w24, eq
mov w0, w24
bl _Assert
mov x0, x26
bl _Base$GetSum
mov x24, x0
cmp x24, #1
cset w24, eq
mov w0, w24
bl _Assert
sub x24, x29, #128
str x24, [x29, #-144]
ldr x24, [x29, #-144]
b label66
label58:
cmp x23, #1
cset w22, eq
mov w0, w22
bl _Assert
b label64
label59:
cmp x22, #2
cset w21, eq
mov w0, w21
bl _Assert
mov x0, x24
bl _Derived$GetSum
mov x21, x0
cmp x21, #3
cset w21, eq
mov w0, w21
bl _Assert
sub x21, x29, #152
add x20, x24, #0
ldr x19, [x20]
add x20, x21, #0
str x19, [x20]
b label62
label60:
cmp x19, #1
cset w21, eq
mov w0, w21
bl _Assert
sub x0, x29, #152
bl _Base$GetSum
mov x21, x0
cmp x21, #1
cset w21, eq
mov w0, w21
bl _Assert
sub x21, x29, #152
sub x28, x29, #200
ldr x27, [x21]
str x27, [x28]
mov x0, x28
bl _PassBase__Base
sub x0, x29, #152
bl _PassBaseRef__Baseref
b label71
label61:
ldr x19, [x29, #-160]
b label60
label62:
ldr x28, [x20]
str x28, [x29, #-160]
b label61
label63:
ldr x22, [x29, #-168]
b label59
label64:
add x28, x24, #8
ldr x22, [x28]
str x22, [x29, #-168]
b label63
label65:
ldr x23, [x29, #-176]
b label58
label66:
add x22, x24, #0
ldr x23, [x22]
str x23, [x29, #-176]
b label65
label67:
ldr x25, [x29, #-184]
b label57
label68:
add x24, x26, #0
ldr x25, [x24]
str x25, [x29, #-184]
b label67
label69:
ldr x16, [x29, #-192]
str x16, [x29, #-216]
b label56
label70:
ldr x16, [x29, #-208]
add x26, x16, #0
ldr x25, [x26]
str x25, [x29, #-192]
b label69
label71:
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
ldp x29, x30, [sp, #224]
add sp, sp, #240
ret
.globl _main
_main:
label72:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestAssignment
bl _TestReferenceAssignment
b label73
label73:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
