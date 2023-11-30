; ModuleID = 'test.wv'
source_filename = "test.wv"

@__StringLiteral0 = internal constant [5 x i8] c"Mate\00"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [5 x i8], align 1
  %2 = getelementptr [5 x i8], ptr %1, i64 0, i64 0
  store i8 77, ptr %2, align 1
  %3 = getelementptr [5 x i8], ptr %1, i64 0, i64 1
  store i8 97, ptr %3, align 1
  %4 = getelementptr [5 x i8], ptr %1, i64 0, i64 2
  store i8 116, ptr %4, align 1
  %5 = getelementptr [5 x i8], ptr %1, i64 0, i64 3
  store i8 101, ptr %5, align 1
  %6 = getelementptr [5 x i8], ptr %1, i64 0, i64 4
  store i8 0, ptr %6, align 1
  call void @PrintString(ptr %1)
  %7 = alloca i64, align 8
  store i64 24, ptr %7, align 4
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
