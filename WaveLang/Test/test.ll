; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define internal i64 @add(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  %1 = add i64 %a, %b
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
  %2 = call i64 @add(i64 2, i64 3)
  store i64 %2, ptr %1, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %3, 5
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
