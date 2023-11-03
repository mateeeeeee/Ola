; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

define internal void @f(ptr %arr) {
entry:
  %0 = getelementptr inbounds i64, ptr %arr, i64 0
  %1 = load i64, ptr %0, align 4
  store i64 10, ptr %0, align 4
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
  %5 = getelementptr inbounds i64, ptr %1, i64 0
  call void @f(ptr %5)
  %6 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  %7 = load ptr, ptr %6, align 8
  store ptr %7, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %8 = load i64, ptr %0, align 4
  ret i64 %8
}
