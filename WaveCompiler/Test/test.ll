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
  %10 = call i64 @ReturnValue()
  %11 = alloca ptr, align 8
  store i64 %10, ptr %11, align 4
  %12 = load ptr, ptr %11, align 8
  %13 = load i64, ptr %12, align 4
  %14 = alloca ptr, align 8
  %15 = load ptr, ptr %12, align 8
  store ptr %15, ptr %14, align 8
  %16 = add i64 %13, 1
  store i64 %16, ptr %12, align 4
  %17 = load i64, ptr @g, align 4
  %18 = icmp eq i64 %17, 10
  call void @Assert(i1 %18)
  %19 = call ptr @ReturnRef()
  %20 = load ptr, ptr %19, align 8
  %21 = load i64, ptr %19, align 4
  %22 = alloca i64, align 8
  store i64 %21, ptr %22, align 4
  %23 = load i64, ptr %22, align 4
  %24 = alloca ptr, align 8
  %25 = load ptr, ptr %22, align 8
  store ptr %25, ptr %24, align 8
  %26 = add i64 %23, 1
  store i64 %26, ptr %22, align 4
  %27 = load i64, ptr @g, align 4
  %28 = icmp eq i64 %27, 10
  call void @Assert(i1 %28)
  %29 = call i64 @ReturnValue()
  %30 = alloca i64, align 8
  store i64 %29, ptr %30, align 4
  %31 = load i64, ptr %30, align 4
  %32 = alloca ptr, align 8
  %33 = load ptr, ptr %30, align 8
  store ptr %33, ptr %32, align 8
  %34 = add i64 %31, 1
  store i64 %34, ptr %30, align 4
  %35 = load i64, ptr @g, align 4
  %36 = icmp eq i64 %35, 10
  call void @Assert(i1 %36)
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
