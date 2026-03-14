
.const

_Base$base_val:
.quad 100
.p2align 3


_Visibility$secret:
.quad 42
.p2align 3


_StaticInit$b:
.quad 20
.p2align 3


.data

_Counter$count:
.quad 0
.p2align 3


_StaticInit$a:
.quad 10
.p2align 3


.text

.extern _Assert
.extern _AssertMsg
.globl _Counter$GetCount
_Counter$GetCount:
label0:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
ldr x27, [x28]
b label1
label1:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Counter$Reset
_Counter$Reset:
label2:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
mov x27, #0
str x27, [x28]
b label3
label3:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Counter$Counter
_Counter$Counter:
label4:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
ldr x27, [x28]
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
add x26, x27, #1
str x26, [x28]
b label5
label5:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Counter$GetValue
_Counter$GetValue:
label6:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
ldr x27, [x28]
b label7
label7:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestStaticFieldViaMethod:
label8:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
b label20
label9:
cmp x28, #0
cset w27, eq
mov w0, w27
bl _Assert
b label18
label10:
cmp x27, #1
cset w26, eq
mov w0, w26
bl _Assert
b label16
label11:
cmp x26, #2
cset w25, eq
mov w0, w25
bl _Assert
b label14
label12:
cmp x25, #0
cset w24, eq
mov w0, w24
bl _Assert
b label21
label13:
adrp x24, _Counter$count@PAGE
add x24, x24, _Counter$count@PAGEOFF
ldr x25, [x24]
b label12
label14:
adrp x24, _Counter$count@PAGE
add x24, x24, _Counter$count@PAGEOFF
mov x25, #0
str x25, [x24]
b label13
label15:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
ldr x26, [x25]
b label11
label16:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
ldr x26, [x25]
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
add x24, x26, #1
str x24, [x25]
b label15
label17:
adrp x24, _Counter$count@PAGE
add x24, x24, _Counter$count@PAGEOFF
ldr x27, [x24]
b label10
label18:
adrp x24, _Counter$count@PAGE
add x24, x24, _Counter$count@PAGEOFF
ldr x27, [x24]
adrp x24, _Counter$count@PAGE
add x24, x24, _Counter$count@PAGEOFF
add x25, x27, #1
str x25, [x24]
b label17
label19:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
ldr x28, [x25]
b label9
label20:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
mov x28, #0
str x28, [x25]
b label19
label21:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestStaticAccessFromInstanceMethod:
label22:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
b label29
label23:
cmp x28, #2
cset w27, eq
mov w0, w27
bl _Assert
b label25
label24:
cmp x27, #2
cset w26, eq
mov w0, w26
bl _Assert
b label30
label25:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x27, [x26]
b label24
label26:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x28, [x26]
b label23
label27:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x28, [x26]
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
add x27, x28, #1
str x27, [x26]
b label26
label28:
adrp x27, _Counter$count@PAGE
add x27, x27, _Counter$count@PAGEOFF
ldr x26, [x27]
adrp x27, _Counter$count@PAGE
add x27, x27, _Counter$count@PAGEOFF
add x28, x26, #1
str x28, [x27]
b label27
label29:
adrp x28, _Counter$count@PAGE
add x28, x28, _Counter$count@PAGEOFF
mov x27, #0
str x27, [x28]
b label28
label30:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _MathUtil$Square__I
_MathUtil$Square__I:
label31:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
mul x27, x28, x28
b label32
label32:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _MathUtil$Add__I__I
_MathUtil$Add__I__I:
label33:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
add x26, x28, x27
b label34
label34:
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _MathUtil$Max__I__I
_MathUtil$Max__I__I:
label35:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
mov x28, x0
mov x27, x1
cmp x28, x27
cset w26, gt
tst w26, w26
b.ne label36
b label37
label36:
mov x26, x28
b label38
label37:
mov x26, x27
b label38
label38:
mov x0, x26
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestStaticMethodsNoState:
label39:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x28, [x29, #-8]
b label40
label40:
mov w0, #1
bl _Assert
b label41
label41:
mov w0, #1
bl _Assert
b label42
label42:
mov w0, #1
bl _Assert
mov x1, #20
mov x0, #10
bl _MathUtil$Max__I__I
mov x28, x0
cmp x28, #20
cset w28, eq
mov w0, w28
bl _Assert
mov x1, #10
mov x0, #20
bl _MathUtil$Max__I__I
mov x28, x0
cmp x28, #20
cset w28, eq
mov w0, w28
bl _Assert
b label43
label43:
ldr x28, [x29, #-8]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Base$GetBaseVal
_Base$GetBaseVal:
label44:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
adrp x28, _Base$base_val@PAGE
add x28, x28, _Base$base_val@PAGEOFF
ldr x27, [x28]
b label45
label45:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _Derived$GetBoth
_Derived$GetBoth:
label46:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
mov x28, x0
adrp x28, _Base$base_val@PAGE
add x28, x28, _Base$base_val@PAGEOFF
ldr x27, [x28]
b label47
label47:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestStaticWithInheritance:
label48:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
adrp x28, _Base$base_val@PAGE
add x28, x28, _Base$base_val@PAGEOFF
ldr x27, [x28]
cmp x27, #100
cset w27, eq
mov w0, w27
bl _Assert
b label52
label49:
cmp x27, #100
cset w28, eq
mov w0, w28
bl _Assert
b label51
label50:
cmp x28, #100
cset w26, eq
mov w0, w26
bl _Assert
b label53
label51:
adrp x26, _Base$base_val@PAGE
add x26, x26, _Base$base_val@PAGEOFF
ldr x28, [x26]
b label50
label52:
adrp x26, _Base$base_val@PAGE
add x26, x26, _Base$base_val@PAGEOFF
ldr x27, [x26]
b label49
label53:
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _Visibility$GetSecret
_Visibility$GetSecret:
label54:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
adrp x28, _Visibility$secret@PAGE
add x28, x28, _Visibility$secret@PAGEOFF
ldr x27, [x28]
b label55
label55:
mov x0, x27
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
_TestStaticVisibility:
label56:
sub sp, sp, #32
stp x29, x30, [sp, #16]
add x29, sp, #16
str x27, [x29, #-8]
str x28, [x29, #-16]
b label58
label57:
cmp x28, #42
cset w27, eq
mov w0, w27
bl _Assert
b label59
label58:
adrp x27, _Visibility$secret@PAGE
add x27, x27, _Visibility$secret@PAGEOFF
ldr x28, [x27]
b label57
label59:
ldr x27, [x29, #-8]
ldr x28, [x29, #-16]
ldp x29, x30, [sp, #16]
add sp, sp, #32
ret
.globl _StaticInit$GetSum
_StaticInit$GetSum:
label60:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x26, [x29, #-8]
str x27, [x29, #-16]
str x28, [x29, #-24]
adrp x28, _StaticInit$a@PAGE
add x28, x28, _StaticInit$a@PAGEOFF
ldr x27, [x28]
adrp x28, _StaticInit$b@PAGE
add x28, x28, _StaticInit$b@PAGEOFF
ldr x26, [x28]
add x28, x27, x26
b label61
label61:
mov x0, x28
ldr x26, [x29, #-8]
ldr x27, [x29, #-16]
ldr x28, [x29, #-24]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
_TestStaticFieldInitializers:
label62:
sub sp, sp, #64
stp x29, x30, [sp, #48]
add x29, sp, #48
str x24, [x29, #-8]
str x25, [x29, #-16]
str x26, [x29, #-24]
str x27, [x29, #-32]
str x28, [x29, #-40]
adrp x28, _StaticInit$a@PAGE
add x28, x28, _StaticInit$a@PAGEOFF
ldr x27, [x28]
cmp x27, #10
cset w27, eq
mov w0, w27
bl _Assert
adrp x27, _StaticInit$b@PAGE
add x27, x27, _StaticInit$b@PAGEOFF
ldr x28, [x27]
cmp x28, #20
cset w28, eq
mov w0, w28
bl _Assert
b label66
label63:
cmp x28, #30
cset w27, eq
mov w0, w27
bl _Assert
adrp x27, _StaticInit$a@PAGE
add x27, x27, _StaticInit$a@PAGEOFF
mov x26, #100
str x26, [x27]
b label65
label64:
cmp x26, #120
cset w27, eq
mov w0, w27
bl _Assert
b label67
label65:
adrp x27, _StaticInit$a@PAGE
add x27, x27, _StaticInit$a@PAGEOFF
ldr x25, [x27]
adrp x27, _StaticInit$b@PAGE
add x27, x27, _StaticInit$b@PAGEOFF
ldr x24, [x27]
add x26, x25, x24
b label64
label66:
adrp x24, _StaticInit$a@PAGE
add x24, x24, _StaticInit$a@PAGEOFF
ldr x26, [x24]
adrp x24, _StaticInit$b@PAGE
add x24, x24, _StaticInit$b@PAGEOFF
ldr x25, [x24]
add x28, x26, x25
b label63
label67:
ldr x24, [x29, #-8]
ldr x25, [x29, #-16]
ldr x26, [x29, #-24]
ldr x27, [x29, #-32]
ldr x28, [x29, #-40]
ldp x29, x30, [sp, #48]
add sp, sp, #64
ret
_TestStaticFieldMutation:
label68:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
str x25, [x29, #-8]
str x26, [x29, #-16]
str x27, [x29, #-24]
str x28, [x29, #-32]
b label79
label69:
cmp x28, #0
cset w27, eq
mov w0, w27
bl _Assert
b label77
label70:
cmp x27, #3
cset w26, eq
mov w0, w26
bl _Assert
b label73
label71:
cmp x26, #0
cset w25, eq
mov w0, w25
bl _Assert
b label80
label72:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
ldr x26, [x25]
b label71
label73:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
mov x26, #0
str x26, [x25]
b label72
label74:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x27, [x26]
b label70
label75:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x27, [x26]
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
add x25, x27, #1
str x25, [x26]
b label74
label76:
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
ldr x26, [x25]
adrp x25, _Counter$count@PAGE
add x25, x25, _Counter$count@PAGEOFF
add x27, x26, #1
str x27, [x25]
b label75
label77:
adrp x27, _Counter$count@PAGE
add x27, x27, _Counter$count@PAGEOFF
ldr x25, [x27]
adrp x27, _Counter$count@PAGE
add x27, x27, _Counter$count@PAGEOFF
add x26, x25, #1
str x26, [x27]
b label76
label78:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
ldr x28, [x26]
b label69
label79:
adrp x26, _Counter$count@PAGE
add x26, x26, _Counter$count@PAGEOFF
mov x28, #0
str x28, [x26]
b label78
label80:
ldr x25, [x29, #-8]
ldr x26, [x29, #-16]
ldr x27, [x29, #-24]
ldr x28, [x29, #-32]
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
.globl _main
_main:
label81:
sub sp, sp, #16
stp x29, x30, [sp, #0]
add x29, sp, #0
bl _TestStaticFieldViaMethod
bl _TestStaticAccessFromInstanceMethod
bl _TestStaticMethodsNoState
bl _TestStaticWithInheritance
bl _TestStaticVisibility
bl _TestStaticFieldInitializers
bl _TestStaticFieldMutation
b label82
label82:
mov x0, #0
ldp x29, x30, [sp, #0]
add sp, sp, #16
ret
