; ModuleID = 'test_increment.ola'
source_filename = "test_increment.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestPreIncrementDecrement() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 8, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 4
  %4 = alloca i64, align 8
  store i64 %3, ptr %4, align 4
  %5 = load i64, ptr %4, align 4
  %6 = icmp eq i64 %5, 6
  call void @Assert(i1 %6)
  %7 = load i64, ptr %0, align 4
  %8 = icmp eq i64 %7, 6
  call void @Assert(i1 %8)
  %9 = load i64, ptr %1, align 4
  %10 = sub i64 %9, 1
  store i64 %10, ptr %1, align 4
  %11 = alloca i64, align 8
  store i64 %10, ptr %11, align 4
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 7
  call void @Assert(i1 %13)
  %14 = load i64, ptr %1, align 4
  %15 = icmp eq i64 %14, 7
  call void @Assert(i1 %15)
  %16 = alloca double, align 8
  store double 3.500000e+00, ptr %16, align 8
  %17 = alloca double, align 8
  store double 8.500000e+00, ptr %17, align 8
  %18 = load double, ptr %16, align 8
  %19 = fadd double %18, 1.000000e+00
  store double %19, ptr %16, align 8
  %20 = alloca double, align 8
  store double %19, ptr %20, align 8
  %21 = load double, ptr %20, align 8
  %22 = fcmp oeq double %21, 4.500000e+00
  call void @Assert(i1 %22)
  %23 = load double, ptr %16, align 8
  %24 = fcmp oeq double %23, 4.500000e+00
  call void @Assert(i1 %24)
  %25 = load double, ptr %17, align 8
  %26 = fsub double %25, 1.000000e+00
  store double %26, ptr %17, align 8
  %27 = alloca double, align 8
  store double %26, ptr %27, align 8
  %28 = load double, ptr %27, align 8
  %29 = fcmp oeq double %28, 7.500000e+00
  call void @Assert(i1 %29)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestPostIncrementDecrement() {
entry:
  %0 = alloca i64, align 8
  store i64 10, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 15, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = alloca ptr, align 8
  %4 = load i64, ptr %0, align 4
  store i64 %4, ptr %3, align 4
  %5 = add i64 %2, 1
  store i64 %5, ptr %0, align 4
  %6 = alloca i64, align 8
  %7 = load ptr, ptr %3, align 8
  store ptr %7, ptr %6, align 8
  %8 = load i64, ptr %6, align 4
  %9 = icmp eq i64 %8, 10
  call void @Assert(i1 %9)
  %10 = load i64, ptr %0, align 4
  %11 = icmp eq i64 %10, 11
  call void @Assert(i1 %11)
  %12 = load i64, ptr %1, align 4
  %13 = alloca ptr, align 8
  %14 = load i64, ptr %1, align 4
  store i64 %14, ptr %13, align 4
  %15 = sub i64 %12, 1
  store i64 %15, ptr %1, align 4
  %16 = alloca i64, align 8
  %17 = load ptr, ptr %13, align 8
  store ptr %17, ptr %16, align 8
  %18 = load i64, ptr %16, align 4
  %19 = icmp eq i64 %18, 15
  call void @Assert(i1 %19)
  %20 = load i64, ptr %1, align 4
  %21 = icmp eq i64 %20, 14
  call void @Assert(i1 %21)
  %22 = alloca double, align 8
  store double 6.500000e+00, ptr %22, align 8
  %23 = alloca double, align 8
  store double 1.250000e+01, ptr %23, align 8
  %24 = load double, ptr %22, align 8
  %25 = alloca ptr, align 8
  %26 = load double, ptr %22, align 8
  store double %26, ptr %25, align 8
  %27 = fadd double %24, 1.000000e+00
  store double %27, ptr %22, align 8
  %28 = alloca double, align 8
  %29 = load ptr, ptr %25, align 8
  store ptr %29, ptr %28, align 8
  %30 = load double, ptr %28, align 8
  %31 = fcmp oeq double %30, 6.500000e+00
  call void @Assert(i1 %31)
  %32 = load double, ptr %22, align 8
  %33 = fcmp oeq double %32, 7.500000e+00
  call void @Assert(i1 %33)
  %34 = load double, ptr %23, align 8
  %35 = alloca ptr, align 8
  %36 = load double, ptr %23, align 8
  store double %36, ptr %35, align 8
  %37 = fsub double %34, 1.000000e+00
  store double %37, ptr %23, align 8
  %38 = alloca double, align 8
  %39 = load ptr, ptr %35, align 8
  store ptr %39, ptr %38, align 8
  %40 = load double, ptr %38, align 8
  %41 = fcmp oeq double %40, 1.250000e+01
  call void @Assert(i1 %41)
  %42 = load double, ptr %23, align 8
  %43 = fcmp oeq double %42, 1.150000e+01
  call void @Assert(i1 %43)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestPreIncrementDecrement()
  call void @TestPostIncrementDecrement()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
