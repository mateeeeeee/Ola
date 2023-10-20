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
  %3 = load i64, ptr %2, align 4
  %4 = srem i64 %3, 2
  %if.cond = icmp ne i64 %4, 0
  br i1 %if.cond, label %if.then, label %if.end

for.end:                                          ; preds = %for.cond
  %5 = load ptr, ptr %1, align 8
  store ptr %5, ptr %0, align 8
  br label %exit

for.cond:                                         ; preds = %for.iter, %entry
  %6 = load i64, ptr %2, align 4
  %7 = icmp slt i64 %6, 10
  br i1 %7, label %for.body, label %for.end

for.iter:                                         ; preds = %if.end, %if.then
  %8 = load i64, ptr %2, align 4
  %9 = add i64 %8, 1
  store i64 %9, ptr %2, align 4
  br label %for.cond

if.then:                                          ; preds = %for.body
  br label %for.iter

if.end:                                           ; preds = %continue, %for.body
  %10 = load i64, ptr %1, align 4
  %11 = add i64 %10, 2
  %12 = load i64, ptr %1, align 4
  store i64 %11, ptr %1, align 4
  br label %for.iter

exit:                                             ; preds = %for.end
  %13 = load i64, ptr %0, align 4
  ret i64 %13
}
