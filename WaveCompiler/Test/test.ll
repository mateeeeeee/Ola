; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@a = internal global [5 x i64] [i64 12, i64 2, i64 3, i64 0, i64 0]

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [5 x i64], align 8
  %2 = getelementptr [5 x i64], ptr %1, i64 0, i64 0
  store i64 12, ptr %2, align 4
  %3 = getelementptr [5 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [5 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = getelementptr [5 x i64], ptr %1, i64 0, i64 3
  store i64 0, ptr %5, align 4
  %6 = getelementptr [5 x i64], ptr %1, i64 0, i64 4
  store i64 0, ptr %6, align 4
  %7 = alloca i64, align 8
  %8 = getelementptr [5 x i64], ptr %1, i64 0, i64 -1
  %9 = load ptr, ptr %8, align 8
  store ptr %9, ptr %7, align 8
  %10 = load ptr, ptr %7, align 8
  store ptr %10, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
