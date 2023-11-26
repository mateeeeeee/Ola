; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64, i64 }

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"S::Init"(ptr %this, i64 %x, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %y, ptr %1, align 4
  %2 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %3 = load i64, ptr %2, align 4
  %4 = load i64, ptr %0, align 4
  %5 = load ptr, ptr %0, align 8
  store ptr %5, ptr %2, align 8
  %6 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %7 = load i64, ptr %6, align 4
  %8 = load i64, ptr %1, align 4
  %9 = load ptr, ptr %1, align 8
  store ptr %9, ptr %6, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define ptr @"S::X"(ptr %this) {
entry:
  %0 = alloca ptr, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load ptr, ptr %1, align 8
  store ptr %3, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load ptr, ptr %0, align 8
  ret ptr %4
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  store i64 0, ptr %2, align 4
  %3 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  store i64 0, ptr %3, align 4
  call void @"S::Init"(ptr %1, i64 10, i64 10)
  %4 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %5 = load i64, ptr %4, align 4
  %6 = alloca ptr, align 8
  store ptr %4, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %9 = load i64, ptr %8, align 4
  %10 = alloca ptr, align 8
  %11 = load ptr, ptr %8, align 8
  store ptr %11, ptr %10, align 8
  %12 = add i64 %9, 1
  store i64 %12, ptr %8, align 4
  %13 = load ptr, ptr %7, align 8
  %14 = load i64, ptr %7, align 4
  call void @PrintInt(i64 %14)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %15 = load i64, ptr %0, align 4
  ret i64 %15
}
