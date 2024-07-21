; ModuleID = 'test.ola'
source_filename = "test.ola"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 42, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  store i64 %2, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}
