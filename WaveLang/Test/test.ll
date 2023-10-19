; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 100, ptr %1, align 4
  %2 = alloca i1, align 1
  %3 = load i64, ptr %1, align 4
  %4 = icmp ne i64 %3, 0
  store i1 %4, ptr %2, align 1
  %5 = load i1, ptr %2, align 1
  %6 = zext i1 %5 to i64
  store i64 %6, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
