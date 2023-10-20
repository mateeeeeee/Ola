; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp sgt i64 %2, 0
  br i1 %3, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %4 = load i64, ptr %1, align 4
  %5 = add i64 %4, 4
  %6 = load i64, ptr %1, align 4
  store i64 %5, ptr %1, align 4
  %7 = alloca i64, align 8
  %8 = load i64, ptr %1, align 4
  %9 = sub i64 %8, 1
  store i64 %9, ptr %7, align 4
  %10 = load i64, ptr %7, align 4
  %11 = mul i64 %10, 5
  %12 = load i64, ptr %7, align 4
  store i64 %11, ptr %7, align 4
  %13 = load ptr, ptr %7, align 8
  store ptr %13, ptr %0, align 8
  br label %exit

if.else:                                          ; preds = %entry
  %14 = alloca i64, align 8
  store i64 0, ptr %14, align 4
  br label %for.cond

if.end:                                           ; preds = %return1, %return
  store i64 100, ptr %0, align 4
  br label %exit

for.body:                                         ; preds = %for.cond
  %15 = load i64, ptr %1, align 4
  %16 = alloca ptr, align 8
  %17 = load ptr, ptr %1, align 8
  store ptr %17, ptr %16, align 8
  %18 = add i64 %15, 1
  store i64 %18, ptr %1, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %if.else
  %19 = load i64, ptr %14, align 4
  %20 = icmp slt i64 %19, 10
  br i1 %20, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %21 = load i64, ptr %14, align 4
  %22 = add i64 %21, 1
  store i64 %22, ptr %14, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %23 = load ptr, ptr %1, align 8
  store ptr %23, ptr %0, align 8
  br label %exit

exit:                                             ; preds = %if.end, %for.end, %if.then
  %24 = load i64, ptr %0, align 4
  ret i64 %24
}
