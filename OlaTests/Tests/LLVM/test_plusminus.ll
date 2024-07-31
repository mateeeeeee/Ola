; ModuleID = 'test_plusminus.ola'
source_filename = "test_plusminus.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = sub i64 0, %2
  %4 = alloca i64, align 8
  store i64 %3, ptr %4, align 4
  %5 = load i64, ptr %4, align 4
  %6 = icmp eq i64 %5, -5
  call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 10, ptr %7, align 4
  %8 = load i64, ptr %7, align 4
  %9 = alloca i64, align 8
  %10 = load i64, ptr %7, align 4
  store i64 %10, ptr %9, align 4
  %11 = load i64, ptr %9, align 4
  %12 = icmp eq i64 %11, 10
  call void @Assert(i1 %12)
  %13 = alloca double, align 8
  store double 1.000000e+01, ptr %13, align 8
  %14 = load double, ptr %13, align 8
  %15 = alloca double, align 8
  %16 = load double, ptr %13, align 8
  store double %16, ptr %15, align 8
  %17 = load double, ptr %15, align 8
  %18 = fcmp oeq double %17, 1.000000e+01
  call void @Assert(i1 %18)
  %19 = load double, ptr %13, align 8
  %20 = fneg double %19
  %21 = alloca double, align 8
  store double %20, ptr %21, align 8
  %22 = load double, ptr %21, align 8
  %23 = fcmp oeq double %22, -1.000000e+01
  call void @Assert(i1 %23)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %24 = load i64, ptr %0, align 4
  ret i64 %24
}
