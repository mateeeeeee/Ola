
.const

_INT0:
.quad 4614253070214989087


_INT1:
.quad 4613284796295104430


_INT2:
.quad 4607182418800017408


_INT3:
.quad 4612811918334230528


.text

.extern _Assert
.extern _AssertMsg
.globl _Box.int.$Box__I
_Box.int.$Box__I:
label0:
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
b label1
label1:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.int.$GetValue
_Box.int.$GetValue:
label2:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
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
.globl _Box.int.$SetValue__I
_Box.int.$SetValue__I:
label5:
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
b label6
label6:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.float.$Box__F
_Box.float.$Box__F:
label7:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
add x27, x28, #0
str d30, [x27]
b label8
label8:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.float.$GetValue
_Box.float.$GetValue:
label9:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-40]
b label11
label10:
label11:
ldr d30, [x29, #-40]
fmov d0, d30
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.float.$SetValue__F
_Box.float.$SetValue__F:
label12:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
add x27, x28, #0
str d30, [x27]
b label13
label13:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.bool.$Box__B
_Box.bool.$Box__B:
label14:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov w27, w1
strb w27, [x29, #-33]
ldrb w27, [x29, #-33]
add x26, x28, #0
strb w27, [x26]
b label15
label15:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Box.bool.$GetValue
_Box.bool.$GetValue:
label16:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-17]
b label18
label17:
label18:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Box.bool.$SetValue__B
_Box.bool.$SetValue__B:
label19:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov w27, w1
strb w27, [x29, #-33]
ldrb w27, [x29, #-33]
add x26, x28, #0
strb w27, [x26]
b label20
label20:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Pair.int.float.$Pair__I__F
_Pair.int.float.$Pair__I__F:
label21:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
str d30, [x29, #-32]
mov x28, x0
mov x27, x1
fmov d30, d2
str x27, [x29, #-40]
str d30, [x29, #-48]
ldr x27, [x29, #-40]
add x26, x28, #0
str x27, [x26]
ldr d30, [x29, #-48]
add x26, x28, #8
str d30, [x26]
b label22
label22:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Pair.int.float.$GetFirst
_Pair.int.float.$GetFirst:
label23:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label25
label24:
label25:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Pair.int.float.$GetSecond
_Pair.int.float.$GetSecond:
label26:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-40]
b label28
label27:
label28:
ldr d30, [x29, #-40]
fmov d0, d30
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Pair.bool.int.$Pair__B__I
_Pair.bool.int.$Pair__B__I:
label29:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov w27, w1
mov x26, x2
strb w27, [x29, #-33]
str x26, [x29, #-41]
ldrb w26, [x29, #-33]
add x27, x28, #0
strb w26, [x27]
ldr x27, [x29, #-41]
add x26, x28, #8
str x27, [x26]
b label30
label30:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Pair.bool.int.$GetFirst
_Pair.bool.int.$GetFirst:
label31:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-17]
b label33
label32:
label33:
ldrb w28, [x29, #-17]
mov w0, w28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Pair.bool.int.$GetSecond
_Pair.bool.int.$GetSecond:
label34:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label36
label35:
label36:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Pair.int.int.$Pair__I__I
_Pair.int.int.$Pair__I__I:
label37:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
mov x26, x2
str x27, [x29, #-40]
str x26, [x29, #-48]
ldr x26, [x29, #-40]
add x27, x28, #0
str x26, [x27]
ldr x27, [x29, #-48]
add x26, x28, #8
str x27, [x26]
b label38
label38:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Pair.int.int.$GetFirst
_Pair.int.int.$GetFirst:
label39:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label41
label40:
label41:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Pair.int.int.$GetSecond
_Pair.int.int.$GetSecond:
label42:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label44
label43:
label44:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Counter.int.$Counter__I
_Counter.int.$Counter__I:
label45:
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
add x26, x28, #8
mov x28, #0
str x28, [x26]
b label46
label46:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Counter.int.$Set__I
_Counter.int.$Set__I:
label47:
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
add x26, x28, #8
ldr x27, [x26]
add x26, x27, #1
add x27, x28, #8
str x26, [x27]
b label48
label48:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Counter.int.$Get
_Counter.int.$Get:
label49:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-24]
b label51
label50:
label51:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Counter.int.$GetCount
_Counter.int.$GetCount:
label52:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label54
label53:
label54:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Counter.float.$Counter__F
_Counter.float.$Counter__F:
label55:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
add x27, x28, #0
str d30, [x27]
add x27, x28, #8
mov x28, #0
str x28, [x27]
b label56
label56:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Counter.float.$Set__F
_Counter.float.$Set__F:
label57:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
str d30, [x29, #-32]
mov x28, x0
fmov d30, d1
str d30, [x29, #-40]
ldr d30, [x29, #-40]
add x27, x28, #0
str d30, [x27]
add x27, x28, #8
ldr x26, [x27]
add x27, x26, #1
add x26, x28, #8
str x27, [x26]
b label58
label58:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Counter.float.$Get
_Counter.float.$Get:
label59:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x27, [x29, #-8]
str x28, [x29, #-16]
str d30, [x29, #-24]
mov x28, x0
add x27, x28, #0
ldr x28, [x27]
str x28, [x29, #-40]
b label61
label60:
label61:
ldr d30, [x29, #-40]
fmov d0, d30
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d30, [x29, #-24]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
.globl _Counter.float.$GetCount
_Counter.float.$GetCount:
label62:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
add x27, x28, #8
ldr x28, [x27]
str x28, [x29, #-24]
b label64
label63:
label64:
ldr x28, [x29, #-24]
mov x0, x28
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label65:
sub sp, sp, #176
stp x29, x30, [sp, #160]
add x29, sp, #160
str x27, [x29, #-8]
str x28, [x29, #-16]
str d29, [x29, #-24]
str d30, [x29, #-32]
sub x28, x29, #48
add x27, x28, #0
mov x28, #0
str x28, [x27]
mov x1, #42
sub x0, x29, #48
bl _Box.int.$Box__I
sub x0, x29, #48
bl _Box.int.$GetValue
mov x28, x0
cmp x28, #42
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #100
sub x0, x29, #48
bl _Box.int.$SetValue__I
sub x0, x29, #48
bl _Box.int.$GetValue
mov x28, x0
cmp x28, #100
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #56
add x27, x28, #0
mov x28, #0
fmov d30, x28
str d30, [x27]
adrp x27, _INT0@PAGE
ldr x27, [x27, _INT0@PAGEOFF]
fmov d1, x27
sub x0, x29, #56
bl _Box.float.$Box__F
sub x0, x29, #56
bl _Box.float.$GetValue
fmov d30, d0
adrp x27, _INT0@PAGE
ldr x27, [x27, _INT0@PAGEOFF]
fmov d29, x27
fcmp d30, d29
cset w27, eq
mov w0, w27
bl _Assert
adrp x27, _INT1@PAGE
ldr x27, [x27, _INT1@PAGEOFF]
fmov d1, x27
sub x0, x29, #56
bl _Box.float.$SetValue__F
sub x0, x29, #56
bl _Box.float.$GetValue
fmov d29, d0
adrp x27, _INT1@PAGE
ldr x27, [x27, _INT1@PAGEOFF]
fmov d30, x27
fcmp d29, d30
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #64
add x28, x27, #0
mov w27, #0
strb w27, [x28]
mov w1, #1
sub x0, x29, #64
bl _Box.bool.$Box__B
sub x0, x29, #64
bl _Box.bool.$GetValue
mov w27, w0
cmp w27, #1
cset w27, eq
mov w0, w27
bl _Assert
mov w1, #0
sub x0, x29, #64
bl _Box.bool.$SetValue__B
sub x0, x29, #64
bl _Box.bool.$GetValue
mov w27, w0
cmp w27, #0
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #72
add x28, x27, #0
mov x27, #0
str x27, [x28]
mov x1, #10
sub x0, x29, #72
bl _Box.int.$Box__I
sub x0, x29, #72
bl _Box.int.$GetValue
mov x27, x0
cmp x27, #10
cset w27, eq
mov w0, w27
bl _Assert
sub x27, x29, #88
add x28, x27, #0
mov x27, #0
str x27, [x28]
sub x27, x29, #88
add x28, x27, #8
mov x27, #0
fmov d30, x27
str d30, [x28]
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d2, x28
mov x1, #10
sub x0, x29, #88
bl _Pair.int.float.$Pair__I__F
sub x0, x29, #88
bl _Pair.int.float.$GetFirst
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #88
bl _Pair.int.float.$GetSecond
fmov d30, d0
adrp x28, _INT0@PAGE
ldr x28, [x28, _INT0@PAGEOFF]
fmov d29, x28
fcmp d30, d29
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #104
add x27, x28, #0
mov w28, #0
strb w28, [x27]
sub x28, x29, #104
add x27, x28, #8
mov x28, #0
str x28, [x27]
mov x2, #99
mov w1, #1
sub x0, x29, #104
bl _Pair.bool.int.$Pair__B__I
sub x0, x29, #104
bl _Pair.bool.int.$GetFirst
mov w28, w0
cmp w28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #104
bl _Pair.bool.int.$GetSecond
mov x28, x0
cmp x28, #99
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #120
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #120
add x27, x28, #8
mov x28, #0
str x28, [x27]
mov x2, #2
mov x1, #1
sub x0, x29, #120
bl _Pair.int.int.$Pair__I__I
sub x0, x29, #120
bl _Pair.int.int.$GetFirst
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #120
bl _Pair.int.int.$GetSecond
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #136
add x27, x28, #0
mov x28, #0
str x28, [x27]
sub x28, x29, #136
add x27, x28, #8
mov x28, #0
str x28, [x27]
mov x1, #0
sub x0, x29, #136
bl _Counter.int.$Counter__I
sub x0, x29, #136
bl _Counter.int.$Get
mov x28, x0
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #136
bl _Counter.int.$GetCount
mov x28, x0
cmp x28, #0
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #5
sub x0, x29, #136
bl _Counter.int.$Set__I
sub x0, x29, #136
bl _Counter.int.$Get
mov x28, x0
cmp x28, #5
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #136
bl _Counter.int.$GetCount
mov x28, x0
cmp x28, #1
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
sub x0, x29, #136
bl _Counter.int.$Set__I
sub x0, x29, #136
bl _Counter.int.$Get
mov x28, x0
cmp x28, #10
cset w28, eq
mov w0, w28
bl _Assert
sub x0, x29, #136
bl _Counter.int.$GetCount
mov x28, x0
cmp x28, #2
cset w28, eq
mov w0, w28
bl _Assert
sub x28, x29, #152
add x27, x28, #0
mov x28, #0
fmov d29, x28
str d29, [x27]
sub x27, x29, #152
add x28, x27, #8
mov x27, #0
str x27, [x28]
adrp x27, _INT2@PAGE
ldr x27, [x27, _INT2@PAGEOFF]
fmov d1, x27
sub x0, x29, #152
bl _Counter.float.$Counter__F
sub x0, x29, #152
bl _Counter.float.$Get
fmov d29, d0
adrp x27, _INT2@PAGE
ldr x27, [x27, _INT2@PAGEOFF]
fmov d30, x27
fcmp d29, d30
cset w27, eq
mov w0, w27
bl _Assert
adrp x27, _INT3@PAGE
ldr x27, [x27, _INT3@PAGEOFF]
fmov d1, x27
sub x0, x29, #152
bl _Counter.float.$Set__F
sub x0, x29, #152
bl _Counter.float.$Get
fmov d30, d0
adrp x27, _INT3@PAGE
ldr x27, [x27, _INT3@PAGEOFF]
fmov d29, x27
fcmp d30, d29
cset w27, eq
mov w0, w27
bl _Assert
sub x0, x29, #152
bl _Counter.float.$GetCount
mov x27, x0
cmp x27, #1
cset w27, eq
mov w0, w27
bl _Assert
mov x27, #0
str x27, [x29, #-40]
b label67
label66:
label67:
ldr x27, [x29, #-40]
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldr d29, [x29, #-24]
ldr d30, [x29, #-32]
ldp x29, x30, [sp, #160]
add sp, sp, #176
ret
