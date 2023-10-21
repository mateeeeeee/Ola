; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  %3 = load i64, ptr %2, align 4
  %4 = alloca ptr, align 8
  %5 = load ptr, ptr %2, align 8
  store ptr %5, ptr %4, align 8
  %6 = add i64 %3, 1
  store i64 %6, ptr %2, align 4
  %7 = load i64, ptr %2, align 4
  %8 = icmp slt i64 %7, 5
  br i1 %8, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 0, ptr %0, align 4
  br label %exit

if.else:                                          ; preds = %entry
  store i64 5, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %if.end, %if.else, %if.then
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
