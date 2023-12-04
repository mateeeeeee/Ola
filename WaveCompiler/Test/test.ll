; ModuleID = 'test.wv'
source_filename = "test.wv"

define internal i64 @add(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = load i64, ptr %0, align 4
  %4 = load i64, ptr %1, align 4
  %5 = add i64 %3, %4
  store i64 %5, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %2, align 4
  ret i64 %6
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @add(i64 5, i64 5)
  %2 = alloca i64, align 8
  store i64 %1, ptr %2, align 4
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
