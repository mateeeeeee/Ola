; ModuleID = 'test_relational.ola'
source_filename = "test_relational.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestLessThanOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp slt i64 %4, %5
  call void @Assert(i1 %6)
  %7 = load double, ptr %2, align 8
  %8 = load double, ptr %3, align 8
  %9 = fcmp olt double %7, %8
  call void @Assert(i1 %9)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestLessThanOrEqualOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp sle i64 %4, %5
  call void @Assert(i1 %6)
  %7 = load double, ptr %2, align 8
  %8 = load double, ptr %3, align 8
  %9 = fcmp ole double %7, %8
  call void @Assert(i1 %9)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestGreaterThanOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp sgt i64 %4, %5
  %7 = icmp eq i1 %6, false
  call void @Assert(i1 %7)
  %8 = load double, ptr %2, align 8
  %9 = load double, ptr %3, align 8
  %10 = fcmp ogt double %8, %9
  %11 = icmp eq i1 %10, false
  call void @Assert(i1 %11)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestGreaterThanOrEqualOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp sge i64 %4, %5
  %7 = icmp eq i1 %6, false
  call void @Assert(i1 %7)
  %8 = load double, ptr %2, align 8
  %9 = load double, ptr %3, align 8
  %10 = fcmp oge double %8, %9
  %11 = icmp eq i1 %10, false
  call void @Assert(i1 %11)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestEqualOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp eq i64 %4, %5
  %7 = icmp eq i1 %6, false
  call void @Assert(i1 %7)
  %8 = load double, ptr %2, align 8
  %9 = load double, ptr %3, align 8
  %10 = fcmp oeq double %8, %9
  %11 = icmp eq i1 %10, false
  call void @Assert(i1 %11)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestNotEqualOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca double, align 8
  store double 2.500000e+00, ptr %2, align 8
  %3 = alloca double, align 8
  store double 5.000000e+00, ptr %3, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp ne i64 %4, %5
  %7 = icmp eq i1 %6, true
  call void @Assert(i1 %7)
  %8 = load double, ptr %2, align 8
  %9 = load double, ptr %3, align 8
  %10 = fcmp one double %8, %9
  %11 = icmp eq i1 %10, true
  call void @Assert(i1 %11)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestLessThanOperators()
  call void @TestLessThanOrEqualOperators()
  call void @TestGreaterThanOperators()
  call void @TestGreaterThanOrEqualOperators()
  call void @TestEqualOperators()
  call void @TestNotEqualOperators()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
