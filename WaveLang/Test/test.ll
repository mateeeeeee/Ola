; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 5
  %4 = load i64, ptr %1, align 4
  store i64 %3, ptr %1, align 4
  %5 = alloca i64, align 8
  store i64 5, ptr %5, align 4
  %6 = load i64, ptr %1, align 4
  %7 = load i64, ptr %5, align 4
  %8 = icmp ne i64 %6, %7
  br i1 %8, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %9 = load i64, ptr %1, align 4
  %10 = add i64 %9, 1
  store i64 %10, ptr %1, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %11 = load ptr, ptr %1, align 8
  store ptr %11, ptr %0, align 8
  br label %exit

exit:                                             ; preds = %if.end
  %12 = load i64, ptr %0, align 4
  ret i64 %12
}
