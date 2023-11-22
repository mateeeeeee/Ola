; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @ModifyInt(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 1
  store i64 %3, ptr %1, align 4
  %4 = load ptr, ptr %1, align 8
  %5 = load i64, ptr %4, align 4
  %6 = alloca i64, align 8
  store i64 %5, ptr %6, align 4
  %7 = load i64, ptr %6, align 4
  %8 = add i64 %7, 1
  store i64 %8, ptr %6, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 9, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  call void @ModifyInt(ptr %1)
  %3 = load ptr, ptr %1, align 8
  store ptr %3, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
