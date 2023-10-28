; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define internal i64 @square(i64 %x) {
entry:
  %0 = alloca i64, align 8
  %1 = mul i64 %x, %x
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define internal i64 @add(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  %1 = add i64 %a, %b
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define internal i1 @isEven(i64 %x) {
entry:
  %0 = alloca i1, align 1
  %1 = srem i64 %x, 2
  %2 = icmp eq i64 %1, 0
  store i1 %2, ptr %0, align 1
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i1, ptr %0, align 1
  ret i1 %3
}

define internal i64 @fma(i64 %a, i64 %b, i64 %c) {
entry:
  %0 = alloca i64, align 8
  %1 = mul i64 %a, %b
  %2 = add i64 %1, %c
  store i64 %2, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define internal i1 @isInRange(i64 %x, i64 %lowerBound, i64 %upperBound) {
entry:
  %0 = alloca i1, align 1
  %1 = icmp sge i64 %x, %lowerBound
  %2 = icmp sle i64 %x, %upperBound
  %3 = and i1 %1, %2
  %4 = icmp ne i1 %3, false
  store i1 %4, ptr %0, align 1
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i1, ptr %0, align 1
  ret i1 %5
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  %2 = call i64 @square(i64 5)
  store i64 %2, ptr %1, align 4
  %3 = load i64, ptr %1, align 4
  %4 = icmp eq i64 %3, 25
  call void @Assert(i1 %4)
  %5 = alloca i1, align 1
  %6 = call i1 @isEven(i64 8)
  store i1 %6, ptr %5, align 1
  %7 = load i1, ptr %5, align 1
  %8 = icmp eq i1 %7, true
  call void @Assert(i1 %8)
  %9 = alloca i64, align 8
  %10 = call i64 @square(i64 -4)
  store i64 %10, ptr %9, align 4
  %11 = load i64, ptr %9, align 4
  %12 = icmp eq i64 %11, 16
  call void @Assert(i1 %12)
  %13 = alloca i1, align 1
  %14 = call i1 @isEven(i64 7)
  store i1 %14, ptr %13, align 1
  %15 = load i1, ptr %13, align 1
  %16 = icmp eq i1 %15, false
  call void @Assert(i1 %16)
  %17 = alloca i64, align 8
  %18 = call i64 @add(i64 5, i64 12)
  store i64 %18, ptr %17, align 4
  %19 = load i64, ptr %17, align 4
  %20 = icmp eq i64 %19, 17
  call void @Assert(i1 %20)
  %21 = alloca i64, align 8
  %22 = call i64 @fma(i64 2, i64 3, i64 4)
  store i64 %22, ptr %21, align 4
  %23 = load i64, ptr %21, align 4
  %24 = icmp eq i64 %23, 10
  call void @Assert(i1 %24)
  %25 = alloca i1, align 1
  %26 = call i1 @isInRange(i64 5, i64 1, i64 10)
  store i1 %26, ptr %25, align 1
  %27 = load i1, ptr %25, align 1
  %28 = icmp eq i1 %27, true
  call void @Assert(i1 %28)
  %29 = alloca i64, align 8
  %30 = call i64 @fma(i64 6, i64 2, i64 8)
  store i64 %30, ptr %29, align 4
  %31 = load i64, ptr %29, align 4
  %32 = icmp eq i64 %31, 20
  call void @Assert(i1 %32)
  %33 = alloca i1, align 1
  %34 = call i1 @isInRange(i64 5, i64 6, i64 10)
  store i1 %34, ptr %33, align 1
  %35 = load i1, ptr %33, align 1
  %36 = icmp eq i1 %35, false
  call void @Assert(i1 %36)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %37 = load i64, ptr %0, align 4
  ret i64 %37
}
