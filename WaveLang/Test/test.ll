; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = alloca ptr, align 8
  %4 = load ptr, ptr %1, align 8
  store ptr %4, ptr %3, align 8
  %5 = add i64 %2, 1
  store i64 %5, ptr %1, align 4
  %6 = load i64, ptr %3, align 4
  %ifcond = icmp ne i64 %6, 0
  br i1 %ifcond, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %7 = load ptr, ptr %1, align 8
  store ptr %7, ptr %0, align 8
  br label %exit

if.end:                                           ; preds = %return, %entry
  %8 = load i64, ptr %1, align 4
  %9 = mul i64 %8, 2
  store i64 %9, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %if.end, %if.then
  %10 = load i64, ptr %0, align 4
  ret i64 %10
}
