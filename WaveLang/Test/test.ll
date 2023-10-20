; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %3 = load i64, ptr %2, align 4
  %4 = icmp slt i64 %3, 10
  br i1 %4, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %5 = load i64, ptr %2, align 4
  %6 = add i64 %5, 1
  store i64 %6, ptr %2, align 4
  %7 = load i64, ptr %1, align 4
  %8 = add i64 %7, 2
  %9 = load i64, ptr %1, align 4
  store i64 %8, ptr %1, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %10 = load ptr, ptr %1, align 8
  store ptr %10, ptr %0, align 8
  br label %exit

exit:                                             ; preds = %for.end
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
