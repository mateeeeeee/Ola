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
  %1 = alloca [16 x i8], align 1
  %2 = getelementptr [16 x i8], ptr %1, i64 0, i64 0
  store i8 0, ptr %2, align 1
  %3 = getelementptr [16 x i8], ptr %1, i64 0, i64 1
  store i8 0, ptr %3, align 1
  %4 = getelementptr [16 x i8], ptr %1, i64 0, i64 2
  store i8 0, ptr %4, align 1
  %5 = getelementptr [16 x i8], ptr %1, i64 0, i64 3
  store i8 0, ptr %5, align 1
  %6 = getelementptr [16 x i8], ptr %1, i64 0, i64 4
  store i8 0, ptr %6, align 1
  %7 = getelementptr [16 x i8], ptr %1, i64 0, i64 5
  store i8 0, ptr %7, align 1
  %8 = getelementptr [16 x i8], ptr %1, i64 0, i64 6
  store i8 0, ptr %8, align 1
  %9 = getelementptr [16 x i8], ptr %1, i64 0, i64 7
  store i8 0, ptr %9, align 1
  %10 = getelementptr [16 x i8], ptr %1, i64 0, i64 8
  store i8 0, ptr %10, align 1
  %11 = getelementptr [16 x i8], ptr %1, i64 0, i64 9
  store i8 0, ptr %11, align 1
  %12 = getelementptr [16 x i8], ptr %1, i64 0, i64 10
  store i8 0, ptr %12, align 1
  %13 = getelementptr [16 x i8], ptr %1, i64 0, i64 11
  store i8 0, ptr %13, align 1
  %14 = getelementptr [16 x i8], ptr %1, i64 0, i64 12
  store i8 0, ptr %14, align 1
  %15 = getelementptr [16 x i8], ptr %1, i64 0, i64 13
  store i8 0, ptr %15, align 1
  %16 = getelementptr [16 x i8], ptr %1, i64 0, i64 14
  store i8 0, ptr %16, align 1
  %17 = getelementptr [16 x i8], ptr %1, i64 0, i64 15
  store i8 0, ptr %17, align 1
  %18 = getelementptr inbounds [16 x i8], ptr %1, i64 0, i64 0
  call void @ReadString(ptr %18, i64 16)
  %19 = alloca ptr, align 8
  %20 = getelementptr inbounds [16 x i8], ptr %1, i64 0, i64 0
  store ptr %20, ptr %19, align 8
  %21 = load ptr, ptr %19, align 8
  call void @PrintString(ptr %21)
  br label %exit

exit:                                             ; preds = %entry
  %22 = load i64, ptr %0, align 4
  ret i64 %22
}
