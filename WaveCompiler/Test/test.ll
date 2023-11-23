; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define internal void @ModifyInt(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 1
  store i64 %3, ptr %1, align 4
  %4 = load ptr, ptr %1, align 8
  %5 = load i64, ptr %1, align 4
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
  %3 = load i64, ptr %1, align 4
  %4 = icmp eq i64 %3, 10
  call void @Assert(i1 %4)
  %5 = load i64, ptr %1, align 4
  %6 = alloca ptr, align 8
  store ptr %1, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = load i64, ptr %7, align 4
  %9 = add i64 %8, 1
  store i64 %9, ptr %7, align 4
  %10 = load i64, ptr %1, align 4
  %11 = icmp eq i64 %10, 11
  call void @Assert(i1 %11)
  %12 = load ptr, ptr %1, align 8
  store ptr %12, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %13 = load i64, ptr %0, align 4
  ret i64 %13
}
