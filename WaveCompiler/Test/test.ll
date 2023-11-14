; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@globalString = internal global [7 x i8] c"global\00"
@__StringLiteral0 = internal constant [6 x i8] c"local\00"
@__StringLiteral1 = internal constant [8 x i8] c"Literal\00"
@__StringLiteral2 = internal constant [9 x i8] c"Variable\00"
@__StringLiteral3 = internal constant [6 x i8] c"12345\00"

declare void @Assert(i1)

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

define internal void @PassStringLiteral(ptr %literal) {
entry:
  %0 = getelementptr inbounds ptr, ptr %literal, i64 0
  %1 = load i8, ptr %0, align 1
  %2 = icmp eq i8 %1, 76
  call void @Assert(i1 %2)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @PassStringVariable(ptr %variable) {
entry:
  %0 = getelementptr inbounds ptr, ptr %variable, i64 0
  %1 = load i8, ptr %0, align 1
  %2 = icmp eq i8 %1, 86
  call void @Assert(i1 %2)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @Assert(i1 true)
  %1 = alloca [6 x i8], align 1
  %2 = getelementptr [6 x i8], ptr %1, i64 0, i64 0
  store i8 108, ptr %2, align 1
  %3 = getelementptr [6 x i8], ptr %1, i64 0, i64 1
  store i8 111, ptr %3, align 1
  %4 = getelementptr [6 x i8], ptr %1, i64 0, i64 2
  store i8 99, ptr %4, align 1
  %5 = getelementptr [6 x i8], ptr %1, i64 0, i64 3
  store i8 97, ptr %5, align 1
  %6 = getelementptr [6 x i8], ptr %1, i64 0, i64 4
  store i8 108, ptr %6, align 1
  %7 = getelementptr [6 x i8], ptr %1, i64 0, i64 5
  store i8 0, ptr %7, align 1
  call void @Assert(i1 true)
  %8 = alloca ptr, align 8
  %9 = getelementptr inbounds [6 x i8], ptr %1, i64 0, i64 0
  store ptr %9, ptr %8, align 8
  %10 = load ptr, ptr %8, align 8
  %11 = getelementptr inbounds ptr, ptr %10, i64 0
  %12 = load i8, ptr %11, align 1
  %13 = icmp eq i8 %12, 108
  call void @Assert(i1 %13)
  call void @PassStringLiteral(ptr @__StringLiteral1)
  call void @PassStringVariable(ptr @__StringLiteral2)
  %14 = alloca [6 x i8], align 1
  %15 = getelementptr [6 x i8], ptr %14, i64 0, i64 0
  store i8 49, ptr %15, align 1
  %16 = getelementptr [6 x i8], ptr %14, i64 0, i64 1
  store i8 50, ptr %16, align 1
  %17 = getelementptr [6 x i8], ptr %14, i64 0, i64 2
  store i8 51, ptr %17, align 1
  %18 = getelementptr [6 x i8], ptr %14, i64 0, i64 3
  store i8 52, ptr %18, align 1
  %19 = getelementptr [6 x i8], ptr %14, i64 0, i64 4
  store i8 53, ptr %19, align 1
  %20 = getelementptr [6 x i8], ptr %14, i64 0, i64 5
  store i8 0, ptr %20, align 1
  %21 = getelementptr inbounds [6 x i8], ptr %14, i64 0, i64 0
  %22 = call i64 @StringToInteger(ptr %21)
  %23 = alloca i64, align 8
  store i64 %22, ptr %23, align 4
  %24 = load i64, ptr %23, align 4
  %25 = icmp eq i64 %24, 12345
  call void @Assert(i1 %25)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %26 = load i64, ptr %0, align 4
  ret i64 %26
}
