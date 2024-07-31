; ModuleID = 'test_additive.ola'
source_filename = "test_additive.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIntAddition() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 15
  call void @Assert(i1 %7)
  %8 = alloca i64, align 8
  store i64 7, ptr %8, align 4
  %9 = load i64, ptr %0, align 4
  %10 = load i64, ptr %8, align 4
  %11 = add i64 %9, %10
  %12 = load i64, ptr %0, align 4
  store i64 %11, ptr %0, align 4
  %13 = load i64, ptr %0, align 4
  %14 = icmp eq i64 %13, 12
  call void @Assert(i1 %14)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestIntSubtraction() {
entry:
  %0 = alloca i64, align 8
  store i64 15, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 7, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = sub i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 8
  call void @Assert(i1 %7)
  %8 = alloca i64, align 8
  store i64 3, ptr %8, align 4
  %9 = load i64, ptr %0, align 4
  %10 = load i64, ptr %8, align 4
  %11 = sub i64 %9, %10
  %12 = load i64, ptr %0, align 4
  store i64 %11, ptr %0, align 4
  %13 = load i64, ptr %0, align 4
  %14 = icmp eq i64 %13, 12
  call void @Assert(i1 %14)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestFloatAddition() {
entry:
  %0 = alloca double, align 8
  store double 3.500000e+00, ptr %0, align 8
  %1 = alloca double, align 8
  store double 2.500000e+00, ptr %1, align 8
  %2 = load double, ptr %0, align 8
  %3 = load double, ptr %1, align 8
  %4 = fadd double %2, %3
  %5 = alloca double, align 8
  store double %4, ptr %5, align 8
  %6 = load double, ptr %5, align 8
  %7 = fcmp oeq double %6, 6.000000e+00
  call void @Assert(i1 %7)
  %8 = alloca double, align 8
  store double 1.200000e+00, ptr %8, align 8
  %9 = load double, ptr %0, align 8
  %10 = load double, ptr %8, align 8
  %11 = fadd double %9, %10
  %12 = load double, ptr %0, align 8
  store double %11, ptr %0, align 8
  %13 = load double, ptr %0, align 8
  %14 = fcmp oeq double %13, 4.700000e+00
  call void @Assert(i1 %14)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestFloatSubtraction() {
entry:
  %0 = alloca double, align 8
  store double 5.000000e+00, ptr %0, align 8
  %1 = alloca double, align 8
  store double 2.500000e+00, ptr %1, align 8
  %2 = load double, ptr %0, align 8
  %3 = load double, ptr %1, align 8
  %4 = fsub double %2, %3
  %5 = alloca double, align 8
  store double %4, ptr %5, align 8
  %6 = load double, ptr %5, align 8
  %7 = fcmp oeq double %6, 2.500000e+00
  call void @Assert(i1 %7)
  %8 = alloca double, align 8
  store double 1.200000e+00, ptr %8, align 8
  %9 = load double, ptr %0, align 8
  %10 = load double, ptr %8, align 8
  %11 = fsub double %9, %10
  %12 = load double, ptr %0, align 8
  store double %11, ptr %0, align 8
  %13 = load double, ptr %0, align 8
  %14 = fcmp oeq double %13, 3.800000e+00
  call void @Assert(i1 %14)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestIntAddition()
  call void @TestIntSubtraction()
  call void @TestFloatAddition()
  call void @TestFloatSubtraction()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
