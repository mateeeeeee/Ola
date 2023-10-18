; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  %3 = alloca i64, align 8
  store i64 10, ptr %3, align 4
  %4 = load i64, ptr %1, align 4
  %ifcond = icmp ne i64 %4, 0
  br i1 %ifcond, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %5 = load ptr, ptr %1, align 8
  store ptr %5, ptr %0, align 8
  br label %exit

if.else:                                          ; preds = %entry
  %6 = load i64, ptr %2, align 4
  %ifcond2 = icmp ne i64 %6, 0
  br i1 %ifcond2, label %if.then1, label %if.end

if.end:                                           ; preds = %return9, %return7, %if.else4, %return3, %if.else, %return
  %nop = alloca i1, align 1
  br label %exit

if.then1:                                         ; preds = %if.else
  %7 = load ptr, ptr %2, align 8
  store ptr %7, ptr %0, align 8
  br label %exit

if.then5:                                         ; preds = %if.else4
  %8 = load ptr, ptr %3, align 8
  store ptr %8, ptr %0, align 8
  br label %exit

exit:                                             ; preds = %if.end, %if.else8, %if.then5, %if.then1, %if.then
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
