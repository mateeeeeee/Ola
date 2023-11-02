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
  %8 = alloca i64, align 8
  store i64 0, ptr %8, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %9 = alloca i64, align 8
  %10 = load i64, ptr %8, align 4
  %11 = getelementptr [6 x i64], ptr %1, i64 0, i64 %10
  %12 = load ptr, ptr %11, align 8
  store ptr %12, ptr %9, align 8
  %13 = load i64, ptr %9, align 4
  call void @PrintInteger(i64 %13)
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %14 = load i64, ptr %8, align 4
  %15 = icmp slt i64 %14, 6
  br i1 %15, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %16 = load i64, ptr %8, align 4
  %17 = alloca ptr, align 8
  %18 = load ptr, ptr %8, align 8
  store ptr %18, ptr %17, align 8
  %19 = add i64 %16, 1
  store i64 %19, ptr %8, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %for.end
  %20 = load i64, ptr %0, align 4
  ret i64 %20
}
