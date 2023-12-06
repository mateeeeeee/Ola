; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { i64 }
%Derived = type { i64, i64 }

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"Base::PrintY"(ptr %this) {
entry:
  %0 = getelementptr inbounds %Base, ptr %this, i32 0, i32 0
  %1 = load i64, ptr %0, align 4
  call void @PrintInt(i64 %1)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"Derived::PrintX"(ptr %this) {
entry:
  call void @"Base::PrintY"(ptr %this)
  %0 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 1
  %1 = load i64, ptr %0, align 4
  call void @PrintInt(i64 %1)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Derived, align 8
  %2 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 0
  store i64 10, ptr %2, align 4
  %3 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 1
  store i64 30, ptr %3, align 4
  call void @"Derived::PrintX"(ptr %1)
  br label %exit

exit:                                             ; preds = %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
