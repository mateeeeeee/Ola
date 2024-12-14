; ModuleID = 'test.ola'
source_filename = "test.ola"

define internal i64 @min__I__I(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = icmp slt i64 %4, %5
  br i1 %6, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %7 = load i64, ptr %3, align 4
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %0, align 4
  store i64 %9, ptr %3, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %10 = load i64, ptr %3, align 4
  %11 = load i64, ptr %1, align 4
  %12 = load i64, ptr %1, align 4
  store i64 %12, ptr %3, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %13 = load i64, ptr %3, align 4
  store i64 %13, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %if.end
  %14 = load i64, ptr %2, align 4
  ret i64 %14
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @min__I__I(i64 3, i64 4)
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}
