; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [6 x i64], align 8
  %2 = getelementptr [6 x i64], ptr %1, i64 0, i64 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr [6 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [6 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = getelementptr [6 x i64], ptr %1, i64 0, i64 3
  store i64 0, ptr %5, align 4
  %6 = getelementptr [6 x i64], ptr %1, i64 0, i64 4
  store i64 0, ptr %6, align 4
  %7 = getelementptr [6 x i64], ptr %1, i64 0, i64 5
  store i64 0, ptr %7, align 4
  %8 = getelementptr [6 x i64], ptr %1, i64 0, i64 0
  %9 = load i64, ptr %8, align 4
  store i64 10, ptr %8, align 4
  %10 = alloca i64, align 8
  store i64 0, ptr %10, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %11 = alloca i64, align 8
  %12 = load i64, ptr %10, align 4
  %13 = getelementptr [6 x i64], ptr %1, i64 0, i64 %12
  %14 = load ptr, ptr %13, align 8
  store ptr %14, ptr %11, align 8
  %15 = load i64, ptr %11, align 4
  call void @PrintInteger(i64 %15)
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %16 = load i64, ptr %10, align 4
  %17 = icmp slt i64 %16, 6
  br i1 %17, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %18 = load i64, ptr %10, align 4
  %19 = alloca ptr, align 8
  %20 = load ptr, ptr %10, align 8
  store ptr %20, ptr %19, align 8
  %21 = add i64 %18, 1
  store i64 %21, ptr %10, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %22 = getelementptr [6 x i64], ptr %1, i64 0, i64 0
  %23 = load ptr, ptr %22, align 8
  store ptr %23, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %for.end
  %24 = load i64, ptr %0, align 4
  ret i64 %24
}
