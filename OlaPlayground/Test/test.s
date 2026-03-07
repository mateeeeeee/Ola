
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
.globl _Map.int.int.$Map
_Map.int.int.$Map:
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
add x27, x28, #24
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
mov x0, #128
bl ___ola_new
mov x26, x0
add x27, x28, #16
str x26, [x27]
add x27, x28, #32
mov x26, #0
str x26, [x27]
mov x26, #0
str x26, [x29, #-56]
b label22
label21:
ldr x26, [x29, #-56]
add x27, x28, #16
ldr x25, [x27]
mov x27, #8
mul x24, x26, x27
add x27, x25, x24
mov x24, #0
str x24, [x27]
b label23
label22:
ldr x24, [x29, #-56]
add x27, x28, #24
ldr x25, [x27]
cmp x24, x25
cset w25, lt
tst w25, w25
b.ne label21
b label24
label23:
ldr x25, [x29, #-56]
add x24, x25, #1
str x24, [x29, #-56]
b label22
label24:
b label25
label25:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
.extern ___ola_new
.globl _Map.int.int.$Size
_Map.int.int.$Size:
label26:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #32
ldr x28, [x27]
str x28, [x29, #-24]
b label28
label27:
label28:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Map.int.int.$Empty
_Map.int.int.$Empty:
label29:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #32
ldr x28, [x27]
cmp x28, #0
cset w28, eq
strb w28, [x29, #-17]
b label31
label30:
label31:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Map.int.int.$Contains__I
_Map.int.int.$Contains__I:
label32:
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
b.ne label33
b label35
label33:
ldr x27, [x29, #-65]
neg x26, x27
str x26, [x29, #-65]
b label35
label34:
label35:
ldr x26, [x29, #-65]
add x27, x28, #24
ldr x25, [x27]
sdiv x27, x26, x25
msub x24, x27, x25, x26
str x24, [x29, #-73]
ldr x24, [x29, #-73]
str x24, [x29, #-81]
b label36
label36:
ldr x24, [x29, #-73]
add x27, x28, #16
ldr x25, [x27]
mov x27, #8
mul x26, x24, x27
add x27, x25, x26
ldr x26, [x27]
cmp x26, #0
cset w26, eq
tst w26, w26
b.ne label40
b label43
label37:
ldr x26, [x29, #-73]
ldr x27, [x29, #-81]
cmp x26, x27
cset w27, ne
tst w27, w27
b.ne label36
b label38
label38:
mov w27, #0
strb w27, [x29, #-57]
b label48
label39:
label40:
mov w27, #0
strb w27, [x29, #-57]
b label48
label41:
label42:
label43:
ldr x27, [x29, #-73]
add x26, x28, #16
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
b.ne label44
b label47
label44:
mov w23, #1
strb w23, [x29, #-57]
b label48
label45:
label46:
label47:
ldr x23, [x29, #-73]
add x25, x28, #24
ldr x24, [x25]
add x25, x23, #1
sdiv x23, x25, x24
msub x27, x23, x24, x25
str x27, [x29, #-73]
b label37
label48:
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
.globl _Map.int.int.$Get__I
_Map.int.int.$Get__I:
label49:
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
str x27, [x29, #-72]
ldr x27, [x29, #-72]
cmp x27, #0
cset w27, lt
tst w27, w27
b.ne label50
b label52
label50:
ldr x27, [x29, #-72]
neg x26, x27
str x26, [x29, #-72]
b label52
label51:
label52:
ldr x26, [x29, #-72]
add x27, x28, #24
ldr x25, [x27]
sdiv x27, x26, x25
msub x24, x27, x25, x26
str x24, [x29, #-80]
ldr x24, [x29, #-80]
str x24, [x29, #-88]
b label53
label53:
ldr x24, [x29, #-80]
add x27, x28, #16
ldr x25, [x27]
mov x27, #8
mul x26, x24, x27
add x27, x25, x26
ldr x26, [x27]
ldr x27, [x29, #-80]
add x25, x28, #0
ldr x24, [x25]
mov x25, #8
mul x23, x27, x25
add x25, x24, x23
ldr x23, [x25]
ldr x25, [x29, #-56]
cmp x26, #1
cset w26, eq
cmp x23, x25
cset w25, eq
and w23, w26, w25
cmp w23, #0
cset w23, ne
tst w23, w23
b.ne label57
b label60
label54:
ldr x23, [x29, #-80]
ldr x25, [x29, #-88]
cmp x23, x25
cset w25, ne
tst w25, w25
b.ne label53
b label55
label55:
add x25, x28, #8
ldr x23, [x25]
add x25, x23, #0
ldr x23, [x25]
str x23, [x29, #-64]
b label65
label56:
label57:
ldr x23, [x29, #-80]
add x25, x28, #8
ldr x26, [x25]
mov x25, #8
mul x24, x23, x25
add x25, x26, x24
ldr x24, [x25]
str x24, [x29, #-64]
b label65
label58:
label59:
label60:
ldr x24, [x29, #-80]
add x25, x28, #16
ldr x26, [x25]
mov x25, #8
mul x23, x24, x25
add x25, x26, x23
ldr x23, [x25]
cmp x23, #0
cset w23, eq
tst w23, w23
b.ne label61
b label64
label61:
add x23, x28, #8
ldr x25, [x23]
add x23, x25, #0
ldr x25, [x23]
str x25, [x29, #-64]
b label65
label62:
label63:
label64:
ldr x25, [x29, #-80]
add x23, x28, #24
ldr x26, [x23]
add x23, x25, #1
sdiv x25, x23, x26
msub x24, x25, x26, x23
str x24, [x29, #-80]
b label54
label65:
ldr x24, [x29, #-64]
mov x0, x24
ldr x23, [x29, #-8]
ldr x24, [x29, #-16]
ldr x25, [x29, #-24]
ldr x26, [x29, #-32]
ldr x27, [x29, #-40]
ldr x28, [x29, #-48]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.globl _Map.int.int.$Put__I__I
_Map.int.int.$Put__I__I:
label66:
sub sp, sp, #192
stp x29, x30, [sp, #176]
add x29, sp, #176
str x22, [x29, #-8]
str x23, [x29, #-16]
str x24, [x29, #-24]
str x25, [x29, #-32]
str x26, [x29, #-40]
str x27, [x29, #-48]
str x28, [x29, #-56]
mov x28, x0
mov x27, x1
mov x26, x2
str x27, [x29, #-72]
str x26, [x29, #-80]
ldr x26, [x29, #-72]
mov x0, x26
bl _Hash__I
mov x26, x0
str x26, [x29, #-88]
ldr x26, [x29, #-88]
cmp x26, #0
cset w26, lt
tst w26, w26
b.ne label67
b label69
label67:
ldr x26, [x29, #-88]
neg x27, x26
str x27, [x29, #-88]
b label69
label68:
label69:
ldr x27, [x29, #-88]
add x26, x28, #24
ldr x25, [x26]
sdiv x26, x27, x25
msub x24, x26, x25, x27
str x24, [x29, #-96]
ldr x24, [x29, #-96]
str x24, [x29, #-104]
b label70
label70:
ldr x24, [x29, #-96]
add x26, x28, #16
ldr x25, [x26]
mov x26, #8
mul x27, x24, x26
add x26, x25, x27
ldr x27, [x26]
ldr x26, [x29, #-96]
add x25, x28, #0
ldr x24, [x25]
mov x25, #8
mul x23, x26, x25
add x25, x24, x23
ldr x23, [x25]
ldr x25, [x29, #-72]
cmp x27, #1
cset w27, eq
cmp x23, x25
cset w25, eq
and w23, w27, w25
cmp w23, #0
cset w23, ne
tst w23, w23
b.ne label73
b label76
label71:
ldr x23, [x29, #-96]
ldr x25, [x29, #-104]
cmp x23, x25
cset w25, ne
tst w25, w25
b.ne label70
b label72
label72:
b label101
label73:
ldr x25, [x29, #-96]
add x23, x28, #8
ldr x27, [x23]
ldr x23, [x29, #-80]
mov x24, #8
mul x26, x25, x24
add x24, x27, x26
str x23, [x24]
b label101
label74:
label75:
label76:
ldr x24, [x29, #-96]
add x23, x28, #16
ldr x26, [x23]
mov x23, #8
mul x27, x24, x23
add x23, x26, x27
ldr x27, [x23]
cmp x27, #1
cset w27, ne
tst w27, w27
b.ne label77
b label79
label77:
ldr x27, [x29, #-96]
add x23, x28, #0
ldr x26, [x23]
ldr x23, [x29, #-72]
mov x24, #8
mul x25, x27, x24
add x24, x26, x25
str x23, [x24]
ldr x24, [x29, #-96]
add x23, x28, #8
ldr x25, [x23]
ldr x23, [x29, #-80]
mov x26, #8
mul x27, x24, x26
add x26, x25, x27
str x23, [x26]
ldr x26, [x29, #-96]
add x23, x28, #16
ldr x27, [x23]
mov x23, #8
mul x25, x26, x23
add x23, x27, x25
mov x25, #1
str x25, [x23]
add x25, x28, #32
ldr x23, [x25]
add x25, x23, #1
add x23, x28, #32
str x25, [x23]
add x23, x28, #32
ldr x25, [x23]
add x23, x28, #24
ldr x27, [x23]
mov x23, #10
mul x26, x25, x23
mov x23, #7
mul x25, x27, x23
cmp x26, x25
cset w25, gt
tst w25, w25
b.ne label80
b label82
label78:
label79:
ldr x25, [x29, #-96]
add x26, x28, #24
ldr x23, [x26]
add x26, x25, #1
sdiv x25, x26, x23
msub x27, x25, x23, x26
str x27, [x29, #-96]
b label71
label80:
add x27, x28, #24
ldr x25, [x27]
str x25, [x29, #-112]
add x25, x28, #0
ldr x27, [x25]
str x27, [x29, #-120]
add x27, x28, #8
ldr x25, [x27]
str x25, [x29, #-128]
add x25, x28, #16
ldr x27, [x25]
str x27, [x29, #-136]
ldr x27, [x29, #-112]
mov x25, #2
mul x26, x27, x25
add x25, x28, #24
str x26, [x25]
add x25, x28, #24
ldr x26, [x25]
mov x25, #8
mul x27, x26, x25
mov x0, x27
bl ___ola_new
mov x27, x0
add x25, x28, #0
str x27, [x25]
add x25, x28, #24
ldr x27, [x25]
mov x25, #8
mul x26, x27, x25
mov x0, x26
bl ___ola_new
mov x26, x0
add x25, x28, #8
str x26, [x25]
add x25, x28, #24
ldr x26, [x25]
mov x25, #8
mul x27, x26, x25
mov x0, x27
bl ___ola_new
mov x27, x0
add x25, x28, #16
str x27, [x25]
add x25, x28, #32
mov x27, #0
str x27, [x25]
mov x27, #0
str x27, [x29, #-144]
b label85
label81:
label82:
b label101
label83:
label84:
ldr x27, [x29, #-144]
add x25, x28, #16
ldr x26, [x25]
mov x25, #8
mul x23, x27, x25
add x25, x26, x23
mov x23, #0
str x23, [x25]
b label86
label85:
ldr x23, [x29, #-144]
add x25, x28, #24
ldr x26, [x25]
cmp x23, x26
cset w26, lt
tst w26, w26
b.ne label84
b label87
label86:
ldr x26, [x29, #-144]
add x23, x26, #1
str x23, [x29, #-144]
b label85
label87:
mov x23, #0
str x23, [x29, #-152]
b label89
label88:
ldr x23, [x29, #-152]
ldr x26, [x29, #-136]
mov x25, #8
mul x27, x23, x25
add x25, x26, x27
ldr x27, [x25]
cmp x27, #1
cset w27, eq
tst w27, w27
b.ne label92
b label94
label89:
ldr x27, [x29, #-152]
ldr x25, [x29, #-112]
cmp x27, x25
cset w25, lt
tst w25, w25
b.ne label88
b label91
label90:
ldr x25, [x29, #-152]
add x27, x25, #1
str x27, [x29, #-152]
b label89
label91:
ldr x27, [x29, #-120]
mov x0, x27
bl ___ola_delete
ldr x27, [x29, #-128]
mov x0, x27
bl ___ola_delete
ldr x27, [x29, #-136]
mov x0, x27
bl ___ola_delete
b label82
label92:
ldr x27, [x29, #-152]
ldr x25, [x29, #-120]
mov x26, #8
mul x23, x27, x26
add x26, x25, x23
ldr x23, [x26]
mov x0, x23
bl _Hash__I
mov x23, x0
str x23, [x29, #-160]
ldr x23, [x29, #-160]
cmp x23, #0
cset w23, lt
tst w23, w23
b.ne label95
b label97
label93:
label94:
b label90
label95:
ldr x23, [x29, #-160]
neg x26, x23
str x26, [x29, #-160]
b label97
label96:
label97:
ldr x26, [x29, #-160]
add x23, x28, #24
ldr x25, [x23]
sdiv x23, x26, x25
msub x27, x23, x25, x26
str x27, [x29, #-168]
b label98
label98:
ldr x27, [x29, #-168]
add x23, x28, #16
ldr x25, [x23]
mov x23, #8
mul x26, x27, x23
add x23, x25, x26
ldr x26, [x23]
cmp x26, #1
cset w26, eq
tst w26, w26
b.ne label99
b label100
label99:
ldr x26, [x29, #-168]
add x23, x28, #24
ldr x25, [x23]
add x23, x26, #1
sdiv x26, x23, x25
msub x27, x26, x25, x23
str x27, [x29, #-168]
b label98
label100:
ldr x27, [x29, #-168]
add x26, x28, #0
ldr x23, [x26]
ldr x26, [x29, #-152]
ldr x25, [x29, #-120]
mov x24, #8
mul x22, x26, x24
add x24, x25, x22
ldr x22, [x24]
mov x24, #8
mul x25, x27, x24
add x24, x23, x25
str x22, [x24]
ldr x24, [x29, #-168]
add x22, x28, #8
ldr x25, [x22]
ldr x22, [x29, #-152]
ldr x23, [x29, #-128]
mov x27, #8
mul x26, x22, x27
add x27, x23, x26
ldr x26, [x27]
mov x27, #8
mul x23, x24, x27
add x27, x25, x23
str x26, [x27]
ldr x27, [x29, #-168]
add x26, x28, #16
ldr x23, [x26]
mov x26, #8
mul x25, x27, x26
add x26, x23, x25
mov x25, #1
str x25, [x26]
add x25, x28, #32
ldr x26, [x25]
add x25, x26, #1
add x26, x28, #32
str x25, [x26]
b label94
label101:
ldr x22, [x29, #-8]
ldr x23, [x29, #-16]
ldr x24, [x29, #-24]
ldr x25, [x29, #-32]
ldr x26, [x29, #-40]
ldr x27, [x29, #-48]
ldr x28, [x29, #-56]
ldp x29, x30, [sp, #176]
add sp, sp, #192
ret
.extern ___ola_delete
.globl _Map.int.int.$Remove__I
_Map.int.int.$Remove__I:
label102:
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
b.ne label103
b label105
label103:
ldr x27, [x29, #-65]
neg x26, x27
str x26, [x29, #-65]
b label105
label104:
label105:
ldr x26, [x29, #-65]
add x27, x28, #24
ldr x25, [x27]
sdiv x27, x26, x25
msub x24, x27, x25, x26
str x24, [x29, #-73]
ldr x24, [x29, #-73]
str x24, [x29, #-81]
b label106
label106:
ldr x24, [x29, #-73]
add x27, x28, #16
ldr x25, [x27]
mov x27, #8
mul x26, x24, x27
add x27, x25, x26
ldr x26, [x27]
cmp x26, #0
cset w26, eq
tst w26, w26
b.ne label110
b label113
label107:
ldr x26, [x29, #-73]
ldr x27, [x29, #-81]
cmp x26, x27
cset w27, ne
tst w27, w27
b.ne label106
b label108
label108:
mov w27, #0
strb w27, [x29, #-57]
b label118
label109:
label110:
mov w27, #0
strb w27, [x29, #-57]
b label118
label111:
label112:
label113:
ldr x27, [x29, #-73]
add x26, x28, #16
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
b.ne label114
b label117
label114:
ldr x23, [x29, #-73]
add x25, x28, #16
ldr x24, [x25]
mov x25, #8
mul x27, x23, x25
add x25, x24, x27
mov x27, #2
str x27, [x25]
add x27, x28, #32
ldr x25, [x27]
sub x27, x25, #1
add x25, x28, #32
str x27, [x25]
mov w25, #1
strb w25, [x29, #-57]
b label118
label115:
label116:
label117:
ldr x25, [x29, #-73]
add x27, x28, #24
ldr x24, [x27]
add x27, x25, #1
sdiv x25, x27, x24
msub x23, x25, x24, x27
str x23, [x29, #-73]
b label107
label118:
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
.globl _Map.int.int.$Clear
_Map.int.int.$Clear:
label119:
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
b label121
label120:
ldr x27, [x29, #-56]
add x26, x28, #16
ldr x25, [x26]
mov x26, #8
mul x24, x27, x26
add x26, x25, x24
mov x24, #0
str x24, [x26]
b label122
label121:
ldr x24, [x29, #-56]
add x26, x28, #24
ldr x25, [x26]
cmp x24, x25
cset w25, lt
tst w25, w25
b.ne label120
b label123
label122:
ldr x25, [x29, #-56]
add x24, x25, #1
str x24, [x29, #-56]
b label121
label123:
add x24, x28, #32
mov x28, #0
str x28, [x24]
b label124
label124:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestPutGet:
label125:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #32
mov x28, #0
str x28, [x27]
sub x0, x29, #56
bl _Map.int.int.$Map
sub x0, x29, #56
bl _Map.int.int.$Empty
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x2, #100
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x2, #200
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x2, #300
mov x1, #3
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
sub x0, x29, #56
bl _Map.int.int.$Size
mov x28, x0
cmp x28, #3
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #100
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #200
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #3
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #300
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Clear
b label126
label126:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestOverwrite:
label127:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #32
mov x28, #0
str x28, [x27]
sub x0, x29, #56
bl _Map.int.int.$Map
mov x2, #10
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
mov x2, #20
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #20
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Size
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Clear
b label128
label128:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestContains:
label129:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #32
mov x28, #0
str x28, [x27]
sub x0, x29, #56
bl _Map.int.int.$Map
mov x2, #50
mov x1, #5
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x1, #5
sub x0, x29, #56
bl _Map.int.int.$Contains__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #6
sub x0, x29, #56
bl _Map.int.int.$Contains__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Clear
b label130
label130:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestRemove:
label131:
sub sp, sp, #80
stp x29, x30, [sp, #64]
add x29, sp, #64
str x27, [x29, #-8]
str x28, [x29, #-16]
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x28, x29, #56
add x27, x28, #32
mov x28, #0
str x28, [x27]
sub x0, x29, #56
bl _Map.int.int.$Map
mov x2, #10
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x2, #20
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x2, #30
mov x1, #3
sub x0, x29, #56
bl _Map.int.int.$Put__I__I
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Remove__I
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Size
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Contains__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #1
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #3
sub x0, x29, #56
bl _Map.int.int.$Get__I
mov x28, x0
cmp x28, #30
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #2
sub x0, x29, #56
bl _Map.int.int.$Remove__I
mov w28, w0
cmp w28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #56
bl _Map.int.int.$Clear
b label132
label132:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #64]
add sp, sp, #80
ret
_TestRehash:
label133:
sub sp, sp, #112
stp x29, x30, [sp, #96]
add x29, sp, #96
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
sub x28, x29, #72
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #72
add x27, x28, #8
mov x28, #0
str x28, [x27]
sub x28, x29, #72
add x27, x28, #16
mov x28, #0
str x28, [x27]
sub x28, x29, #72
add x27, x28, #24
mov x28, #0
str x28, [x27]
sub x28, x29, #72
add x27, x28, #32
mov x28, #0
str x28, [x27]
sub x0, x29, #72
bl _Map.int.int.$Map
mov x28, #0
str x28, [x29, #-80]
b label135
label134:
ldr x28, [x29, #-80]
ldr x27, [x29, #-80]
mov x26, #10
mul x25, x27, x26
mov x2, x25
mov x1, x28
sub x0, x29, #72
bl _Map.int.int.$Put__I__I
b label136
label135:
ldr x28, [x29, #-80]
cmp x28, #15
cset w28, lt
tst w28, w28
b.ne label134
b label137
label136:
ldr x28, [x29, #-80]
add x25, x28, #1
str x25, [x29, #-80]
b label135
label137:
sub x0, x29, #72
bl _Map.int.int.$Size
mov x25, x0
cmp x25, #15
cset w25, eq
mov w0, w25
bl _Assert
mov x25, #0
str x25, [x29, #-88]
b label139
label138:
ldr x25, [x29, #-88]
mov x1, x25
sub x0, x29, #72
bl _Map.int.int.$Get__I
mov x25, x0
ldr x28, [x29, #-88]
mov x26, #10
mul x27, x28, x26
cmp x25, x27
cset w27, eq
mov w0, w27
bl _Assert
b label140
label139:
ldr x27, [x29, #-88]
cmp x27, #15
cset w27, lt
tst w27, w27
b.ne label138
b label141
label140:
ldr x27, [x29, #-88]
add x25, x27, #1
str x25, [x29, #-88]
b label139
label141:
sub x0, x29, #72
bl _Map.int.int.$Clear
b label142
label142:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #96]
add sp, sp, #112
ret
.globl _main
_main:
label143:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x28, [x29, #-8]
bl _TestPutGet
bl _TestOverwrite
bl _TestContains
bl _TestRemove
bl _TestRehash
mov x28, #0
str x28, [x29, #-24]
b label145
label144:
label145:
ldr x28, [x29, #-24]
mov x0, x28
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
