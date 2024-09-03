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
  call void @Assert(i1 true)
  %0 = load i64, ptr @GlobalIntB, align 8
  %1 = call i64 @llvm.smax.i64(i64 %0, i64 5)
  %2 = icmp eq i64 %1, 7
  call void @Assert(i1 %2)
  %3 = load i64, ptr @GlobalIntA, align 8
  %4 = load i64, ptr @GlobalIntB, align 8
  %5 = call i64 @llvm.smax.i64(i64 %3, i64 %4)
  %6 = icmp eq i64 %5, 12
  call void @Assert(i1 %6)
  %7 = load i64, ptr @GlobalIntA, align 8
  %8 = icmp slt i64 %7, 16
  call void @Assert(i1 %8)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestTernaryOperatorFloats() {
entry:
  call void @Assert(i1 true)
  %0 = load double, ptr @GlobalFloatD, align 8
  %1 = fcmp olt double %0, 2.500000e+00
  %2 = select i1 %1, double 2.500000e+00, double %0
  %3 = fcmp oeq double %2, 9.000000e+00
  call void @Assert(i1 %3)
  %4 = load double, ptr @GlobalFloatC, align 8
  %5 = load double, ptr @GlobalFloatD, align 8
  %6 = fcmp ogt double %4, %5
  %7 = select i1 %6, double %4, double %5
  %8 = fcmp oeq double %7, 9.000000e+00
  call void @Assert(i1 %8)
  %9 = load double, ptr @GlobalFloatC, align 8
  %10 = fcmp ogt double %9, 5.000000e+00
  %11 = select i1 %10, double %9, double 5.000000e+00
  %12 = fcmp oeq double %11, 5.000000e+00
  call void @Assert(i1 %12)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestTernaryOperatorBools() {
entry:
  call void @Assert(i1 true)
  %0 = load i1, ptr @GlobalCondition, align 1
  %not. = xor i1 %0, true
  call void @Assert(i1 %not.)
  %1 = load i1, ptr @GlobalCondition, align 1
  %2 = load i64, ptr @GlobalIntA, align 8
  %3 = load i64, ptr @GlobalIntB, align 8
  %4 = select i1 %1, i64 %2, i64 %3
  %5 = icmp eq i64 %4, 7
  call void @Assert(i1 %5)
  %6 = load i1, ptr @GlobalCondition, align 1
  %not.1 = xor i1 %6, true
  call void @Assert(i1 %not.1)
  call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  call void @TestTernaryOperatorIntegers()
  call void @TestTernaryOperatorFloats()
  call void @TestTernaryOperatorBools()
  ret i64 0
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.smax.i64(i64, i64) #0

attributes #0 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
