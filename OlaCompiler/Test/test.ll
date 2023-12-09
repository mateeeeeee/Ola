; ModuleID = 'test.ola'
source_filename = "test.ola"

%Derived = type { ptr, i64, i64 }
%Base = type { ptr }

@VTable_Base = internal constant [1 x ptr] zeroinitializer
@VTable_Derived = internal constant [2 x ptr] [ptr @"Derived::GetX", ptr @"Derived::GetY"]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare i64 @"Base::GetX"(ptr)

define i64 @"Derived::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 1
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
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 2
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
  store i64 100, ptr %3, align 4
  %4 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 2
  store i64 10, ptr %4, align 4
  %5 = load %Derived, ptr %1, align 8
  %6 = alloca ptr, align 8
  store ptr %1, ptr %6, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = getelementptr inbounds %Base, ptr %7, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds ptr, ptr %9, i32 0
  %11 = load ptr, ptr %10, align 8
  %12 = call i64 %11(ptr %7)
  store i64 %12, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %13 = load i64, ptr %0, align 4
  ret i64 %13
}
