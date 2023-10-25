; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  %2 = load i64, ptr %1, align 4
  store i64 47, ptr %1, align 4
  %3 = load i64, ptr %1, align 4
  %4 = icmp eq i64 %3, 47
  call void @Assert(i1 %4)
  %5 = load i64, ptr %1, align 4
  store i64 15, ptr %1, align 4
  %6 = load i64, ptr %1, align 4
  %7 = icmp eq i64 %6, 15
  call void @Assert(i1 %7)
  %8 = load i64, ptr %1, align 4
  store i64 4, ptr %1, align 4
  %9 = load i64, ptr %1, align 4
  %10 = icmp eq i64 %9, 4
  call void @Assert(i1 %10)
  %11 = load i64, ptr %1, align 4
  store i64 6, ptr %1, align 4
  %12 = load i64, ptr %1, align 4
  %13 = icmp eq i64 %12, 6
  call void @Assert(i1 %13)
  %14 = load i64, ptr %1, align 4
  store i64 5, ptr %1, align 4
  %15 = load i64, ptr %1, align 4
  %16 = mul i64 %15, 4
  %17 = load i64, ptr %1, align 4
  store i64 %16, ptr %1, align 4
  %18 = load i64, ptr %1, align 4
  %19 = icmp eq i64 %18, 20
  call void @Assert(i1 %19)
  %20 = load i64, ptr %1, align 4
  store i64 7, ptr %1, align 4
  %21 = load i64, ptr %1, align 4
  %22 = sdiv i64 %21, 3
  %23 = load i64, ptr %1, align 4
  store i64 %22, ptr %1, align 4
  %24 = load i64, ptr %1, align 4
  %25 = icmp eq i64 %24, 2
  call void @Assert(i1 %25)
  %26 = load i64, ptr %1, align 4
  store i64 24, ptr %1, align 4
  %27 = load i64, ptr %1, align 4
  %28 = srem i64 %27, 5
  %29 = load i64, ptr %1, align 4
  store i64 %28, ptr %1, align 4
  %30 = load i64, ptr %1, align 4
  %31 = icmp eq i64 %30, 4
  call void @Assert(i1 %31)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %32 = load i64, ptr %0, align 4
  ret i64 %32
}
