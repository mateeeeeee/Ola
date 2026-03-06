
.const

_INT0:
.quad 2654435


.text

.extern _Assert
.extern _AssertMsg
_Hash__I:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
str x28, [x29, #-24]
ldr x28, [x29, #-24]
cmp x28, #0
cset w28, lt
tst w28, w28
b.ne label1
b label4
label1:
ldr x28, [x29, #-24]
neg x27, x28
str x27, [x29, #-32]
b label6
label2:
label3:
label4:
ldr x27, [x29, #-24]
str x27, [x29, #-32]
b label6
label5:
label6:
ldr x27, [x29, #-32]
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_Hash__F:
label7:
sub sp, sp, #96
stp x29, x30, [sp, #80]
add x29, sp, #80
str x27, [x29, #-8]
str x28, [x29, #-16]
str d28, [x29, #-24]
str d29, [x29, #-32]
str d30, [x29, #-40]
fmov d30, d0
str d30, [x29, #-56]
ldr d30, [x29, #-56]
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
scvtf d29, x28
fmul d28, d30, d29
fcvtzs x28, d28
str x28, [x29, #-72]
ldr x28, [x29, #-72]
cmp x28, #0
cset w28, lt
tst w28, w28
b.ne label8
b label10
label8:
ldr x28, [x29, #-72]
neg x27, x28
str x27, [x29, #-72]
b label10
label9:
label10:
ldr x27, [x29, #-72]
str x27, [x29, #-64]
b label12
label11:
label12:
ldr x27, [x29, #-64]
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d28, [x29, #-24]
ldr d29, [x29, #-32]
ldr d30, [x29, #-40]
ldp x29, x30, [sp, #80]
add sp, sp, #96
ret
_Hash__B:
label13:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
mov w28, w0
strb w28, [x29, #-17]
ldrb w28, [x29, #-17]
tst w28, w28
b.ne label14
b label17
label14:
mov x28, #1
str x28, [x29, #-25]
b label19
label15:
label16:
label17:
mov x28, #0
str x28, [x29, #-25]
b label19
label18:
label19:
ldr x28, [x29, #-25]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Id$Id
_Id$Id:
label20:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
mov x28, #0
str x28, [x27]
b label21
label21:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Id$Id__I
_Id$Id__I:
label22:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
str x27, [x29, #-40]
ldr x27, [x29, #-40]
add x26, x28, #0
str x27, [x26]
b label23
label23:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_Hash__Id:
label24:
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
sub x26, x29, #40
add x27, x26, #0
ldr x26, [x27]
str x26, [x29, #-48]
b label26
label25:
label26:
ldr x26, [x29, #-48]
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _Set.int.$Set
_Set.int.$Set:
label27:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
mov x28, x0
add x27, x28, #16
mov x26, #16
str x26, [x27]
mov x0, #128
bl ___ola_new
mov x26, x0
add x27, x28, #0
str x26, [x27]
mov x0, #128
bl ___ola_new
mov x27, x0
add x26, x28, #8
str x27, [x26]
add x26, x28, #24
mov x27, #0
str x27, [x26]
mov x27, #0
str x27, [x29, #-56]
b label29
label28:
ldr x27, [x29, #-56]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
mov x24, #0
str x24, [x26]
b label30
label29:
ldr x24, [x29, #-56]
add x26, x28, #16
ldr x25, [x26]
cmp x24, x25
cset w25, lt
tst w25, w25
b.ne label28
b label31
label30:
ldr x25, [x29, #-56]
add x24, x25, #1
str x24, [x29, #-56]
b label29
label31:
b label32
label32:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.extern ___ola_new
.globl _Set.int.$Size
_Set.int.$Size:
label33:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #24
ldr x28, [x27]
str x28, [x29, #-24]
b label35
label34:
label35:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Set.int.$Empty
_Set.int.$Empty:
label36:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #24
ldr x28, [x27]
cmp x28, #0
cset w28, eq
strb w28, [x29, #-17]
b label38
label37:
label38:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Set.int.$Contains__I
_Set.int.$Contains__I:
label39:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x27, x1
str x27, [x29, #-56]
ldr x27, [x29, #-56]
mov x0, x27
bl _Hash__I
mov x27, x0
str x27, [x29, #-65]
ldr x27, [x29, #-65]
cmp x27, #0
cset w27, lt
tst w27, w27
b.ne label40
b label42
label40:
ldr x27, [x29, #-65]
neg x26, x27
str x26, [x29, #-65]
b label42
label41:
label42:
ldr x26, [x29, #-65]
add x27, x28, #16
ldr x25, [x27]
sdiv x27, x26, x25
msub x24, x27, x25, x26
str x24, [x29, #-73]
ldr x24, [x29, #-73]
str x24, [x29, #-81]
b label43
label43:
ldr x24, [x29, #-73]
add x27, x28, #8
ldr x25, [x27]
mov x27, #8
mul x26, x24, x27
add x27, x25, x26
ldr x26, [x27]
cmp x26, #0
cset w26, eq
tst w26, w26
b.ne label47
b label50
label44:
ldr x26, [x29, #-73]
ldr x27, [x29, #-81]
cmp x26, x27
cset w27, ne
tst w27, w27
b.ne label43
b label45
label45:
mov w27, #0
strb w27, [x29, #-57]
b label55
label46:
label47:
mov w27, #0
strb w27, [x29, #-57]
b label55
label48:
label49:
label50:
ldr x27, [x29, #-73]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
ldr x24, [x26]
ldr x26, [x29, #-73]
add x25, x28, #0
ldr x27, [x25]
mov x25, #8
mul x23, x26, x25
add x25, x27, x23
ldr x23, [x25]
ldr x25, [x29, #-56]
cmp x24, #1
cset w24, eq
cmp x23, x25
cset w25, eq
and w23, w24, w25
cmp w23, #0
cset w23, ne
tst w23, w23
b.ne label51
b label54
label51:
mov w23, #1
strb w23, [x29, #-57]
b label55
label52:
label53:
label54:
ldr x23, [x29, #-73]
add x25, x28, #16
ldr x24, [x25]
add x25, x23, #1
sdiv x23, x25, x24
msub x27, x23, x24, x25
str x27, [x29, #-73]
b label44
label55:
ldrb w27, [x29, #-57]
mov w0, w27
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.globl _Set.int.$Insert__I
_Set.int.$Insert__I:
label56:
sub sp, sp, #176
stp x29, x30, [sp, #160]
add x29, sp, #160
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
ldr x27, [x29, #-72]
mov x1, x27
mov x0, x28
bl _Set.int.$Contains__I
mov w27, w0
tst w27, w27
b.ne label57
b label60
label57:
mov w27, #0
strb w27, [x29, #-73]
b label88
label58:
label59:
label60:
add x27, x28, #24
ldr x26, [x27]
add x27, x28, #16
ldr x25, [x27]
mov x27, #10
mul x24, x26, x27
mov x27, #7
mul x26, x25, x27
cmp x24, x26
cset w26, gt
tst w26, w26
b.ne label61
b label63
label61:
add x26, x28, #16
ldr x24, [x26]
str x24, [x29, #-81]
add x24, x28, #0
ldr x26, [x24]
str x26, [x29, #-89]
add x26, x28, #8
ldr x24, [x26]
str x24, [x29, #-97]
ldr x24, [x29, #-81]
mov x26, #2
mul x27, x24, x26
add x26, x28, #16
str x27, [x26]
add x26, x28, #16
ldr x27, [x26]
mov x26, #8
mul x24, x27, x26
mov x0, x24
bl ___ola_new
mov x24, x0
add x26, x28, #0
str x24, [x26]
add x26, x28, #16
ldr x24, [x26]
mov x26, #8
mul x27, x24, x26
mov x0, x27
bl ___ola_new
mov x27, x0
add x26, x28, #8
str x27, [x26]
add x26, x28, #24
mov x27, #0
str x27, [x26]
mov x27, #0
str x27, [x29, #-105]
b label65
label62:
label63:
ldr x27, [x29, #-72]
mov x0, x27
bl _Hash__I
mov x27, x0
str x27, [x29, #-113]
ldr x27, [x29, #-113]
cmp x27, #0
cset w27, lt
tst w27, w27
b.ne label81
b label83
label64:
ldr x27, [x29, #-105]
add x26, x28, #8
ldr x24, [x26]
mov x26, #8
mul x25, x27, x26
add x26, x24, x25
mov x25, #0
str x25, [x26]
b label66
label65:
ldr x25, [x29, #-105]
add x26, x28, #16
ldr x24, [x26]
cmp x25, x24
cset w24, lt
tst w24, w24
b.ne label64
b label67
label66:
ldr x24, [x29, #-105]
add x25, x24, #1
str x25, [x29, #-105]
b label65
label67:
mov x25, #0
str x25, [x29, #-121]
b label69
label68:
ldr x25, [x29, #-121]
ldr x24, [x29, #-97]
mov x26, #8
mul x27, x25, x26
add x26, x24, x27
ldr x27, [x26]
cmp x27, #1
cset w27, eq
tst w27, w27
b.ne label72
b label74
label69:
ldr x27, [x29, #-121]
ldr x26, [x29, #-81]
cmp x27, x26
cset w26, lt
tst w26, w26
b.ne label68
b label71
label70:
ldr x26, [x29, #-121]
add x27, x26, #1
str x27, [x29, #-121]
b label69
label71:
ldr x27, [x29, #-89]
mov x0, x27
bl ___ola_delete
ldr x27, [x29, #-97]
mov x0, x27
bl ___ola_delete
b label63
label72:
ldr x27, [x29, #-121]
ldr x26, [x29, #-89]
mov x24, #8
mul x25, x27, x24
add x24, x26, x25
ldr x25, [x24]
mov x0, x25
bl _Hash__I
mov x25, x0
str x25, [x29, #-129]
ldr x25, [x29, #-129]
cmp x25, #0
cset w25, lt
tst w25, w25
b.ne label75
b label77
label73:
label74:
b label70
label75:
ldr x25, [x29, #-129]
neg x24, x25
str x24, [x29, #-129]
b label77
label76:
label77:
ldr x24, [x29, #-129]
add x25, x28, #16
ldr x26, [x25]
sdiv x25, x24, x26
msub x27, x25, x26, x24
str x27, [x29, #-137]
b label78
label78:
ldr x27, [x29, #-137]
add x25, x28, #8
ldr x26, [x25]
mov x25, #8
mul x24, x27, x25
add x25, x26, x24
ldr x24, [x25]
cmp x24, #1
cset w24, eq
tst w24, w24
b.ne label79
b label80
label79:
ldr x24, [x29, #-137]
add x25, x28, #16
ldr x26, [x25]
add x25, x24, #1
sdiv x24, x25, x26
msub x27, x24, x26, x25
str x27, [x29, #-137]
b label78
label80:
ldr x27, [x29, #-137]
add x24, x28, #0
ldr x25, [x24]
ldr x24, [x29, #-121]
ldr x26, [x29, #-89]
mov x23, #8
mul x22, x24, x23
add x23, x26, x22
ldr x22, [x23]
mov x23, #8
mul x26, x27, x23
add x23, x25, x26
str x22, [x23]
ldr x23, [x29, #-137]
add x22, x28, #8
ldr x26, [x22]
mov x22, #8
mul x25, x23, x22
add x22, x26, x25
mov x25, #1
str x25, [x22]
add x25, x28, #24
ldr x22, [x25]
add x25, x22, #1
add x22, x28, #24
str x25, [x22]
b label74
label81:
ldr x22, [x29, #-113]
neg x25, x22
str x25, [x29, #-113]
b label83
label82:
label83:
ldr x25, [x29, #-113]
add x22, x28, #16
ldr x26, [x22]
sdiv x22, x25, x26
msub x23, x22, x26, x25
str x23, [x29, #-145]
b label84
label84:
ldr x23, [x29, #-145]
add x22, x28, #8
ldr x26, [x22]
mov x22, #8
mul x25, x23, x22
add x22, x26, x25
ldr x25, [x22]
cmp x25, #1
cset w25, eq
tst w25, w25
b.ne label85
b label86
label85:
ldr x25, [x29, #-145]
add x22, x28, #16
ldr x26, [x22]
add x22, x25, #1
sdiv x25, x22, x26
msub x23, x25, x26, x22
str x23, [x29, #-145]
b label84
label86:
ldr x23, [x29, #-145]
add x25, x28, #0
ldr x22, [x25]
ldr x25, [x29, #-72]
mov x26, #8
mul x27, x23, x26
add x26, x22, x27
str x25, [x26]
ldr x26, [x29, #-145]
add x25, x28, #8
ldr x27, [x25]
mov x25, #8
mul x22, x26, x25
add x25, x27, x22
mov x22, #1
str x22, [x25]
add x22, x28, #24
ldr x25, [x22]
add x22, x25, #1
add x25, x28, #24
str x22, [x25]
mov w25, #1
strb w25, [x29, #-73]
b label88
label87:
label88:
ldrb w25, [x29, #-73]
mov w0, w25
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #160]
add sp, sp, #176
ret
.extern ___ola_delete
.globl _Set.int.$Remove__I
_Set.int.$Remove__I:
label89:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x27, x1
str x27, [x29, #-56]
ldr x27, [x29, #-56]
mov x0, x27
bl _Hash__I
mov x27, x0
str x27, [x29, #-65]
ldr x27, [x29, #-65]
cmp x27, #0
cset w27, lt
tst w27, w27
b.ne label90
b label92
label90:
ldr x27, [x29, #-65]
neg x26, x27
str x26, [x29, #-65]
b label92
label91:
label92:
ldr x26, [x29, #-65]
add x27, x28, #16
ldr x25, [x27]
sdiv x27, x26, x25
msub x24, x27, x25, x26
str x24, [x29, #-73]
ldr x24, [x29, #-73]
str x24, [x29, #-81]
b label93
label93:
ldr x24, [x29, #-73]
add x27, x28, #8
ldr x25, [x27]
mov x27, #8
mul x26, x24, x27
add x27, x25, x26
ldr x26, [x27]
cmp x26, #0
cset w26, eq
tst w26, w26
b.ne label97
b label100
label94:
ldr x26, [x29, #-73]
ldr x27, [x29, #-81]
cmp x26, x27
cset w27, ne
tst w27, w27
b.ne label93
b label95
label95:
mov w27, #0
strb w27, [x29, #-57]
b label105
label96:
label97:
mov w27, #0
strb w27, [x29, #-57]
b label105
label98:
label99:
label100:
ldr x27, [x29, #-73]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
ldr x24, [x26]
ldr x26, [x29, #-73]
add x25, x28, #0
ldr x27, [x25]
mov x25, #8
mul x23, x26, x25
add x25, x27, x23
ldr x23, [x25]
ldr x25, [x29, #-56]
cmp x24, #1
cset w24, eq
cmp x23, x25
cset w25, eq
and w23, w24, w25
cmp w23, #0
cset w23, ne
tst w23, w23
b.ne label101
b label104
label101:
ldr x23, [x29, #-73]
add x25, x28, #8
ldr x24, [x25]
mov x25, #8
mul x27, x23, x25
add x25, x24, x27
mov x27, #2
str x27, [x25]
add x27, x28, #24
ldr x25, [x27]
sub x27, x25, #1
add x25, x28, #24
str x27, [x25]
mov w25, #1
strb w25, [x29, #-57]
b label105
label102:
label103:
label104:
ldr x25, [x29, #-73]
add x27, x28, #16
ldr x24, [x27]
add x27, x25, #1
sdiv x25, x27, x24
msub x23, x25, x24, x27
str x23, [x29, #-73]
b label94
label105:
ldrb w23, [x29, #-57]
mov w0, w23
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.globl _Set.int.$Clear
_Set.int.$Clear:
label106:
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
str x27, [x29, #-56]
b label108
label107:
ldr x27, [x29, #-56]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
mov x24, #0
str x24, [x26]
b label109
label108:
ldr x24, [x29, #-56]
add x26, x28, #16
ldr x25, [x26]
cmp x24, x25
cset w25, lt
tst w25, w25
b.ne label107
b label110
label109:
ldr x25, [x29, #-56]
add x24, x25, #1
str x24, [x29, #-56]
b label108
label110:
add x24, x28, #24
mov x28, #0
str x28, [x24]
b label111
label111:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestInsertContains:
label112:
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
bl _Set.int.$Set
sub x0, x29, #48
bl _Set.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Size
mov x28, x0
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
mov x1, #20
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
mov x1, #30
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
sub x0, x29, #48
bl _Set.int.$Size
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #20
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #30
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #40
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Clear
b label113
label113:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestDuplicates:
label114:
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
bl _Set.int.$Set
mov x1, #5
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #5
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Size
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Clear
b label115
label115:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestRemove:
label116:
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
bl _Set.int.$Set
mov x1, #1
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
mov x1, #2
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
mov x1, #3
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
mov x1, #2
sub x0, x29, #48
bl _Set.int.$Remove__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Size
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #2
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #1
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #3
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #2
sub x0, x29, #48
bl _Set.int.$Remove__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #48
bl _Set.int.$Clear
b label117
label117:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestRehash:
label118:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
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
bl _Set.int.$Set
mov x28, #0
str x28, [x29, #-56]
b label120
label119:
ldr x28, [x29, #-56]
mov x1, x28
sub x0, x29, #48
bl _Set.int.$Insert__I
mov w28, w0
b label121
label120:
ldr x28, [x29, #-56]
cmp x28, #15
cset w28, lt
tst w28, w28
b.ne label119
b label122
label121:
ldr x28, [x29, #-56]
add x27, x28, #1
str x27, [x29, #-56]
b label120
label122:
sub x0, x29, #48
bl _Set.int.$Size
mov x27, x0
cmp x27, #15
cset w27, eq
mov w0, w27
bl _Assert
mov x27, #0
str x27, [x29, #-64]
b label124
label123:
ldr x27, [x29, #-64]
mov x1, x27
sub x0, x29, #48
bl _Set.int.$Contains__I
mov w27, w0
cmp w27, #1
cset w27, eq
mov w0, w27
bl _Assert
b label125
label124:
ldr x27, [x29, #-64]
cmp x27, #15
cset w27, lt
tst w27, w27
b.ne label123
b label126
label125:
ldr x27, [x29, #-64]
add x28, x27, #1
str x28, [x29, #-64]
b label124
label126:
sub x0, x29, #48
bl _Set.int.$Clear
b label127
label127:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _Set.Id.$Set
_Set.Id.$Set:
label128:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
add x27, x28, #16
mov x26, #16
str x26, [x27]
add x26, x28, #0
mov x0, #128
bl ___ola_new
mov x27, x0
mov x25, #0
str x25, [x29, #-56]
b label129
label129:
ldr x25, [x29, #-56]
cmp x25, #16
cset w25, lt
tst w25, w25
b.ne label130
b label131
label130:
ldr x25, [x29, #-56]
mov x24, #8
mul x23, x25, x24
add x24, x27, x23
add x23, x24, #0
mov x24, #0
str x24, [x23]
add x24, x25, #1
str x24, [x29, #-56]
b label129
label131:
str x27, [x26]
mov x0, #128
bl ___ola_new
mov x27, x0
add x26, x28, #8
str x27, [x26]
add x26, x28, #24
mov x27, #0
str x27, [x26]
mov x27, #0
str x27, [x29, #-64]
b label133
label132:
ldr x27, [x29, #-64]
add x26, x28, #8
ldr x24, [x26]
mov x26, #8
mul x25, x27, x26
add x26, x24, x25
mov x25, #0
str x25, [x26]
b label134
label133:
ldr x25, [x29, #-64]
add x26, x28, #16
ldr x24, [x26]
cmp x25, x24
cset w24, lt
tst w24, w24
b.ne label132
b label135
label134:
ldr x24, [x29, #-64]
add x25, x24, #1
str x25, [x29, #-64]
b label133
label135:
b label136
label136:
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.globl _Set.Id.$Size
_Set.Id.$Size:
label137:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #24
ldr x28, [x27]
str x28, [x29, #-24]
b label139
label138:
label139:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Set.Id.$Empty
_Set.Id.$Empty:
label140:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #24
ldr x28, [x27]
cmp x28, #0
cset w28, eq
strb w28, [x29, #-17]
b label142
label141:
label142:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Set.Id.$Contains__Id
_Set.Id.$Contains__Id:
label143:
sub sp, sp, #144
stp x29, x30, [sp, #128]
add x29, sp, #128
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x27, x1
ldr x26, [x27]
sub x27, x29, #120
str x26, [x27]
sub x27, x29, #120
sub x26, x29, #56
ldr x25, [x27]
str x25, [x26]
sub x25, x29, #56
sub x26, x29, #72
ldr x27, [x25]
str x27, [x26]
mov x0, x26
bl _Hash__Id
mov x26, x0
str x26, [x29, #-80]
ldr x26, [x29, #-80]
cmp x26, #0
cset w26, lt
tst w26, w26
b.ne label144
b label146
label144:
ldr x26, [x29, #-80]
neg x27, x26
str x27, [x29, #-80]
b label146
label145:
label146:
ldr x27, [x29, #-80]
add x26, x28, #16
ldr x25, [x26]
sdiv x26, x27, x25
msub x24, x26, x25, x27
str x24, [x29, #-88]
ldr x24, [x29, #-88]
str x24, [x29, #-96]
b label147
label147:
ldr x24, [x29, #-88]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x27, x24, x26
add x26, x25, x27
ldr x27, [x26]
cmp x27, #0
cset w27, eq
tst w27, w27
b.ne label151
b label154
label148:
ldr x27, [x29, #-88]
ldr x26, [x29, #-96]
cmp x27, x26
cset w26, ne
tst w26, w26
b.ne label147
b label149
label149:
mov w26, #0
strb w26, [x29, #-57]
b label159
label150:
label151:
mov w26, #0
strb w26, [x29, #-57]
b label159
label152:
label153:
label154:
ldr x26, [x29, #-88]
add x27, x28, #8
ldr x25, [x27]
mov x27, #8
mul x24, x26, x27
add x27, x25, x24
ldr x24, [x27]
ldr x27, [x29, #-88]
add x25, x28, #0
ldr x26, [x25]
mov x25, #8
mul x23, x27, x25
add x25, x26, x23
mov x23, x25
sub x25, x29, #104
ldr x26, [x23]
str x26, [x25]
sub x26, x29, #56
sub x23, x29, #112
ldr x27, [x26]
str x27, [x23]
cmp x24, #1
cset w24, eq
cmp x25, x23
cset w23, eq
and w25, w24, w23
cmp w25, #0
cset w25, ne
tst w25, w25
b.ne label155
b label158
label155:
mov w25, #1
strb w25, [x29, #-57]
b label159
label156:
label157:
label158:
ldr x25, [x29, #-88]
add x23, x28, #16
ldr x24, [x23]
add x23, x25, #1
sdiv x25, x23, x24
msub x27, x25, x24, x23
str x27, [x29, #-88]
b label148
label159:
ldrb w27, [x29, #-57]
mov w0, w27
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #128]
add sp, sp, #144
ret
.globl _Set.Id.$Insert__Id
_Set.Id.$Insert__Id:
label160:
sub sp, sp, #224
stp x29, x30, [sp, #208]
add x29, sp, #208
str x22, [x29, #-8]
str x23, [x29, #-16]
str x24, [x29, #-24]
str x25, [x29, #-32]
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
mov x28, x0
mov x27, x1
ldr x26, [x27]
sub x27, x29, #208
str x26, [x27]
sub x27, x29, #208
sub x26, x29, #72
ldr x25, [x27]
str x25, [x26]
sub x25, x29, #72
sub x26, x29, #88
ldr x27, [x25]
str x27, [x26]
mov x1, x26
mov x0, x28
bl _Set.Id.$Contains__Id
mov w26, w0
tst w26, w26
b.ne label161
b label164
label161:
mov w26, #0
strb w26, [x29, #-73]
b label195
label162:
label163:
label164:
add x26, x28, #24
ldr x27, [x26]
add x26, x28, #16
ldr x25, [x26]
mov x26, #10
mul x24, x27, x26
mov x26, #7
mul x27, x25, x26
cmp x24, x27
cset w27, gt
tst w27, w27
b.ne label165
b label167
label165:
add x27, x28, #16
ldr x24, [x27]
str x24, [x29, #-96]
add x24, x28, #0
ldr x27, [x24]
str x27, [x29, #-104]
add x27, x28, #8
ldr x24, [x27]
str x24, [x29, #-112]
ldr x24, [x29, #-96]
mov x27, #2
mul x26, x24, x27
add x27, x28, #16
str x26, [x27]
add x27, x28, #0
add x26, x28, #16
ldr x24, [x26]
mov x26, #8
mul x25, x24, x26
mov x0, x25
bl ___ola_new
mov x25, x0
mov x26, #0
str x26, [x29, #-120]
b label168
label166:
label167:
sub x26, x29, #72
sub x23, x29, #128
ldr x22, [x26]
str x22, [x23]
mov x0, x23
bl _Hash__Id
mov x23, x0
str x23, [x29, #-136]
ldr x23, [x29, #-136]
cmp x23, #0
cset w23, lt
tst w23, w23
b.ne label188
b label190
label168:
ldr x23, [x29, #-120]
cmp x23, x24
cset w23, lt
tst w23, w23
b.ne label169
b label170
label169:
ldr x23, [x29, #-120]
mov x22, #8
mul x26, x23, x22
add x22, x25, x26
add x26, x22, #0
mov x22, #0
str x22, [x26]
add x22, x23, #1
str x22, [x29, #-120]
b label168
label170:
str x25, [x27]
add x25, x28, #16
ldr x24, [x25]
mov x25, #8
mul x27, x24, x25
mov x0, x27
bl ___ola_new
mov x27, x0
add x25, x28, #8
str x27, [x25]
add x25, x28, #24
mov x27, #0
str x27, [x25]
mov x27, #0
str x27, [x29, #-144]
b label172
label171:
ldr x27, [x29, #-144]
add x25, x28, #8
ldr x24, [x25]
mov x25, #8
mul x22, x27, x25
add x25, x24, x22
mov x22, #0
str x22, [x25]
b label173
label172:
ldr x22, [x29, #-144]
add x25, x28, #16
ldr x24, [x25]
cmp x22, x24
cset w24, lt
tst w24, w24
b.ne label171
b label174
label173:
ldr x24, [x29, #-144]
add x22, x24, #1
str x22, [x29, #-144]
b label172
label174:
mov x22, #0
str x22, [x29, #-152]
b label176
label175:
ldr x22, [x29, #-152]
ldr x24, [x29, #-112]
mov x25, #8
mul x27, x22, x25
add x25, x24, x27
ldr x27, [x25]
cmp x27, #1
cset w27, eq
tst w27, w27
b.ne label179
b label181
label176:
ldr x27, [x29, #-152]
ldr x25, [x29, #-96]
cmp x27, x25
cset w25, lt
tst w25, w25
b.ne label175
b label178
label177:
ldr x25, [x29, #-152]
add x27, x25, #1
str x27, [x29, #-152]
b label176
label178:
ldr x27, [x29, #-104]
mov x0, x27
bl ___ola_delete
ldr x27, [x29, #-112]
mov x0, x27
bl ___ola_delete
b label167
label179:
ldr x27, [x29, #-152]
ldr x25, [x29, #-104]
mov x24, #8
mul x22, x27, x24
add x24, x25, x22
mov x22, x24
sub x24, x29, #160
ldr x25, [x22]
str x25, [x24]
mov x0, x24
bl _Hash__Id
mov x24, x0
str x24, [x29, #-168]
ldr x24, [x29, #-168]
cmp x24, #0
cset w24, lt
tst w24, w24
b.ne label182
b label184
label180:
label181:
b label177
label182:
ldr x24, [x29, #-168]
neg x25, x24
str x25, [x29, #-168]
b label184
label183:
label184:
ldr x25, [x29, #-168]
add x24, x28, #16
ldr x22, [x24]
sdiv x24, x25, x22
msub x27, x24, x22, x25
str x27, [x29, #-176]
b label185
label185:
ldr x27, [x29, #-176]
add x24, x28, #8
ldr x22, [x24]
mov x24, #8
mul x25, x27, x24
add x24, x22, x25
ldr x25, [x24]
cmp x25, #1
cset w25, eq
tst w25, w25
b.ne label186
b label187
label186:
ldr x25, [x29, #-176]
add x24, x28, #16
ldr x22, [x24]
add x24, x25, #1
sdiv x25, x24, x22
msub x27, x25, x22, x24
str x27, [x29, #-176]
b label185
label187:
ldr x27, [x29, #-176]
add x25, x28, #0
ldr x24, [x25]
mov x25, #8
mul x22, x27, x25
add x25, x24, x22
ldr x22, [x29, #-152]
ldr x24, [x29, #-104]
mov x27, #8
mul x23, x22, x27
add x27, x24, x23
mov x23, x27
sub x27, x29, #184
ldr x24, [x23]
str x24, [x27]
mov x24, x27
mov x27, x25
ldr x25, [x24]
str x25, [x27]
ldr x25, [x29, #-176]
add x27, x28, #8
ldr x24, [x27]
mov x27, #8
mul x23, x25, x27
add x27, x24, x23
mov x23, #1
str x23, [x27]
add x23, x28, #24
ldr x27, [x23]
add x23, x27, #1
add x27, x28, #24
str x23, [x27]
b label181
label188:
ldr x27, [x29, #-136]
neg x23, x27
str x23, [x29, #-136]
b label190
label189:
label190:
ldr x23, [x29, #-136]
add x27, x28, #16
ldr x24, [x27]
sdiv x27, x23, x24
msub x25, x27, x24, x23
str x25, [x29, #-192]
b label191
label191:
ldr x25, [x29, #-192]
add x27, x28, #8
ldr x24, [x27]
mov x27, #8
mul x23, x25, x27
add x27, x24, x23
ldr x23, [x27]
cmp x23, #1
cset w23, eq
tst w23, w23
b.ne label192
b label193
label192:
ldr x23, [x29, #-192]
add x27, x28, #16
ldr x24, [x27]
add x27, x23, #1
sdiv x23, x27, x24
msub x25, x23, x24, x27
str x25, [x29, #-192]
b label191
label193:
ldr x25, [x29, #-192]
add x23, x28, #0
ldr x27, [x23]
mov x23, #8
mul x24, x25, x23
add x23, x27, x24
sub x24, x29, #72
sub x27, x29, #200
ldr x25, [x24]
str x25, [x27]
mov x25, x27
mov x27, x23
ldr x23, [x25]
str x23, [x27]
ldr x23, [x29, #-192]
add x27, x28, #8
ldr x25, [x27]
mov x27, #8
mul x24, x23, x27
add x27, x25, x24
mov x24, #1
str x24, [x27]
add x24, x28, #24
ldr x27, [x24]
add x24, x27, #1
add x27, x28, #24
str x24, [x27]
mov w27, #1
strb w27, [x29, #-73]
b label195
label194:
label195:
ldrb w27, [x29, #-73]
mov w0, w27
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #208]
add sp, sp, #224
ret
.globl _Set.Id.$Remove__Id
_Set.Id.$Remove__Id:
label196:
sub sp, sp, #144
stp x29, x30, [sp, #128]
add x29, sp, #128
str x23, [x29, #-8]
str x24, [x29, #-16]
str x25, [x29, #-24]
str x26, [x29, #-32]
str x27, [x29, #-40]
str x28, [x29, #-48]
mov x28, x0
mov x27, x1
ldr x26, [x27]
sub x27, x29, #120
str x26, [x27]
sub x27, x29, #120
sub x26, x29, #56
ldr x25, [x27]
str x25, [x26]
sub x25, x29, #56
sub x26, x29, #72
ldr x27, [x25]
str x27, [x26]
mov x0, x26
bl _Hash__Id
mov x26, x0
str x26, [x29, #-80]
ldr x26, [x29, #-80]
cmp x26, #0
cset w26, lt
tst w26, w26
b.ne label197
b label199
label197:
ldr x26, [x29, #-80]
neg x27, x26
str x27, [x29, #-80]
b label199
label198:
label199:
ldr x27, [x29, #-80]
add x26, x28, #16
ldr x25, [x26]
sdiv x26, x27, x25
msub x24, x26, x25, x27
str x24, [x29, #-88]
ldr x24, [x29, #-88]
str x24, [x29, #-96]
b label200
label200:
ldr x24, [x29, #-88]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x27, x24, x26
add x26, x25, x27
ldr x27, [x26]
cmp x27, #0
cset w27, eq
tst w27, w27
b.ne label204
b label207
label201:
ldr x27, [x29, #-88]
ldr x26, [x29, #-96]
cmp x27, x26
cset w26, ne
tst w26, w26
b.ne label200
b label202
label202:
mov w26, #0
strb w26, [x29, #-57]
b label212
label203:
label204:
mov w26, #0
strb w26, [x29, #-57]
b label212
label205:
label206:
label207:
ldr x26, [x29, #-88]
add x27, x28, #8
ldr x25, [x27]
mov x27, #8
mul x24, x26, x27
add x27, x25, x24
ldr x24, [x27]
ldr x27, [x29, #-88]
add x25, x28, #0
ldr x26, [x25]
mov x25, #8
mul x23, x27, x25
add x25, x26, x23
mov x23, x25
sub x25, x29, #104
ldr x26, [x23]
str x26, [x25]
sub x26, x29, #56
sub x23, x29, #112
ldr x27, [x26]
str x27, [x23]
cmp x24, #1
cset w24, eq
cmp x25, x23
cset w23, eq
and w25, w24, w23
cmp w25, #0
cset w25, ne
tst w25, w25
b.ne label208
b label211
label208:
ldr x25, [x29, #-88]
add x23, x28, #8
ldr x24, [x23]
mov x23, #8
mul x27, x25, x23
add x23, x24, x27
mov x27, #2
str x27, [x23]
add x27, x28, #24
ldr x23, [x27]
sub x27, x23, #1
add x23, x28, #24
str x27, [x23]
mov w23, #1
strb w23, [x29, #-57]
b label212
label209:
label210:
label211:
ldr x23, [x29, #-88]
add x27, x28, #16
ldr x24, [x27]
add x27, x23, #1
sdiv x23, x27, x24
msub x25, x23, x24, x27
str x25, [x29, #-88]
b label201
label212:
ldrb w25, [x29, #-57]
mov w0, w25
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #128]
add sp, sp, #144
ret
.globl _Set.Id.$Clear
_Set.Id.$Clear:
label213:
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
str x27, [x29, #-56]
b label215
label214:
ldr x27, [x29, #-56]
add x26, x28, #8
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
mov x24, #0
str x24, [x26]
b label216
label215:
ldr x24, [x29, #-56]
add x26, x28, #16
ldr x25, [x26]
cmp x24, x25
cset w25, lt
tst w25, w25
b.ne label214
b label217
label216:
ldr x25, [x29, #-56]
add x24, x25, #1
str x24, [x29, #-56]
b label215
label217:
add x24, x28, #24
mov x28, #0
str x28, [x24]
b label218
label218:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestCustomClass:
label219:
sub sp, sp, #176
stp x29, x30, [sp, #160]
add x29, sp, #160
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
sub x28, x29, #64
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #64
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #64
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #64
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x0, x29, #64
bl _Set.Id.$Set
sub x28, x29, #72
add x27, x28, #0
mov x28, #0
str x28, [x27]
mov x1, #10
sub x0, x29, #72
bl _Id$Id__I
sub x28, x29, #80
add x27, x28, #0
mov x28, #0
str x28, [x27]
mov x1, #20
sub x0, x29, #80
bl _Id$Id__I
sub x28, x29, #88
add x27, x28, #0
mov x28, #0
str x28, [x27]
mov x1, #30
sub x0, x29, #88
bl _Id$Id__I
sub x28, x29, #72
sub x27, x29, #96
ldr x26, [x28]
str x26, [x27]
mov x1, x27
sub x0, x29, #64
bl _Set.Id.$Insert__Id
mov w27, w0
sub x27, x29, #80
sub x26, x29, #104
ldr x28, [x27]
str x28, [x26]
mov x1, x26
sub x0, x29, #64
bl _Set.Id.$Insert__Id
mov w26, w0
sub x26, x29, #88
sub x28, x29, #112
ldr x27, [x26]
str x27, [x28]
mov x1, x28
sub x0, x29, #64
bl _Set.Id.$Insert__Id
mov w28, w0
sub x0, x29, #64
bl _Set.Id.$Size
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #72
sub x27, x29, #120
ldr x26, [x28]
str x26, [x27]
mov x1, x27
sub x0, x29, #64
bl _Set.Id.$Contains__Id
mov w27, w0
cmp w27, #1
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #80
sub x26, x29, #128
ldr x28, [x27]
str x28, [x26]
mov x1, x26
sub x0, x29, #64
bl _Set.Id.$Contains__Id
mov w26, w0
cmp w26, #1
cset w26, eq
mov w0, w26
bl _Assert
sub x26, x29, #88
sub x28, x29, #136
ldr x27, [x26]
str x27, [x28]
mov x1, x28
sub x0, x29, #64
bl _Set.Id.$Contains__Id
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #144
add x27, x28, #0
mov x28, #0
str x28, [x27]
mov x1, #40
sub x0, x29, #144
bl _Id$Id__I
sub x28, x29, #144
sub x27, x29, #152
ldr x26, [x28]
str x26, [x27]
mov x1, x27
sub x0, x29, #64
bl _Set.Id.$Contains__Id
mov w27, w0
cmp w27, #0
cset w27, eq
mov w0, w27
bl _Assert
sub x0, x29, #64
bl _Set.Id.$Clear
b label220
label220:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #160]
add sp, sp, #176
ret
.globl _main
_main:
label221:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestInsertContains
bl _TestDuplicates
bl _TestRemove
bl _TestRehash
bl _TestCustomClass
mov x28, #0
str x28, [x29, #-24]
b label223
label222:
label223:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
