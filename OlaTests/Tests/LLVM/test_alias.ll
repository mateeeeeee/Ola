; ModuleID = 'test_alias.ola'
source_filename = "test_alias.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  %2 = alloca [3 x i64], align 8
  %3 = getelementptr [3 x i64], ptr %2, i64 0, i64 0
  %4 = load i64, ptr %1, align 4
  store i64 %4, ptr %3, align 4
  %5 = getelementptr [3 x i64], ptr %2, i64 0, i64 1
  %6 = load i64, ptr %1, align 4
  store i64 %6, ptr %5, align 4
  %7 = getelementptr [3 x i64], ptr %2, i64 0, i64 2
  %8 = load i64, ptr %1, align 4
  store i64 %8, ptr %7, align 4
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
