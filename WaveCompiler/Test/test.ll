; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define internal void @f(ptr %a, i64 %size) {
entry:
  %0 = getelementptr inbounds i64, ptr %a, i64 0
  %1 = load i64, ptr %0, align 4
  store i64 100, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [3 x i64], align 8
  %2 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr [3 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [3 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  %6 = load i64, ptr %5, align 4
  store i64 10, ptr %5, align 4
  %7 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
