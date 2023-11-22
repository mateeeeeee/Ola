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
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"S::SetY"(ptr %this, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %y, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
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

define internal void @ModifyS(%S %s) {
entry:
  %0 = alloca %S, align 8
  store %S %s, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %2 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %3 = load i64, ptr %2, align 4
  %4 = mul i64 %3, 2
  %5 = load i64, ptr %1, align 4
  store i64 %4, ptr %1, align 4
  %6 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %7 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %8 = load i64, ptr %7, align 4
  %9 = mul i64 %8, 2
  %10 = load i64, ptr %6, align 4
  store i64 %9, ptr %6, align 4
  %11 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %12 = load i64, ptr %11, align 4
  call void @PrintInt(i64 %12)
  %13 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %14 = load i64, ptr %13, align 4
  call void @PrintInt(i64 %14)
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
  %8 = load %S, ptr %1, align 4
  call void @ModifyS(%S %8)
  %9 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %10 = load i64, ptr %9, align 4
  %11 = icmp eq i64 %10, 10
  call void @Assert(i1 %11)
  %12 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %13 = load i64, ptr %12, align 4
  %14 = icmp eq i64 %13, 10
  call void @Assert(i1 %14)
  %15 = call i64 @"S::GetX"(ptr %1)
  %16 = icmp eq i64 %15, 10
  call void @Assert(i1 %16)
  %17 = call i64 @"S::GetY"(ptr %1)
  %18 = icmp eq i64 %17, 10
  call void @Assert(i1 %18)
  %19 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %20 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %21 = load i64, ptr %20, align 4
  %22 = add i64 %21, 10
  %23 = load i64, ptr %19, align 4
  store i64 %22, ptr %19, align 4
  %24 = call i64 @"S::GetX"(ptr %1)
  %25 = icmp eq i64 %24, 20
  call void @Assert(i1 %25)
  %26 = call i64 @"S::GetX"(ptr %1)
  %27 = icmp eq i64 %26, 20
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
