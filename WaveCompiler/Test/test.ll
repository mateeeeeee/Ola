; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i1, align 1
  store i1 false, ptr %1, align 1
  %2 = load i1, ptr %1, align 1
  call void @Assert(i1 %2)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}
