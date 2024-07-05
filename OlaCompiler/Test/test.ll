; ModuleID = 'test.ola'
source_filename = "test.ola"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
