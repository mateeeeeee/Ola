; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare i64 @f(i64)

declare void @PrintInteger(i64)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  call void @PrintInteger(i64 %2)
  %3 = load i64, ptr %1, align 4
  %4 = call i64 @f(i64 %3)
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
