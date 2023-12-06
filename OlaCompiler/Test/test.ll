; ModuleID = 'test.ola'
source_filename = "test.ola"

%S = type {}

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @GetX() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 20, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 10
  store i64 %3, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define i64 @GetY() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @GetX()
  %2 = mul i64 %1, 2
  store i64 %2, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define i64 @"S::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 25, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = add i64 %2, 10
  store i64 %3, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define i64 @"S::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @"S::GetX"(ptr %this)
  %2 = mul i64 %1, 2
  store i64 %2, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = call i64 @"S::GetY"(ptr %1)
  %3 = call i64 @GetY()
  %4 = add i64 %2, %3
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
