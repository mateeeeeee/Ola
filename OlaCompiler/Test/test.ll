; ModuleID = 'test.ola'
source_filename = "test.ola"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 6
  %4 = alloca i64, align 8
  store i64 %3, ptr %4, align 4
  %5 = load i64, ptr %4, align 4
  %6 = icmp sgt i64 %5, 10
  br i1 %6, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %7 = load i64, ptr %1, align 4
  %8 = alloca ptr, align 8
  store i64 %7, ptr %8, align 4
  %9 = add i64 %7, 1
  store i64 %9, ptr %1, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  store i64 2, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %if.then
  %10 = load i64, ptr %1, align 4
  store i64 %10, ptr %0, align 4
  br label %exit

return1:                                          ; No predecessors!
  %nop2 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return1, %return, %if.end, %if.else
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
