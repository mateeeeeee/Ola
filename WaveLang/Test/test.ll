; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 10, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = load i64, ptr %1, align 4
  %4 = sub i64 %3, 10
  store i64 %4, ptr %2, align 4
  %5 = load i64, ptr %2, align 4
  %6 = add i64 %5, 1
  %ifcond = icmp ne i64 %6, 0
  br i1 %ifcond, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %7 = load i64, ptr %2, align 4
  %8 = add i64 %7, 5
  %9 = load i64, ptr %2, align 4
  store i64 %8, ptr %2, align 4
  %10 = load i64, ptr %2, align 4
  %11 = load i64, ptr %2, align 4
  %12 = mul i64 %10, %11
  store i64 %12, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  br label %if.end

if.else:                                          ; preds = %entry
  %13 = load i64, ptr %2, align 4
  %14 = sub i64 %13, 3
  %15 = load i64, ptr %1, align 4
  store i64 %14, ptr %1, align 4
  %16 = load i64, ptr %1, align 4
  %17 = mul i64 %16, 2
  store i64 %17, ptr %0, align 4
  br label %exit

return1:                                          ; No predecessors!
  br label %if.end

if.end:                                           ; preds = %return1, %return
  store i64 0, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %if.end, %if.else, %if.then
  %18 = load i64, ptr %0, align 4
  ret i64 %18
}
