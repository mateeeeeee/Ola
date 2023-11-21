; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = alloca i64, align 8
  store i64 %2, ptr %3, align 4
  %4 = alloca ptr, align 8
  %5 = load ptr, ptr %3, align 8
  store ptr %5, ptr %4, align 8
  %6 = load ptr, ptr %4, align 8
  %7 = add ptr %6, i0 0
  store ptr %7, ptr %4, align 8
  %8 = load ptr, ptr %4, align 8
  %9 = load i64, ptr %8, align 4
  store i64 %9, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %10 = load i64, ptr %0, align 4
  ret i64 %10
}
