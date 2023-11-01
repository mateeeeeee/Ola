; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@global_arr = internal global [5 x i64] [i64 1, i64 2, i64 3, i64 0, i64 0]

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [10 x i64], align 8
  %2 = getelementptr [10 x i64], ptr %1, i64 0, i64 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr [10 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [10 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = alloca i64, align 8
  store i64 10, ptr %5, align 4
  store i64 10, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
