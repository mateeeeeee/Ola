; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare i1 @IsAlnum(i8)

declare i1 @IsAlpha(i8)

declare i1 @IsLower(i8)

declare i1 @IsUpper(i8)

declare i1 @IsDigit(i8)

declare i1 @IsSpace(i8)

declare i8 @ToLower(i8)

declare i8 @ToUpper(i8)

declare double @StringToFloat(ptr)

declare i64 @StringToInteger(ptr)

declare void @StringCopy(ptr, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [2 x [2 x i64]], align 8
  %2 = getelementptr [2 x [2 x i64]], ptr %1, i64 0, i64 0
  store [2 x i64] zeroinitializer, ptr %2, align 4
  %3 = getelementptr [2 x [2 x i64]], ptr %1, i64 0, i64 1
  store [2 x i64] zeroinitializer, ptr %3, align 4
  %4 = getelementptr [2 x [2 x i64]], ptr %1, i64 0, i64 0
  %5 = getelementptr inbounds ptr, ptr %4, i64 0
  %6 = load i64, ptr %5, align 4
  store i64 5, ptr %5, align 4
  %7 = getelementptr [2 x [2 x i64]], ptr %1, i64 0, i64 0
  %8 = getelementptr inbounds ptr, ptr %7, i64 0
  %9 = load ptr, ptr %8, align 8
  store ptr %9, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %10 = load i64, ptr %0, align 4
  ret i64 %10
}
