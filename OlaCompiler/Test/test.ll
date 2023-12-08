; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { ptr, i64, i64 }
%Derived = type { ptr, i64, i64, i64, i64 }

@VTable_Base = internal constant [2 x ptr] [ptr @"Base::GetX", ptr @"Base::GetZ"]
@VTable_Derived = internal constant [3 x ptr] [ptr @"Derived::GetX", ptr @"Base::GetZ", ptr @"Derived::GetY"]

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define i64 @"Base::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Base, ptr %this, i32 0, i32 2
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

define i64 @"Base::GetZ"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Base, ptr %this, i32 0, i32 1
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

define i64 @"Derived::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 4
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

define i64 @"Derived::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 3
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
  %1 = alloca %Derived, align 8
  %2 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 0
  store ptr @VTable_Derived, ptr %2, align 8
  %3 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 1
  store i64 10, ptr %3, align 4
  %4 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 2
  store i64 123, ptr %4, align 4
  %5 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 3
  store i64 1000, ptr %5, align 4
  %6 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 4
  store i64 100, ptr %6, align 4
  %7 = load %Derived, ptr %1, align 8
  %8 = alloca ptr, align 8
  store ptr %1, ptr %8, align 8
  %9 = load ptr, ptr %8, align 8
  %10 = call i64 @"Derived::GetX"(ptr %1)
  call void @PrintInt(i64 %10)
  br label %exit

exit:                                             ; preds = %entry
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
