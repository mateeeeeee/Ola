; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64 }

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"S::Init"(ptr %this, i64 %x) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define ptr @"S::X"(ptr %this) {
entry:
  %0 = alloca ptr, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  store ptr %1, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load ptr, ptr %0, align 8
  ret ptr %3
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  store i64 10, ptr %2, align 4
  %3 = call ptr @"S::X"(ptr %1)
  %4 = load ptr, ptr %3, align 8
  %5 = alloca ptr, align 8
  store ptr %3, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %8 = load i64, ptr %7, align 4
  call void @PrintInt(i64 %8)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
