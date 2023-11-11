; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@arr2d = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]
@arr1d = internal global [4 x i64] [i64 1, i64 2, i64 3, i64 4]

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
  %1 = alloca i64, align 8
  %2 = load ptr, ptr getelementptr inbounds (ptr, ptr @arr2d, i64 1), align 8
  store ptr %2, ptr %1, align 8
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
