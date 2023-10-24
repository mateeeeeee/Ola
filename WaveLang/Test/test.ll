; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  %2 = call i64 @ReadInteger()
  store i64 %2, ptr %1, align 4
  %3 = load i64, ptr %1, align 4
  call void @PrintInteger(i64 %3)
  %4 = load i64, ptr %1, align 4
  %5 = icmp sgt i64 %4, 10
  call void @Assert(i1 %5)
  %6 = load ptr, ptr %1, align 8
  store ptr %6, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
