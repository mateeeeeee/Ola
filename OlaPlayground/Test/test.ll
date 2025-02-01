; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalIntA = internal global i64 12
@GlobalIntB = internal global i64 7
@GlobalFloatC = internal global double 4.500000e+00
@GlobalFloatD = internal global double 9.000000e+00
@GlobalCondition = internal global i1 false

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
  %11 = load i64, ptr %0, align 4
  %12 = load i64, ptr @GlobalIntB, align 4
  %13 = icmp sgt i64 %11, %12
  %14 = load i64, ptr %0, align 4
  %15 = load i64, ptr @GlobalIntB, align 4
  %16 = select i1 %13, i64 %14, i64 %15
  %17 = alloca i64, align 8
  store i64 %16, ptr %17, align 4
  %18 = load i64, ptr %17, align 4
  %19 = icmp eq i64 %18, 7
  call void @Assert(i1 %19)
  %20 = load i64, ptr @GlobalIntA, align 4
  %21 = load i64, ptr @GlobalIntB, align 4
  %22 = icmp sgt i64 %20, %21
  %23 = load i64, ptr @GlobalIntA, align 4
  %24 = load i64, ptr @GlobalIntB, align 4
  %25 = select i1 %22, i64 %23, i64 %24
  %26 = alloca i64, align 8
  store i64 %25, ptr %26, align 4
  %27 = load i64, ptr %26, align 4
  %28 = icmp eq i64 %27, 12
  call void @Assert(i1 %28)
  %29 = load i64, ptr @GlobalIntA, align 4
  %30 = icmp sgt i64 %29, 15
  %31 = load i64, ptr @GlobalIntA, align 4
  %32 = select i1 %30, i64 %31, i64 15
  %33 = alloca i64, align 8
  store i64 %32, ptr %33, align 4
  %34 = load i64, ptr %33, align 4
  %35 = icmp eq i64 %34, 15
  call void @Assert(i1 %35)
  %36 = alloca i64, align 8
  store i64 3, ptr %36, align 4
  %37 = load i64, ptr %36, align 4
  %38 = icmp eq i64 %37, 3
  call void @Assert(i1 %38)
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
  %11 = load double, ptr %0, align 8
  %12 = load double, ptr @GlobalFloatD, align 8
  %13 = fcmp ogt double %11, %12
  %14 = load double, ptr %0, align 8
  %15 = load double, ptr @GlobalFloatD, align 8
  %16 = select i1 %13, double %14, double %15
  %17 = alloca double, align 8
  store double %16, ptr %17, align 8
  %18 = load double, ptr %17, align 8
  %19 = fcmp oeq double %18, 9.000000e+00
  call void @Assert(i1 %19)
  %20 = load double, ptr @GlobalFloatC, align 8
  %21 = load double, ptr @GlobalFloatD, align 8
  %22 = fcmp ogt double %20, %21
  %23 = load double, ptr @GlobalFloatC, align 8
  %24 = load double, ptr @GlobalFloatD, align 8
  %25 = select i1 %22, double %23, double %24
  %26 = alloca double, align 8
  store double %25, ptr %26, align 8
  %27 = load double, ptr %26, align 8
  %28 = fcmp oeq double %27, 9.000000e+00
  call void @Assert(i1 %28)
  %29 = load double, ptr @GlobalFloatC, align 8
  %30 = fcmp ogt double %29, 5.000000e+00
  %31 = load double, ptr @GlobalFloatC, align 8
  %32 = select i1 %30, double %31, double 5.000000e+00
  %33 = alloca double, align 8
  store double %32, ptr %33, align 8
  %34 = load double, ptr %33, align 8
  %35 = fcmp oeq double %34, 5.000000e+00
  call void @Assert(i1 %35)
  %36 = alloca double, align 8
  store double 7.000000e+00, ptr %36, align 8
  %37 = load double, ptr %36, align 8
  %38 = fcmp oeq double %37, 7.000000e+00
  call void @Assert(i1 %38)
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
  %10 = load i1, ptr @GlobalCondition, align 1
  %11 = load i64, ptr %1, align 4
  %12 = load i64, ptr %2, align 4
  %13 = select i1 %10, i64 %11, i64 %12
  %14 = alloca i64, align 8
  store i64 %13, ptr %14, align 4
  %15 = load i64, ptr %14, align 4
  %16 = icmp eq i64 %15, 10
  call void @Assert(i1 %16)
  %17 = load i1, ptr @GlobalCondition, align 1
  %18 = load i64, ptr @GlobalIntA, align 4
  %19 = load i64, ptr @GlobalIntB, align 4
  %20 = select i1 %17, i64 %18, i64 %19
  %21 = alloca i64, align 8
  store i64 %20, ptr %21, align 4
  %22 = load i64, ptr %21, align 4
  %23 = icmp eq i64 %22, 7
  call void @Assert(i1 %23)
  %24 = load i1, ptr @GlobalCondition, align 1
  %25 = select i1 %24, i64 20, i64 30
  %26 = alloca i64, align 8
  store i64 %25, ptr %26, align 4
  %27 = load i64, ptr %26, align 4
  %28 = icmp eq i64 %27, 30
  call void @Assert(i1 %28)
  %29 = alloca i64, align 8
  store i64 1, ptr %29, align 4
  %30 = load i64, ptr %29, align 4
  %31 = icmp eq i64 %30, 1
  call void @Assert(i1 %31)
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
