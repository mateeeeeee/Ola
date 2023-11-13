; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@globalFloat = internal constant double 1.000000e+01

declare void @Assert(i1)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca double, align 8
  store double 0x4023CCCCCCCCCCCC, ptr %1, align 8
  %2 = load double, ptr @globalFloat, align 8
  %3 = load double, ptr %1, align 8
  %4 = fcmp ogt double %2, %3
  call void @Assert(i1 %4)
  %5 = load double, ptr @globalFloat, align 8
  %6 = load double, ptr %1, align 8
  %7 = fsub double %5, %6
  %8 = alloca double, align 8
  store double %7, ptr %8, align 8
  %9 = load double, ptr %8, align 8
  %10 = load double, ptr %8, align 8
  %11 = fmul double %9, %10
  %12 = load double, ptr %8, align 8
  %13 = fmul double %11, %12
  %14 = alloca double, align 8
  store double %13, ptr %14, align 8
  %15 = load double, ptr %14, align 8
  %16 = fmul double %15, 9.990000e+02
  %17 = fptosi double %16 to i64
  %18 = alloca i64, align 8
  store i64 %17, ptr %18, align 4
  %19 = load i64, ptr %18, align 4
  %20 = icmp eq i64 %19, 0
  call void @Assert(i1 %20)
  %21 = load double, ptr %14, align 8
  %22 = fmul double %21, 1.000000e+03
  %23 = fptosi double %22 to i64
  %24 = alloca i64, align 8
  store i64 %23, ptr %24, align 4
  %25 = load i64, ptr %24, align 4
  %26 = icmp eq i64 %25, 1
  call void @Assert(i1 %26)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %27 = load i64, ptr %0, align 4
  ret i64 %27
}
