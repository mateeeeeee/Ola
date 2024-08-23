; ModuleID = 'test.ola'
source_filename = "test.ola"

@Array = internal global [3 x i64] zeroinitializer

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 2, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = getelementptr inbounds ptr, ptr @Array, i64 %2
  %4 = load i64, ptr %3, align 4
  store i64 10, ptr %3, align 4
  %5 = load i64, ptr %1, align 4
  %6 = getelementptr inbounds ptr, ptr @Array, i64 %5
  %7 = load ptr, ptr %6, align 8
  store ptr %7, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %8 = load i64, ptr %0, align 4
  ret i64 %8
}
