; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@int2d = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]

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
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca ptr, align 8
  store ptr @int2d, ptr %2, align 8
  %3 = alloca ptr, align 8
  store ptr getelementptr inbounds (ptr, ptr @int2d, i64 1), ptr %3, align 8
  %4 = load ptr, ptr %2, align 8
  %5 = getelementptr inbounds ptr, ptr %4, i64 0
  %6 = load i64, ptr %5, align 4
  call void @PrintInteger(i64 %6)
  %7 = load ptr, ptr %2, align 8
  %8 = getelementptr inbounds ptr, ptr %7, i64 1
  %9 = load i64, ptr %8, align 4
  call void @PrintInteger(i64 %9)
  %10 = load ptr, ptr %3, align 8
  %11 = getelementptr inbounds ptr, ptr %10, i64 0
  %12 = load i64, ptr %11, align 4
  call void @PrintInteger(i64 %12)
  %13 = load ptr, ptr %3, align 8
  %14 = getelementptr inbounds ptr, ptr %13, i64 1
  %15 = load i64, ptr %14, align 4
  call void @PrintInteger(i64 %15)
  %16 = load ptr, ptr %1, align 8
  store ptr %16, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %17 = load i64, ptr %0, align 4
  ret i64 %17
}
