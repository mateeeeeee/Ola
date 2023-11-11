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

define internal void @func(i64 %a) {
entry:
  %0 = icmp sgt i64 %a, 0
  br i1 %0, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @PrintInteger(i64 %a)
  br label %if.end

if.else:                                          ; preds = %entry
  %1 = sub i64 0, %a
  call void @PrintInteger(i64 %1)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %if.end
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @func(i64 5)
  %1 = alloca double, align 8
  store double 1.000000e+00, ptr %1, align 8
  %2 = load double, ptr %1, align 8
  %3 = fadd double %2, 2.000000e+00
  %4 = alloca double, align 8
  store double %3, ptr %4, align 8
  %5 = load double, ptr %4, align 8
  %6 = fcmp ogt double %5, 2.500000e+00
  br i1 %6, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %7 = alloca [3 x i8], align 1
  %8 = getelementptr [3 x i8], ptr %7, i64 0, i64 0
  store i8 100, ptr %8, align 1
  %9 = getelementptr [3 x i8], ptr %7, i64 0, i64 1
  store i8 97, ptr %9, align 1
  %10 = getelementptr [3 x i8], ptr %7, i64 0, i64 2
  store i8 0, ptr %10, align 1
  %11 = getelementptr inbounds [3 x i8], ptr %7, i64 0, i64 0
  call void @PrintString(ptr %11)
  br label %if.end

if.else:                                          ; preds = %entry
  %12 = alloca [3 x i8], align 1
  %13 = getelementptr [3 x i8], ptr %12, i64 0, i64 0
  store i8 110, ptr %13, align 1
  %14 = getelementptr [3 x i8], ptr %12, i64 0, i64 1
  store i8 101, ptr %14, align 1
  %15 = getelementptr [3 x i8], ptr %12, i64 0, i64 2
  store i8 0, ptr %15, align 1
  %16 = getelementptr inbounds [3 x i8], ptr %12, i64 0, i64 0
  call void @PrintString(ptr %16)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %17 = load double, ptr %4, align 8
  call void @PrintFloat(double %17)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %if.end
  %18 = load i64, ptr %0, align 4
  ret i64 %18
}
