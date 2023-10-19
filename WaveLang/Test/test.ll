; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  %3 = alloca i64, align 8
  store i64 0, ptr %3, align 4
  %4 = load i64, ptr %1, align 4
  %5 = alloca ptr, align 8
  %6 = load ptr, ptr %1, align 8
  store ptr %6, ptr %5, align 8
  %7 = add i64 %4, 1
  store i64 %7, ptr %1, align 4
  %8 = load i64, ptr %5, align 4
  %ifcond = icmp ne i64 %8, 0
  br i1 %ifcond, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %9 = load ptr, ptr %1, align 8
  store ptr %9, ptr %0, align 8
  br label %exit

if.end:                                           ; preds = %return, %entry
  %10 = load i64, ptr %1, align 4
  %11 = mul i64 %10, 2
  store i64 %11, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %if.end, %if.then
  %12 = load i64, ptr %0, align 4
  ret i64 %12
}
