; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@E = external global double
@LOG2E = external global double
@LOG10E = external global double
@LN2 = external global double
@LN10 = external global double
@PI = external global double
@PI_2 = external global double
@PI_4 = external global double
@SQRT2 = external global double
@SQRT1_2 = external global double

declare double @Fabs(double)

declare double @Fmod(double, double)

declare double @Ffma(double, double, double)

declare double @Fmax(double, double)

declare double @Fmin(double, double)

declare double @Ceil(double)

declare double @Floor(double)

declare double @Round(double)

declare double @Trunc(double)

declare double @Sqrt(double)

declare double @Cbrt(double)

declare double @Pow(double, double)

declare double @Log(double)

declare double @Log2(double)

declare double @Log10(double)

declare double @Exp(double)

declare double @Sin(double)

declare double @Cos(double)

declare double @Tan(double)

declare double @Asin(double)

declare double @Acos(double)

declare double @Atan(double)

declare double @Atan2(double, double)

declare i64 @Abs(i64)

declare i64 @Min(i64, i64)

declare i64 @Max(i64, i64)

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = load double, ptr @PI, align 8
  call void @PrintFloat(double %1)
  br label %exit

exit:                                             ; preds = %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}
