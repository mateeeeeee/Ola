; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca double, align 8
  store double 2.300000e+00, ptr %1, align 8
  %2 = load double, ptr %1, align 8
  %3 = fadd double %2, 1.000000e+00
  store double %3, ptr %1, align 8
  %4 = load double, ptr %1, align 8
  %5 = fptosi double %4 to i64
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
