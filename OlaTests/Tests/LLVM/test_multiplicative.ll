; ModuleID = 'test_multiplicative.ola'
source_filename = "test_multiplicative.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestMultiplication() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 3, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 1.200000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = mul i64 %4, %5
  %7 = alloca i64, align 8
  store i64 %6, ptr %7, align 4
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 15
  call void @Assert(i1 %9)
  %10 = load double, ptr %2, align 8
  %11 = load double, ptr %3, align 8
  %12 = fmul double %10, %11
  %13 = alloca double, align 8
  store double %12, ptr %13, align 8
  %14 = load double, ptr %13, align 8
  %15 = fcmp oeq double %14, 3.000000e+00
  call void @Assert(i1 %15)
  %16 = load i64, ptr %0, align 4
  %17 = mul i64 %16, 2
  %18 = load i64, ptr %0, align 4
  store i64 %17, ptr %0, align 4
  %19 = load i64, ptr %0, align 4
  %20 = icmp eq i64 %19, 10
  call void @Assert(i1 %20)
  %21 = load double, ptr %2, align 8
  %22 = fmul double %21, 1.500000e+00
  %23 = load double, ptr %2, align 8
  store double %22, ptr %2, align 8
  %24 = load double, ptr %2, align 8
  %25 = fcmp oeq double %24, 3.750000e+00
  call void @Assert(i1 %25)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestDivision() {
entry:
  %0 = alloca i64, align 8
  store i64 15, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 3, ptr %1, align 4
  %2 = alloca double, align 8
  store double 5.000000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 2.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = sdiv i64 %4, %5
  %7 = alloca i64, align 8
  store i64 %6, ptr %7, align 4
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 5
  call void @Assert(i1 %9)
  %10 = load double, ptr %2, align 8
  %11 = load double, ptr %3, align 8
  %12 = fdiv double %10, %11
  %13 = alloca double, align 8
  store double %12, ptr %13, align 8
  %14 = load double, ptr %13, align 8
  %15 = fcmp oeq double %14, 2.500000e+00
  call void @Assert(i1 %15)
  %16 = load i64, ptr %0, align 4
  %17 = sdiv i64 %16, 2
  %18 = load i64, ptr %0, align 4
  store i64 %17, ptr %0, align 4
  %19 = load i64, ptr %0, align 4
  %20 = icmp eq i64 %19, 7
  call void @Assert(i1 %20)
  %21 = load double, ptr %2, align 8
  %22 = fdiv double %21, 2.000000e+00
  %23 = load double, ptr %2, align 8
  store double %22, ptr %2, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestModulo() {
entry:
  %0 = alloca i64, align 8
  store i64 17, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 4, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = srem i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 1
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = srem i64 %8, 3
  %10 = load i64, ptr %0, align 4
  store i64 %9, ptr %0, align 4
  %11 = load i64, ptr %0, align 4
  %12 = icmp eq i64 %11, 2
  call void @Assert(i1 %12)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestMultiplication()
  call void @TestDivision()
  call void @TestModulo()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
