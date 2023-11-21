; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%Foo = type { i64, i64 }

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"Foo::SetX"(ptr %this, i64 %x) {
entry:
  %0 = getelementptr inbounds %Foo, ptr %this, i32 0, i32 0
  %1 = load i64, ptr %0, align 4
  store i64 %x, ptr %0, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @"Foo::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Foo, ptr %this, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
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
  %1 = alloca %Foo, align 8
  %2 = getelementptr inbounds %Foo, ptr %1, i32 0, i32 0
  store i64 5, ptr %2, align 4
  %3 = getelementptr inbounds %Foo, ptr %1, i32 0, i32 1
  store i64 10, ptr %3, align 4
  call void @"Foo::SetX"(ptr %1, i64 12)
  %4 = alloca %Foo, align 8
  %5 = load ptr, ptr %1, align 8
  store ptr %5, ptr %4, align 8
  call void @"Foo::SetX"(ptr %1, i64 24)
  %6 = call i64 @"Foo::GetX"(ptr %4)
  store i64 %6, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
