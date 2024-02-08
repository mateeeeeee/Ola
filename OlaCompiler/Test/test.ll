; ModuleID = 'test.ola'
source_filename = "test.ola"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  ret i64 10
}
