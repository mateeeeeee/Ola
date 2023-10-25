; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 42, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 42
  call void @Assert(i1 %3)
  %4 = load i64, ptr %1, align 4
  store i64 0, ptr %1, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp eq i64 %5, 0
  call void @Assert(i1 %6)
  %7 = load i64, ptr %1, align 4
  store i64 21, ptr %1, align 4
  %8 = load i64, ptr %1, align 4
  %9 = icmp eq i64 %8, 21
  call void @Assert(i1 %9)
  %10 = load i64, ptr %1, align 4
  store i64 41, ptr %1, align 4
  %11 = load i64, ptr %1, align 4
  %12 = icmp eq i64 %11, 41
  call void @Assert(i1 %12)
  %13 = load i64, ptr %1, align 4
  store i64 2, ptr %1, align 4
  %14 = load i64, ptr %1, align 4
  %15 = add i64 %14, 5
  %16 = load i64, ptr %1, align 4
  store i64 %15, ptr %1, align 4
  %17 = load i64, ptr %1, align 4
  %18 = icmp eq i64 %17, 7
  call void @Assert(i1 %18)
  %19 = load i64, ptr %1, align 4
  store i64 5, ptr %1, align 4
  %20 = load i64, ptr %1, align 4
  %21 = sub i64 %20, 7
  %22 = load i64, ptr %1, align 4
  store i64 %21, ptr %1, align 4
  %23 = load i64, ptr %1, align 4
  %24 = icmp eq i64 %23, -2
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
