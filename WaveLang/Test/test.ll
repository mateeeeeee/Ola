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
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %3, 2
  %5 = load i64, ptr %1, align 4
  store i64 %4, ptr %1, align 4
  %6 = load i64, ptr %2, align 4
  %7 = add i64 %6, 1
  store i64 %7, ptr %2, align 4
  br label %for.iter

for.end:                                          ; preds = %for.cond
  %8 = load ptr, ptr %1, align 8
  store ptr %8, ptr %0, align 8
  br label %exit

for.cond:                                         ; preds = %for.iter, %entry
  %9 = load i64, ptr %2, align 4
  %10 = icmp slt i64 %9, 10
  br i1 %10, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  br label %for.cond

exit:                                             ; preds = %for.end
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
