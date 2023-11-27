; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

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
  %5 = alloca ptr, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds [3 x i64], ptr %1, i64 0, i64 0
  %8 = getelementptr inbounds [3 x i64], ptr %1, i64 0, i64 0
  store ptr %8, ptr %5, align 8
  %9 = getelementptr [3 x i64], ptr %1, i64 0, i64 2
  %10 = load i64, ptr %9, align 4
  store i64 100, ptr %9, align 4
  %11 = load ptr, ptr %5, align 8
  %12 = getelementptr inbounds ptr, ptr %11, i64 2
  %13 = load ptr, ptr %12, align 8
  store ptr %13, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %14 = load i64, ptr %0, align 4
  ret i64 %14
}
