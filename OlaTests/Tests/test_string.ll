; ModuleID = 'test_string.ola'
source_filename = "test_string.ola"

@globalString = internal global [7 x i8] c"global\00"
@__StringLiteral0 = internal constant [6 x i8] c"local\00"
@__StringLiteral1 = internal constant [8 x i8] c"Literal\00"
@__StringLiteral2 = internal constant [9 x i8] c"Variable\00"
@__StringLiteral3 = internal constant [6 x i8] c"12345\00"

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

define internal void @PassStringLiteral(ptr %literal) {
entry:
  %0 = load i8, ptr %literal, align 1
  %1 = icmp eq i8 %0, 76
  tail call void @Assert(i1 %1)
  ret void
}

define internal void @PassStringVariable(ptr %variable) {
entry:
  %0 = load i8, ptr %variable, align 1
  %1 = icmp eq i8 %0, 86
  tail call void @Assert(i1 %1)
  ret void
}

define i64 @main() {
entry:
  tail call void @Assert(i1 true)
  %0 = alloca [6 x i8], align 1
  store i8 108, ptr %0, align 1
  %1 = getelementptr inbounds [6 x i8], ptr %0, i64 0, i64 1
  store i8 111, ptr %1, align 1
  %2 = getelementptr inbounds [6 x i8], ptr %0, i64 0, i64 2
  store i8 99, ptr %2, align 1
  %3 = getelementptr inbounds [6 x i8], ptr %0, i64 0, i64 3
  store i8 97, ptr %3, align 1
  %4 = getelementptr inbounds [6 x i8], ptr %0, i64 0, i64 4
  store i8 108, ptr %4, align 1
  %5 = getelementptr inbounds [6 x i8], ptr %0, i64 0, i64 5
  store i8 0, ptr %5, align 1
  tail call void @Assert(i1 true)
  %6 = load i8, ptr %0, align 1
  %7 = icmp eq i8 %6, 108
  call void @Assert(i1 %7)
  call void @PassStringLiteral(ptr nonnull @__StringLiteral1)
  call void @PassStringVariable(ptr nonnull @__StringLiteral2)
  %8 = alloca [6 x i8], align 1
  store i8 49, ptr %8, align 1
  %9 = getelementptr inbounds [6 x i8], ptr %8, i64 0, i64 1
  store i8 50, ptr %9, align 1
  %10 = getelementptr inbounds [6 x i8], ptr %8, i64 0, i64 2
  store i8 51, ptr %10, align 1
  %11 = getelementptr inbounds [6 x i8], ptr %8, i64 0, i64 3
  store i8 52, ptr %11, align 1
  %12 = getelementptr inbounds [6 x i8], ptr %8, i64 0, i64 4
  store i8 53, ptr %12, align 1
  %13 = getelementptr inbounds [6 x i8], ptr %8, i64 0, i64 5
  store i8 0, ptr %13, align 1
  %14 = call i64 @StringToInt(ptr nonnull %8)
  %15 = icmp eq i64 %14, 12345
  call void @Assert(i1 %15)
  ret i64 0
}
