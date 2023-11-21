; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

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
  call void @Assert(i1 %10)
  %11 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 20
  call void @Assert(i1 %13)
  %14 = alloca %S, align 8
  %15 = load ptr, ptr %1, align 8
  store ptr %15, ptr %14, align 8
  %16 = call i64 @"S::GetY"(ptr %1)
  call void @PrintInt(i64 %16)
  %17 = call i64 @"S::GetX"(ptr %14)
  %18 = icmp eq i64 %17, 20
  call void @Assert(i1 %18)
  %19 = getelementptr inbounds %S, ptr %14, i32 0, i32 0
  %20 = getelementptr inbounds %S, ptr %14, i32 0, i32 0
  %21 = load i64, ptr %20, align 4
  %22 = add i64 %21, 10
  %23 = load i64, ptr %19, align 4
  store i64 %22, ptr %19, align 4
  %24 = call i64 @"S::GetX"(ptr %1)
  %25 = icmp eq i64 %24, 20
  call void @Assert(i1 %25)
  %26 = call i64 @"S::GetX"(ptr %14)
  %27 = icmp eq i64 %26, 30
  call void @Assert(i1 %27)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %28 = load i64, ptr %0, align 4
  ret i64 %28
}
