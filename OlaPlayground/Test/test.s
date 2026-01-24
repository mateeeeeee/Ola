
.text

.extern _Assert
.extern _AssertMsg
.globl _S$Init__I__I
_S$Init__I__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
mov x27, x1
mov x26, x2
add x25, x28, #0
str x27, [x25]
add x25, x28, #8
str x26, [x25]
b label1
label1:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _S$SetX__I
_S$SetX__I:
label2:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
add x26, x28, #0
str x27, [x26]
b label3
label3:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _S$SetY__I
_S$SetY__I:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
add x26, x28, #8
str x27, [x26]
b label5
label5:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _S$GetX
_S$GetX:
label6:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
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
.globl _S$GetY
_S$GetY:
label8:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label9
label9:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_StructByValue__S:
label10:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
mov x28, x0
ldr x27, [x28]
sub x26, x29, #80
add x25, x28, #8
ldr x28, [x25]
add x25, x26, #8
str x27, [x26]
str x28, [x25]
b label18
label11:
cmp x25, #100
cset w26, eq
mov w0, w26
bl _Assert
b label14
label12:
cmp x26, #100
cset w27, eq
mov w0, w27
bl _Assert
b label19
label13:
ldr x26, [x29, #-56]
b label12
label14:
ldr x27, [x28]
str x27, [x29, #-56]
b label13
label15:
ldr x25, [x29, #-64]
b label11
label16:
ldr x27, [x26]
str x27, [x29, #-64]
b label15
label17:
sub x27, x29, #48
add x28, x27, #8
mov x27, #100
str x27, [x28]
b label16
label18:
sub x27, x29, #48
add x26, x27, #0
mov x27, #100
str x27, [x26]
b label17
label19:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_StructByRef__Sref:
label20:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
b label28
label21:
cmp x27, #1000
cset w25, eq
mov w0, w25
bl _Assert
b label24
label22:
cmp x25, #1000
cset w24, eq
mov w0, w24
bl _Assert
b label29
label23:
ldr x25, [x29, #-56]
b label22
label24:
ldr x24, [x26]
str x24, [x29, #-56]
b label23
label25:
ldr x27, [x29, #-64]
b label21
label26:
ldr x24, [x25]
str x24, [x29, #-64]
b label25
label27:
add x26, x28, #8
mov x24, #1000
str x24, [x26]
b label26
label28:
add x25, x28, #0
mov x26, #1000
str x26, [x25]
b label27
label29:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _main
_main:
label30:
sub sp, sp, #304
stp x29, x30, [sp, #288]
add x29, sp, #288
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
add x16, x28, #0
str x16, [x29, #-224]
mov x28, #0
ldr x16, [x29, #-224]
str x28, [x16]
sub x28, x29, #96
add x16, x28, #8
str x16, [x29, #-232]
mov x28, #0
ldr x16, [x29, #-232]
str x28, [x16]
b label68
label31:
sub x28, x29, #96
sub x25, x29, #216
ldr x24, [x28]
add x23, x28, #8
ldr x28, [x23]
add x23, x25, #8
str x24, [x25]
str x28, [x23]
mov x0, x25
bl _StructByValue__S
b label67
label32:
ldr x16, [x29, #-240]
cmp x16, #10
cset w23, eq
mov w0, w23
bl _Assert
b label65
label33:
ldr x16, [x29, #-248]
cmp x16, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #112
ldr x16, [x29, #-224]
ldr x24, [x16]
add x16, x28, #0
str x16, [x29, #-256]
ldr x16, [x29, #-256]
str x24, [x16]
sub x24, x29, #112
ldr x16, [x29, #-232]
ldr x28, [x16]
add x16, x24, #8
sub x17, x29, #264
str x16, [x17]
sub x16, x29, #264
ldr x16, [x16]
str x28, [x16]
b label63
label34:
sub x17, x29, #272
ldr x16, [x17]
cmp x16, #10
cset w24, eq
mov w0, w24
bl _Assert
b label59
label35:
sub x17, x29, #280
ldr x16, [x17]
cmp x16, #10
cset w20, eq
mov w0, w20
bl _Assert
b label57
label36:
cmp x19, #25
cset w26, eq
mov w0, w26
bl _Assert
b label55
label37:
cmp x27, #25
cset w25, eq
mov w0, w25
bl _Assert
sub x0, x29, #96
bl _StructByRef__Sref
b label53
label38:
cmp x25, #1000
cset w23, eq
mov w0, w23
bl _Assert
b label51
label39:
cmp x23, #1000
cset w21, eq
mov w0, w21
bl _Assert
b label49
label40:
cmp x21, #1000
cset w22, eq
mov w0, w22
bl _Assert
b label47
label41:
cmp x22, #1000
cset w28, eq
mov w0, w28
bl _Assert
b label45
label42:
cmp x28, #0
cset w24, eq
mov w0, w24
bl _Assert
b label69
label43:
ldr x28, [x29, #-120]
b label42
label44:
ldr x16, [x29, #-224]
ldr x24, [x16]
str x24, [x29, #-120]
b label43
label45:
mov x24, #0
ldr x16, [x29, #-224]
str x24, [x16]
b label44
label46:
ldr x22, [x29, #-128]
b label41
label47:
str x26, [x29, #-128]
b label46
label48:
ldr x21, [x29, #-136]
b label40
label49:
str x20, [x29, #-136]
b label48
label50:
ldr x23, [x29, #-144]
b label39
label51:
str x26, [x29, #-144]
b label50
label52:
ldr x25, [x29, #-152]
b label38
label53:
str x20, [x29, #-152]
b label52
label54:
ldr x27, [x29, #-160]
b label37
label55:
ldr x16, [x29, #-232]
ldr x26, [x16]
str x26, [x29, #-160]
b label54
label56:
ldr x19, [x29, #-168]
b label36
label57:
ldr x16, [x29, #-224]
ldr x20, [x16]
str x20, [x29, #-168]
b label56
label58:
ldr x16, [x29, #-176]
sub x17, x29, #280
str x16, [x17]
b label35
label59:
sub x16, x29, #264
ldr x16, [x16]
ldr x20, [x16]
str x20, [x29, #-176]
b label58
label60:
ldr x16, [x29, #-184]
sub x17, x29, #272
str x16, [x17]
b label34
label61:
ldr x16, [x29, #-256]
ldr x20, [x16]
str x20, [x29, #-184]
b label60
label62:
mov x20, #25
ldr x16, [x29, #-232]
str x20, [x16]
b label61
label63:
mov x20, #25
ldr x16, [x29, #-224]
str x20, [x16]
b label62
label64:
ldr x16, [x29, #-192]
str x16, [x29, #-248]
b label33
label65:
ldr x16, [x29, #-232]
ldr x20, [x16]
str x20, [x29, #-192]
b label64
label66:
ldr x16, [x29, #-200]
str x16, [x29, #-240]
b label32
label67:
ldr x16, [x29, #-224]
ldr x20, [x16]
str x20, [x29, #-200]
b label66
label68:
mov x20, #10
ldr x16, [x29, #-224]
str x20, [x16]
mov x20, #10
ldr x16, [x29, #-232]
str x20, [x16]
b label31
label69:
mov x0, #0
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
ldp x29, x30, [sp, #288]
add sp, sp, #240
ret
