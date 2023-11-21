; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64, i64 }

@__StringLiteral0 = internal constant [2 x i8] c"1\00"
@__StringLiteral1 = internal constant [2 x i8] c"2\00"
@__StringLiteral2 = internal constant [2 x i8] c"3\00"
@__StringLiteral3 = internal constant [2 x i8] c"4\00"
@__StringLiteral4 = internal constant [2 x i8] c"5\00"
@__StringLiteral5 = internal constant [2 x i8] c"6\00"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"S::SetX"(ptr %this, i64 %x) {
entry:
  %0 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %1 = load i64, ptr %0, align 4
  store i64 %x, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"S::SetY"(ptr %this, i64 %y) {
entry:
  %0 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %1 = load i64, ptr %0, align 4
  store i64 %y, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @"S::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define i64 @"S::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define internal void @ModifyS(ptr %s) {
entry:
  %0 = getelementptr inbounds %S, ptr %s, i32 0, i32 0
  %1 = getelementptr inbounds %S, ptr %s, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = mul i64 %2, 2
  %4 = load i64, ptr %0, align 4
  store i64 %3, ptr %0, align 4
  %5 = getelementptr inbounds %S, ptr %s, i32 0, i32 1
  %6 = getelementptr inbounds %S, ptr %s, i32 0, i32 1
  %7 = load i64, ptr %6, align 4
  %8 = mul i64 %7, 2
  %9 = load i64, ptr %5, align 4
  store i64 %8, ptr %5, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  store i64 0, ptr %2, align 4
  %3 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  store i64 0, ptr %3, align 4
  %4 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %5 = load i64, ptr %4, align 4
  store i64 10, ptr %4, align 4
  %6 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %7 = load i64, ptr %6, align 4
  store i64 10, ptr %6, align 4
  call void @ModifyS(ptr %1)
  %8 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %9 = load i64, ptr %8, align 4
  %10 = icmp eq i64 %9, 20
  call void @AssertMsg(i1 %10, ptr @__StringLiteral0)
  %11 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 20
  call void @AssertMsg(i1 %13, ptr @__StringLiteral1)
  %14 = call i64 @"S::GetX"(ptr %1)
  %15 = icmp eq i64 %14, 20
  call void @AssertMsg(i1 %15, ptr @__StringLiteral2)
  %16 = call i64 @"S::GetY"(ptr %1)
  %17 = icmp eq i64 %16, 20
  call void @AssertMsg(i1 %17, ptr @__StringLiteral3)
  %18 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %19 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %20 = load i64, ptr %19, align 4
  %21 = add i64 %20, 10
  %22 = load i64, ptr %18, align 4
  store i64 %21, ptr %18, align 4
  %23 = call i64 @"S::GetX"(ptr %1)
  %24 = icmp eq i64 %23, 20
  call void @AssertMsg(i1 %24, ptr @__StringLiteral4)
  %25 = call i64 @"S::GetX"(ptr %1)
  %26 = icmp eq i64 %25, 30
  call void @AssertMsg(i1 %26, ptr @__StringLiteral5)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %27 = load i64, ptr %0, align 4
  ret i64 %27
}
