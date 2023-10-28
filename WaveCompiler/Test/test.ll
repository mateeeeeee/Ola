; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 0
  call void @Assert(i1 %3)
  %4 = load i64, ptr %1, align 4
  store i64 1, ptr %1, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp eq i64 %5, 1
  call void @Assert(i1 %6)
  %7 = load i64, ptr %1, align 4
  store i64 2, ptr %1, align 4
  %8 = load i64, ptr %1, align 4
  %9 = icmp eq i64 %8, 2
  call void @Assert(i1 %9)
  %10 = alloca i64, align 8
  store i64 0, ptr %10, align 4
  %11 = load i64, ptr %10, align 4
  %12 = icmp eq i64 %11, 0
  call void @Assert(i1 %12)
  %13 = load i64, ptr %10, align 4
  store i64 5, ptr %10, align 4
  %14 = load i64, ptr %10, align 4
  %15 = icmp eq i64 %14, 5
  call void @Assert(i1 %15)
  %16 = load i64, ptr %10, align 4
  store i64 3, ptr %10, align 4
  %17 = load i64, ptr %10, align 4
  %18 = icmp eq i64 %17, 3
  call void @Assert(i1 %18)
  %19 = load i64, ptr %10, align 4
  store i64 4, ptr %10, align 4
  %20 = load i64, ptr %10, align 4
  %21 = icmp eq i64 %20, 4
  call void @Assert(i1 %21)
  call void @Assert(i1 true)
  %22 = alloca i64, align 8
  store i64 0, ptr %22, align 4
  %23 = load i64, ptr %22, align 4
  %24 = icmp eq i64 %23, 0
  call void @Assert(i1 %24)
  %25 = load i64, ptr %22, align 4
  store i64 1, ptr %22, align 4
  %26 = load i64, ptr %22, align 4
  %27 = icmp eq i64 %26, 1
  call void @Assert(i1 %27)
  %28 = load i64, ptr %22, align 4
  store i64 2, ptr %22, align 4
  %29 = load i64, ptr %22, align 4
  %30 = icmp eq i64 %29, 2
  call void @Assert(i1 %30)
  %31 = alloca i64, align 8
  store i64 0, ptr %31, align 4
  %32 = load i64, ptr %31, align 4
  %33 = icmp eq i64 %32, 0
  call void @Assert(i1 %33)
  %34 = load i64, ptr %31, align 4
  store i64 1, ptr %31, align 4
  %35 = load i64, ptr %31, align 4
  %36 = icmp eq i64 %35, 1
  call void @Assert(i1 %36)
  %37 = load i64, ptr %31, align 4
  store i64 3, ptr %31, align 4
  %38 = load i64, ptr %31, align 4
  %39 = icmp eq i64 %38, 3
  call void @Assert(i1 %39)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %40 = load i64, ptr %0, align 4
  ret i64 %40
}
