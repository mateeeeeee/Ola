; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@a = internal global i64 0

define i64 @f(i64 %a) {
entry:
  %0 = alloca i64, align 8
  %1 = mul i64 2, %a
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 7, ptr %2, align 4
  %3 = load i64, ptr @a, align 4
  %4 = load i64, ptr %1, align 4
  %5 = add i64 %3, %4
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
