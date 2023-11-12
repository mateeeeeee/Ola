; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define internal i64 @add(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  %1 = add i64 %a, %b
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @add(i64 3, i64 1)
  %2 = alloca i64, align 8
  store i64 %1, ptr %2, align 4
  %3 = load i64, ptr %2, align 4
  call void @PrintInteger(i64 %3)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
