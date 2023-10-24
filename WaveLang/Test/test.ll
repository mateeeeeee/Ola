; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@PI = external global i64

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @Assert(i1)

declare double @Abs(double)

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

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  %2 = call i64 @ReadInteger()
  store i64 %2, ptr %1, align 4
  %3 = load i64, ptr %1, align 4
  call void @PrintInteger(i64 %3)
  %4 = load ptr, ptr @PI, align 8
  store ptr %4, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
