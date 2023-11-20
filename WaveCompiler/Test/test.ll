; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%Foo.0 = type { i64 }
%Foo.1 = type { i64 }

@__StringLiteral0 = internal constant [5 x i8] c"ajmo\00"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"Foo::PrintX"(ptr %this) {
entry:
  call void @PrintString(ptr @__StringLiteral0)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Foo.0, align 8
  %2 = getelementptr inbounds %Foo.0, ptr %1, i32 0, i32 0
  store i64 5, ptr %2, align 4
  %3 = load ptr, ptr %1, align 8
  call void @"Foo::PrintX"(ptr %3)
  %4 = getelementptr inbounds %Foo.1, ptr %1, i32 0, i32 0
  %5 = load ptr, ptr %4, align 8
  store ptr %5, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
