; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { ptr, i64, i64 }
%Derived = type { ptr, i64, i64, i64 }
%ExtDerived = type { ptr, i64, i64, i64, i64 }

@VTable_Base = internal constant [2 x ptr] [ptr @"Base::GetX", ptr @"Base::GetY"]
@VTable_Derived = internal constant [2 x ptr] [ptr @"Derived::GetX", ptr @"Base::GetY"]
@VTable_ExtDerived = internal constant [3 x ptr] [ptr @"Derived::GetX", ptr @"ExtDerived::GetY", ptr @"ExtDerived::GetX"]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @"Base::GetX"(ptr %this) {
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

define i64 @"Base::GetY"(ptr %this) {
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

define i64 @"Derived::GetX"(ptr %this) {
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

define i64 @"ExtDerived::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %ExtDerived, ptr %this, i32 0, i32 4
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

define i64 @"ExtDerived::GetX"(ptr %this, i64 %0) {
entry:
  %1 = alloca i64, align 8
  store i64 %0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 100000, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %2, align 4
  ret i64 %3
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %ExtDerived, align 8
  %2 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 0
  store ptr @VTable_ExtDerived, ptr %2, align 8
  %3 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 3
  store i64 100, ptr %3, align 4
  %4 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 1
  store i64 10, ptr %4, align 4
  %5 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 2
  store i64 20, ptr %5, align 4
  %6 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 4
  store i64 200, ptr %6, align 4
  %7 = load %ExtDerived, ptr %1, align 8
  %8 = alloca ptr, align 8
  store ptr %1, ptr %8, align 8
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %Base, ptr %9, i32 0, i32 0
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds ptr, ptr %11, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = call i64 %13(ptr %9)
  %15 = getelementptr inbounds %ExtDerived, ptr %1, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = getelementptr inbounds ptr, ptr %16, i32 2
  %18 = load ptr, ptr %17, align 8
  %19 = call i64 %18(ptr %1, i64 1)
  %20 = add i64 %14, %19
  store i64 %20, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %21 = load i64, ptr %0, align 4
  ret i64 %21
}
