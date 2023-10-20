; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %3, 2
  %5 = load i64, ptr %1, align 4
  store i64 %4, ptr %1, align 4
  br label %dowhile.cond

dowhile.cond:                                     ; preds = %dowhile.body
  br i1 false, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %6 = load ptr, ptr %1, align 8
  store ptr %6, ptr %0, align 8
  br label %exit

exit:                                             ; preds = %dowhile.end
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
