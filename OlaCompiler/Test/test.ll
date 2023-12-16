; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define internal i64 @f(i64 %a) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  %2 = load i64, ptr %0, align 4
  %3 = mul i64 %2, 2
  store i64 %3, ptr %1, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %1, align 4
  ret i64 %4
}

define internal i64 @f.1(ptr %c) {
entry:
  %0 = alloca ptr, align 8
  store ptr %c, ptr %0, align 8
  %1 = alloca i64, align 8
  call void @PrintString(ptr %0)
  br label %exit

exit:                                             ; preds = %entry
  %2 = load i64, ptr %1, align 4
  ret i64 %2
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @f(i64 5)
  %2 = alloca i64, align 8
  store i64 %1, ptr %2, align 4
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
