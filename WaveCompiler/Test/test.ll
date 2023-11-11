; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@arr2d = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]
@arr1d = internal global [4 x i64] [i64 1, i64 2, i64 3, i64 4]

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
  store double add (double 1.000000e+00, double 2.000000e+00), ptr %1, align 8
  %2 = load double, ptr %1, align 8
  %3 = add double %2, 3.000000e+00
  %4 = alloca double, align 8
  store double %3, ptr %4, align 8
  %5 = load double, ptr %1, align 8
  call void @PrintFloat(double %5)
  br label %exit

exit:                                             ; preds = %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
