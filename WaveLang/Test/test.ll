; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @add(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  %1 = add i64 %a, %b
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp ne i64 %2, 0
  %4 = select i1 %3, i64 10, i64 0
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
