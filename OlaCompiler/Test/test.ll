; ModuleID = 'test.ola'
source_filename = "test.ola"

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
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 1
  br i1 %3, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @PrintInt(i64 0)
  br label %if.end

if.else:                                          ; preds = %entry
  %4 = alloca i64, align 8
  store i64 0, ptr %4, align 4
  %5 = alloca i64, align 8
  store i64 1, ptr %5, align 4
  %6 = load i64, ptr %4, align 4
  call void @PrintInt(i64 %6)
  %7 = load i64, ptr %5, align 4
  call void @PrintInt(i64 %7)
  %8 = alloca i64, align 8
  store i64 2, ptr %8, align 4
  br label %for.cond

if.end:                                           ; preds = %for.end, %if.then
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

for.body:                                         ; preds = %for.cond
  %9 = load i64, ptr %4, align 4
  %10 = load i64, ptr %5, align 4
  %11 = add i64 %9, %10
  %12 = alloca i64, align 8
  store i64 %11, ptr %12, align 4
  %13 = load i64, ptr %4, align 4
  %14 = load i64, ptr %5, align 4
  %15 = load ptr, ptr %5, align 8
  store ptr %15, ptr %4, align 8
  %16 = load i64, ptr %5, align 4
  %17 = load i64, ptr %12, align 4
  %18 = load ptr, ptr %12, align 8
  store ptr %18, ptr %5, align 8
  %19 = load i64, ptr %12, align 4
  call void @PrintInt(i64 %19)
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %if.else
  %20 = load i64, ptr %8, align 4
  %21 = load i64, ptr %1, align 4
  %22 = icmp slt i64 %20, %21
  br i1 %22, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %23 = load i64, ptr %8, align 4
  %24 = alloca ptr, align 8
  %25 = load ptr, ptr %8, align 8
  store ptr %25, ptr %24, align 8
  %26 = add i64 %23, 1
  store i64 %26, ptr %8, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %nop1 = alloca i1, align 1
  br label %if.end

exit:                                             ; preds = %return, %if.end
  %27 = load i64, ptr %0, align 4
  ret i64 %27
}
