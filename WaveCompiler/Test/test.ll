; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @ModifyInt(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = load i64, ptr %1, align 4
  store i64 10, ptr %1, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  call void @ModifyInt(ptr %1)
  %3 = load i64, ptr %1, align 4
  call void @PrintInt(i64 %3)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
