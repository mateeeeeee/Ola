; ModuleID = 'test.ola'
source_filename = "test.ola"

@globalString = internal constant [7 x i8] c"global\00"
@__StringLiteral0 = internal constant [6 x i8] c"local\00"
@__StringLiteral1 = internal constant [8 x i8] c"Literal\00"
@__StringLiteral2 = internal constant [6 x i8] c"12345\00"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare i1 @IsAlnum(i8)

declare i1 @IsAlpha(i8)

declare i1 @IsLower(i8)

declare i1 @IsUpper(i8)

declare i1 @IsDigit(i8)

declare i1 @IsSpace(i8)

declare i8 @ToLower(i8)

declare i8 @ToUpper(i8)

declare double @StringToFloat(ptr)

declare i64 @StringToInt(ptr)

declare void @StringCopy(ptr, ptr, i64)

define internal void @PassStringLiteral__C0(ptr %literal) {
entry:
  %0 = alloca ptr, align 8
  store ptr %literal, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds i64, ptr %1, i64 0
  %3 = load i8, ptr %2, align 1
  %4 = icmp eq i8 %3, 76
  call void @Assert(i1 %4)
  %5 = load ptr, ptr %0, align 8
  %6 = getelementptr inbounds i64, ptr %5, i64 1
  %7 = load i8, ptr %6, align 1
  %8 = icmp eq i8 %7, 105
  call void @Assert(i1 %8)
  %9 = load ptr, ptr %0, align 8
  %10 = getelementptr inbounds i64, ptr %9, i64 2
  %11 = load i8, ptr %10, align 1
  %12 = icmp eq i8 %11, 116
  call void @Assert(i1 %12)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @PassStringVariable__C0(ptr %variable) {
entry:
  %0 = alloca ptr, align 8
  store ptr %variable, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds i64, ptr %1, i64 0
  %3 = load i8, ptr %2, align 1
  %4 = icmp eq i8 %3, 108
  call void @Assert(i1 %4)
  %5 = load ptr, ptr %0, align 8
  %6 = getelementptr inbounds i64, ptr %5, i64 1
  %7 = load i8, ptr %6, align 1
  %8 = icmp eq i8 %7, 111
  call void @Assert(i1 %8)
  %9 = load ptr, ptr %0, align 8
  %10 = getelementptr inbounds i64, ptr %9, i64 2
  %11 = load i8, ptr %10, align 1
  %12 = icmp eq i8 %11, 99
  call void @Assert(i1 %12)
  %13 = load ptr, ptr %0, align 8
  %14 = getelementptr inbounds i64, ptr %13, i64 3
  %15 = load i8, ptr %14, align 1
  %16 = icmp eq i8 %15, 97
  call void @Assert(i1 %16)
  %17 = load ptr, ptr %0, align 8
  %18 = getelementptr inbounds i64, ptr %17, i64 4
  %19 = load i8, ptr %18, align 1
  %20 = icmp eq i8 %19, 108
  call void @Assert(i1 %20)
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
  %11 = getelementptr inbounds i64, ptr %10, i64 0
  %12 = load i8, ptr %11, align 1
  %13 = icmp eq i8 %12, 108
  call void @Assert(i1 %13)
  call void @PassStringLiteral__C0(ptr @__StringLiteral1)
  call void @PassStringVariable__C0(ptr %1)
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
  %21 = call i64 @StringToInt(ptr %14)
  %22 = alloca i64, align 8
  store i64 %21, ptr %22, align 4
  %23 = load i64, ptr %22, align 4
  %24 = icmp eq i64 %23, 12345
  call void @Assert(i1 %24)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %25 = load i64, ptr %0, align 4
  ret i64 %25
}
