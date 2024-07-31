; ModuleID = 'test_logical.ola'
source_filename = "test_logical.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestUnaryLogicalOperators() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i1, align 1
  store i1 false, ptr %1, align 1
  %2 = load i1, ptr %0, align 1
  %3 = icmp eq i1 %2, false
  %4 = alloca i1, align 1
  store i1 %3, ptr %4, align 1
  %5 = load i1, ptr %1, align 1
  %6 = icmp eq i1 %5, false
  %7 = alloca i1, align 1
  store i1 %6, ptr %7, align 1
  %8 = load i1, ptr %4, align 1
  %9 = icmp eq i1 %8, false
  call void @Assert(i1 %9)
  %10 = load i1, ptr %7, align 1
  %11 = icmp eq i1 %10, true
  call void @Assert(i1 %11)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestBinaryLogicalOperators() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i1, align 1
  store i1 false, ptr %1, align 1
  %2 = load i1, ptr %0, align 1
  %3 = load i1, ptr %0, align 1
  %4 = and i1 %2, %3
  %5 = icmp ne i1 %4, false
  %6 = alloca i1, align 1
  store i1 %5, ptr %6, align 1
  %7 = load i1, ptr %0, align 1
  %8 = load i1, ptr %1, align 1
  %9 = and i1 %7, %8
  %10 = icmp ne i1 %9, false
  %11 = alloca i1, align 1
  store i1 %10, ptr %11, align 1
  %12 = load i1, ptr %1, align 1
  %13 = load i1, ptr %0, align 1
  %14 = and i1 %12, %13
  %15 = icmp ne i1 %14, false
  %16 = alloca i1, align 1
  store i1 %15, ptr %16, align 1
  %17 = load i1, ptr %1, align 1
  %18 = load i1, ptr %1, align 1
  %19 = and i1 %17, %18
  %20 = icmp ne i1 %19, false
  %21 = alloca i1, align 1
  store i1 %20, ptr %21, align 1
  %22 = load i1, ptr %6, align 1
  %23 = icmp eq i1 %22, true
  call void @Assert(i1 %23)
  %24 = load i1, ptr %11, align 1
  %25 = icmp eq i1 %24, false
  call void @Assert(i1 %25)
  %26 = load i1, ptr %16, align 1
  %27 = icmp eq i1 %26, false
  call void @Assert(i1 %27)
  %28 = load i1, ptr %21, align 1
  %29 = icmp eq i1 %28, false
  call void @Assert(i1 %29)
  %30 = load i1, ptr %0, align 1
  %31 = load i1, ptr %0, align 1
  %32 = or i1 %30, %31
  %33 = icmp ne i1 %32, false
  %34 = alloca i1, align 1
  store i1 %33, ptr %34, align 1
  %35 = load i1, ptr %0, align 1
  %36 = load i1, ptr %1, align 1
  %37 = or i1 %35, %36
  %38 = icmp ne i1 %37, false
  %39 = alloca i1, align 1
  store i1 %38, ptr %39, align 1
  %40 = load i1, ptr %1, align 1
  %41 = load i1, ptr %0, align 1
  %42 = or i1 %40, %41
  %43 = icmp ne i1 %42, false
  %44 = alloca i1, align 1
  store i1 %43, ptr %44, align 1
  %45 = load i1, ptr %1, align 1
  %46 = load i1, ptr %1, align 1
  %47 = or i1 %45, %46
  %48 = icmp ne i1 %47, false
  %49 = alloca i1, align 1
  store i1 %48, ptr %49, align 1
  %50 = load i1, ptr %34, align 1
  %51 = icmp eq i1 %50, true
  call void @Assert(i1 %51)
  %52 = load i1, ptr %39, align 1
  %53 = icmp eq i1 %52, true
  call void @Assert(i1 %53)
  %54 = load i1, ptr %44, align 1
  %55 = icmp eq i1 %54, true
  call void @Assert(i1 %55)
  %56 = load i1, ptr %49, align 1
  %57 = icmp eq i1 %56, false
  call void @Assert(i1 %57)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestBinaryLogicalOperatorsImplicitCasts() {
entry:
  %0 = alloca i64, align 8
  store i64 42, ptr %0, align 4
  %1 = alloca double, align 8
  store double 3.140000e+00, ptr %1, align 8
  %2 = load i64, ptr %0, align 4
  %3 = icmp ne i64 %2, 0
  %4 = load double, ptr %1, align 8
  %5 = fptoui double %4 to i1
  %6 = and i1 %3, %5
  %7 = icmp ne i1 %6, false
  %8 = alloca i1, align 1
  store i1 %7, ptr %8, align 1
  %9 = load i1, ptr %8, align 1
  %10 = icmp eq i1 %9, true
  call void @Assert(i1 %10)
  %11 = load i64, ptr %0, align 4
  %12 = icmp ne i64 %11, 0
  %13 = load double, ptr %1, align 8
  %14 = fptoui double %13 to i1
  %15 = or i1 %12, %14
  %16 = icmp ne i1 %15, false
  %17 = alloca i1, align 1
  store i1 %16, ptr %17, align 1
  %18 = load i1, ptr %17, align 1
  %19 = icmp eq i1 %18, true
  call void @Assert(i1 %19)
  %20 = load i64, ptr %0, align 4
  %21 = icmp ne i64 %20, 0
  %22 = load i64, ptr %0, align 4
  %23 = icmp ne i64 %22, 0
  %24 = and i1 %21, %23
  %25 = icmp ne i1 %24, false
  %26 = alloca i1, align 1
  store i1 %25, ptr %26, align 1
  %27 = load i1, ptr %26, align 1
  %28 = icmp eq i1 %27, true
  call void @Assert(i1 %28)
  %29 = load double, ptr %1, align 8
  %30 = fptoui double %29 to i1
  %31 = load double, ptr %1, align 8
  %32 = fptoui double %31 to i1
  %33 = or i1 %30, %32
  %34 = icmp ne i1 %33, false
  %35 = alloca i1, align 1
  store i1 %34, ptr %35, align 1
  %36 = load i1, ptr %35, align 1
  %37 = icmp eq i1 %36, true
  call void @Assert(i1 %37)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestLogicalOperatorsImplicitCasts() {
entry:
  %0 = alloca i64, align 8
  store i64 42, ptr %0, align 4
  %1 = alloca double, align 8
  store double 3.140000e+00, ptr %1, align 8
  %2 = load i64, ptr %0, align 4
  %3 = icmp ne i64 %2, 0
  %4 = icmp eq i1 %3, false
  %5 = alloca i1, align 1
  store i1 %4, ptr %5, align 1
  %6 = load i1, ptr %5, align 1
  %7 = icmp eq i1 %6, false
  call void @Assert(i1 %7)
  %8 = load double, ptr %1, align 8
  %9 = fptoui double %8 to i1
  %10 = load i64, ptr %0, align 4
  %11 = icmp ne i64 %10, 0
  %12 = and i1 %9, %11
  %13 = icmp ne i1 %12, false
  %14 = alloca i1, align 1
  store i1 %13, ptr %14, align 1
  %15 = load i1, ptr %14, align 1
  %16 = icmp eq i1 %15, true
  call void @Assert(i1 %16)
  %17 = load i64, ptr %0, align 4
  %18 = icmp ne i64 %17, 0
  %19 = load double, ptr %1, align 8
  %20 = fptoui double %19 to i1
  %21 = or i1 %18, %20
  %22 = icmp ne i1 %21, false
  %23 = alloca i1, align 1
  store i1 %22, ptr %23, align 1
  %24 = load i1, ptr %23, align 1
  %25 = icmp eq i1 %24, true
  call void @Assert(i1 %25)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestUnaryLogicalOperators()
  call void @TestBinaryLogicalOperators()
  call void @TestBinaryLogicalOperatorsImplicitCasts()
  call void @TestLogicalOperatorsImplicitCasts()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
