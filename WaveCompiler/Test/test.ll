; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @FooByRef(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 1
  store i64 %3, ptr %1, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @FooByValue(i64 %a) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = add i64 %1, 1
  store i64 %2, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestRefSimple() {
entry:
  %0 = alloca i64, align 8
  store i64 9, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  call void @FooByRef(ptr %0)
  %2 = load i64, ptr %0, align 4
  %3 = icmp eq i64 %2, 10
  call void @Assert(i1 %3)
  %4 = load i64, ptr %0, align 4
  %5 = alloca ptr, align 8
  store ptr %0, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = load i64, ptr %6, align 4
  %8 = add i64 %7, 1
  store i64 %8, ptr %6, align 4
  %9 = load i64, ptr %0, align 4
  %10 = icmp eq i64 %9, 11
  call void @Assert(i1 %10)
  %11 = load ptr, ptr %6, align 8
  %12 = load i64, ptr %6, align 4
  %13 = alloca i64, align 8
  store i64 %12, ptr %13, align 4
  %14 = load i64, ptr %13, align 4
  %15 = add i64 %14, 1
  store i64 %15, ptr %13, align 4
  %16 = load i64, ptr %13, align 4
  %17 = icmp eq i64 %16, 12
  call void @Assert(i1 %17)
  %18 = load i64, ptr %0, align 4
  %19 = icmp eq i64 %18, 11
  call void @Assert(i1 %19)
  %20 = load ptr, ptr %6, align 8
  %21 = alloca ptr, align 8
  store ptr %6, ptr %21, align 8
  %22 = load ptr, ptr %21, align 8
  %23 = load i64, ptr %22, align 4
  %24 = add i64 %23, 1
  store i64 %24, ptr %22, align 4
  %25 = load i64, ptr %0, align 4
  %26 = icmp eq i64 %25, 12
  call void @Assert(i1 %26)
  %27 = load ptr, ptr %22, align 8
  call void @FooByRef(ptr %22)
  %28 = load i64, ptr %0, align 4
  %29 = icmp eq i64 %28, 13
  call void @Assert(i1 %29)
  %30 = load ptr, ptr %22, align 8
  %31 = load i64, ptr %22, align 4
  call void @FooByValue(i64 %31)
  %32 = load i64, ptr %0, align 4
  %33 = icmp eq i64 %32, 13
  call void @Assert(i1 %33)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestRefSimple()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
