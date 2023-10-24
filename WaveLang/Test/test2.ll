; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @f(i64 %a) {
entry:
  %0 = alloca i64, align 8
  %1 = mul i64 2, %a
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}
