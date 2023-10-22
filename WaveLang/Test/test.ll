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
  %0 = alloca i64, align 8
  %1 = call i64 @add(i64 5, i64 4)
  %.cast = inttoptr i64 %1 to ptr
  store ptr %.cast, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 8
  ret i64 %2
}
