; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = add i64 %1, 3
  %3 = alloca i64, align 8
  store i64 %2, ptr %3, align 4
  %4 = load i64, ptr %3, align 4
  %5 = add i64 %4, 2
  %6 = load i64, ptr %0, align 4
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
