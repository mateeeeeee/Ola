; ModuleID = 'test_ternary.ola'
source_filename = "test_ternary.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestTernaryOperatorIntegers() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = icmp sgt i64 %2, %3
  %5 = load i64, ptr %0, align 4
  %6 = load i64, ptr %1, align 4
  %7 = select i1 %4, i64 %5, i64 %6
  %8 = alloca i64, align 8
  store i64 %7, ptr %8, align 4
  %9 = load i64, ptr %8, align 4
  %10 = icmp eq i64 %9, 10
  call void @Assert(i1 %10)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestTernaryOperatorFloats() {
entry:
  %0 = alloca double, align 8
  store double 2.500000e+00, ptr %0, align 8
  %1 = alloca double, align 8
  store double 3.000000e+00, ptr %1, align 8
  %2 = load double, ptr %0, align 8
  %3 = load double, ptr %1, align 8
  %4 = fcmp ogt double %2, %3
  %5 = load double, ptr %0, align 8
  %6 = load double, ptr %1, align 8
  %7 = select i1 %4, double %5, double %6
  %8 = alloca double, align 8
  store double %7, ptr %8, align 8
  %9 = load double, ptr %8, align 8
  %10 = fcmp oeq double %9, 3.000000e+00
  call void @Assert(i1 %10)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestTernaryOperatorBools() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 10, ptr %2, align 4
  %3 = load i1, ptr %0, align 1
  %4 = load i64, ptr %1, align 4
  %5 = load i64, ptr %2, align 4
  %6 = select i1 %3, i64 %4, i64 %5
  %7 = alloca i64, align 8
  store i64 %6, ptr %7, align 4
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 5
  call void @Assert(i1 %9)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestTernaryOperatorIntegers()
  call void @TestTernaryOperatorFloats()
  call void @TestTernaryOperatorBools()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
