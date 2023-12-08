; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { i64 }
%Derived = type { i64, i64 }

@VTable_Base = internal constant [1 x ptr] [ptr @"Base::GetX"]
@VTable_Derived = internal constant [1 x ptr] [ptr @"Derived::GetX"]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @"Base::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Base, ptr %this, i32 0, i32 0
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

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Derived, align 8
  %2 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 1
  store i64 2, ptr %3, align 4
  %4 = load %Derived, ptr %1, align 4
  %5 = alloca ptr, align 8
  store ptr %1, ptr %5, align 8
  %6 = load ptr, ptr %5, align 8
  %7 = call i64 @"Base::GetX"(ptr %6)
  store i64 %7, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  store i64 0, ptr %0, align 4
  br label %exit

return1:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return1, %return, %entry
  %8 = load i64, ptr %0, align 4
  ret i64 %8
}
