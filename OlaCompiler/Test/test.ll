; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalInt1 = internal global i64 5
@GlobalInt2 = internal global i64 10
@GlobalFloat1 = internal global double 3.500000e+00
@GlobalFloat2 = internal global double 8.500000e+00

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIntIncrementDecrement() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  %0 = load i64, ptr @GlobalInt1, align 8
  %1 = add i64 %0, 1
  store i64 %1, ptr @GlobalInt1, align 8
  %2 = icmp eq i64 %1, 6
  call void @Assert(i1 %2)
  %3 = load i64, ptr @GlobalInt1, align 8
  %4 = icmp eq i64 %3, 6
  call void @Assert(i1 %4)
  %5 = load i64, ptr @GlobalInt2, align 8
  %6 = add i64 %5, -1
  store i64 %6, ptr @GlobalInt2, align 8
  %7 = icmp eq i64 %6, 9
  call void @Assert(i1 %7)
  %8 = load i64, ptr @GlobalInt2, align 8
  %9 = icmp eq i64 %8, 9
  call void @Assert(i1 %9)
  %10 = load i64, ptr @GlobalInt1, align 8
  %11 = add i64 %10, 1
  store i64 %11, ptr @GlobalInt1, align 8
  %12 = icmp eq i64 %10, 6
  call void @Assert(i1 %12)
  %13 = load i64, ptr @GlobalInt1, align 8
  %14 = icmp eq i64 %13, 7
  call void @Assert(i1 %14)
  %15 = load i64, ptr @GlobalInt2, align 8
  %16 = add i64 %15, -1
  store i64 %16, ptr @GlobalInt2, align 8
  %17 = icmp eq i64 %15, 9
  call void @Assert(i1 %17)
  %18 = load i64, ptr @GlobalInt2, align 8
  %19 = icmp eq i64 %18, 8
  call void @Assert(i1 %19)
  ret void
}

define internal void @TestFloatIncrementDecrement() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  %0 = load double, ptr @GlobalFloat1, align 8
  %1 = alloca ptr, align 8
  store double %0, ptr %1, align 8
  %2 = fadd double %0, 1.000000e+00
  store double %2, ptr @GlobalFloat1, align 8
  %3 = alloca double, align 8
  %4 = load ptr, ptr %1, align 8
  store ptr %4, ptr %3, align 8
  %5 = load double, ptr %3, align 8
  %6 = fcmp oeq double %5, 3.500000e+00
  call void @Assert(i1 %6)
  %7 = load double, ptr @GlobalFloat1, align 8
  %8 = fcmp oeq double %7, 4.500000e+00
  call void @Assert(i1 %8)
  %9 = load double, ptr @GlobalFloat2, align 8
  %10 = alloca ptr, align 8
  store double %9, ptr %10, align 8
  %11 = fadd double %9, -1.000000e+00
  store double %11, ptr @GlobalFloat2, align 8
  %12 = alloca double, align 8
  %13 = load ptr, ptr %10, align 8
  store ptr %13, ptr %12, align 8
  %14 = load double, ptr %12, align 8
  %15 = fcmp oeq double %14, 8.500000e+00
  call void @Assert(i1 %15)
  %16 = load double, ptr @GlobalFloat2, align 8
  %17 = fcmp oeq double %16, 7.500000e+00
  call void @Assert(i1 %17)
  ret void
}

define i64 @main() {
entry:
  call void @TestIntIncrementDecrement()
  call void @TestFloatIncrementDecrement()
  ret i64 0
}
