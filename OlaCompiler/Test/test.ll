; ModuleID = 'test.ola'
source_filename = "test.ola"

%S = type { i64, i64, i64 }

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"S::PrintX"(ptr %this, i64 %x) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  call void @PrintInt(i64 %2)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  store i64 20, ptr %2, align 4
  %3 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  store i64 10, ptr %3, align 4
  %4 = getelementptr inbounds %S, ptr %1, i32 0, i32 2
  store i64 30, ptr %4, align 4
  call void @"S::PrintX"(ptr %1, i64 100)
  br label %exit

exit:                                             ; preds = %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
