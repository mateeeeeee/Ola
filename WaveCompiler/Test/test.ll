; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@g = internal global i64 9

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

define internal ptr @ReturnRef() {
entry:
  %0 = alloca ptr, align 8
  %1 = load i64, ptr @g, align 4
  store ptr @g, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load ptr, ptr %0, align 8
  ret ptr %2
}

define internal i64 @ReturnValue() {
entry:
  %0 = alloca i64, align 8
  store ptr @g, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}

define internal void @TestRefReturnSimple() {
entry:
  %0 = call ptr @ReturnRef()
  %1 = load ptr, ptr %0, align 8
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = load i64, ptr %3, align 4
  %5 = alloca ptr, align 8
  %6 = load ptr, ptr %3, align 8
  store ptr %6, ptr %5, align 8
  %7 = add i64 %4, 1
  store i64 %7, ptr %3, align 4
  %8 = load i64, ptr @g, align 4
  %9 = icmp eq i64 %8, 10
  call void @Assert(i1 %9)
  %10 = call ptr @ReturnRef()
  %11 = load ptr, ptr %10, align 8
  %12 = load i64, ptr %10, align 4
  %13 = alloca i64, align 8
  store i64 %12, ptr %13, align 4
  %14 = load i64, ptr %13, align 4
  %15 = alloca ptr, align 8
  %16 = load ptr, ptr %13, align 8
  store ptr %16, ptr %15, align 8
  %17 = add i64 %14, 1
  store i64 %17, ptr %13, align 4
  %18 = load i64, ptr @g, align 4
  %19 = icmp eq i64 %18, 10
  call void @Assert(i1 %19)
  %20 = call i64 @ReturnValue()
  %21 = alloca i64, align 8
  store i64 %20, ptr %21, align 4
  %22 = load i64, ptr %21, align 4
  %23 = alloca ptr, align 8
  %24 = load ptr, ptr %21, align 8
  store ptr %24, ptr %23, align 8
  %25 = add i64 %22, 1
  store i64 %25, ptr %21, align 4
  %26 = load i64, ptr @g, align 4
  %27 = icmp eq i64 %26, 10
  call void @Assert(i1 %27)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestRefReturnSimple()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
