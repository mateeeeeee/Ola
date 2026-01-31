
.text

.globl _main
_main:
label0:
sub sp, sp, #48
stp x29, x30, [sp, #32]
add x29, sp, #32
b label2
label1:
label2:
mov x0, #30
ldp x29, x30, [sp, #32]
add sp, sp, #48
ret
