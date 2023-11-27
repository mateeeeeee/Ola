; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@Global2dArray = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  %3 = alloca ptr, align 8
  store ptr @Global2dArray, ptr %3, align 8
  %4 = load [2 x [2 x i64]], ptr @Global2dArray, align 4
  %5 = load ptr, ptr %3, align 8
  %6 = load ptr, ptr %3, align 8
  store ptr %6, ptr @Global2dArray, align 8
  %7 = alloca i64, align 8
  store i64 0, ptr %7, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %8 = alloca i64, align 8
  store i64 0, ptr %8, align 4
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %9 = load i64, ptr %7, align 4
  %10 = icmp slt i64 %9, 2
  br i1 %10, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %11 = load i64, ptr %7, align 4
  %12 = add i64 %11, 1
  store i64 %12, ptr %7, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %13 = load i64, ptr %1, align 4
  %14 = icmp eq i64 %13, 10
  call void @Assert(i1 %14)
  %15 = load i64, ptr %1, align 4
  call void @PrintInt(i64 %15)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

for.body1:                                        ; preds = %for.cond2
  %16 = load i64, ptr %7, align 4
  %17 = load ptr, ptr %3, align 8
  %18 = getelementptr inbounds ptr, ptr %17, i64 %16
  %19 = load i64, ptr %8, align 4
  %20 = getelementptr inbounds ptr, ptr %18, i64 %19
  %21 = load i64, ptr %1, align 4
  %22 = load i64, ptr %20, align 4
  %23 = add i64 %21, %22
  %24 = load i64, ptr %1, align 4
  store i64 %23, ptr %1, align 4
  %25 = load i64, ptr %7, align 4
  %26 = load ptr, ptr %3, align 8
  %27 = getelementptr inbounds ptr, ptr %26, i64 %25
  %28 = load i64, ptr %8, align 4
  %29 = getelementptr inbounds ptr, ptr %27, i64 %28
  %30 = load i64, ptr %29, align 4
  call void @PrintInt(i64 %30)
  %31 = load i64, ptr %7, align 4
  %32 = mul i64 %31, 2
  %33 = getelementptr inbounds ptr, ptr @Global2dArray, i64 %32
  %34 = load i64, ptr %8, align 4
  %35 = getelementptr inbounds ptr, ptr %33, i64 %34
  %36 = load i64, ptr %2, align 4
  %37 = load i64, ptr %35, align 4
  %38 = add i64 %36, %37
  %39 = load i64, ptr %2, align 4
  store i64 %38, ptr %2, align 4
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.body
  %40 = load i64, ptr %8, align 4
  %41 = icmp slt i64 %40, 2
  br i1 %41, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %42 = load i64, ptr %8, align 4
  %43 = add i64 %42, 1
  store i64 %43, ptr %8, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

exit:                                             ; preds = %return, %for.end
  %44 = load i64, ptr %0, align 4
  ret i64 %44
}
