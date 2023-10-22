; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @add(i64 %a, i64 %b) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = add i64 %a, %b
  ret i64 %0
}

define i64 @main() {
entry:
  %0 = call i64 @add(i64 5, i64 4)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = add i64 %0, 1
  ret i64 %1
}
