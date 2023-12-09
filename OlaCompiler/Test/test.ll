; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { ptr, i64 }
%Derived = type { ptr, i64, i64 }
%Abstract = type { ptr }

@VTable_Abstract = internal constant [1 x ptr] zeroinitializer
@VTable_Base = internal constant [2 x ptr] [ptr @"Base::GetX", ptr @"Base::GetSumX"]
@VTable_Derived = internal constant [2 x ptr] [ptr @"Derived::GetX", ptr @"Derived::GetSumX"]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare i64 @"Abstract::GetX"(ptr)

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

define i64 @"Base::GetSumX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Base, ptr %this, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds ptr, ptr %2, i32 0
  %4 = load ptr, ptr %3, align 8
  %5 = call i64 %4(ptr %this)
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
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

define i64 @"Derived::GetSumX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  %3 = getelementptr inbounds ptr, ptr %2, i32 0
  %4 = load ptr, ptr %3, align 8
  %5 = call i64 %4(ptr %this)
  %6 = call i64 @"Base::GetX"(ptr %this)
  %7 = add i64 %5, %6
  store i64 %7, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %8 = load i64, ptr %0, align 4
  ret i64 %8
}

define internal void @TestBase(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Abstract, ptr %1, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds ptr, ptr %3, i32 0
  %5 = load ptr, ptr %4, align 8
  %6 = call i64 %5(ptr %1)
  %7 = icmp eq i64 %6, 1
  call void @Assert(i1 %7)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestDerived(ptr %a) {
entry:
  %0 = alloca ptr, align 8
  store ptr %a, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Abstract, ptr %1, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds ptr, ptr %3, i32 0
  %5 = load ptr, ptr %4, align 8
  %6 = call i64 %5(ptr %1)
  %7 = icmp eq i64 %6, 10
  call void @Assert(i1 %7)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestDerived2(ptr %b) {
entry:
  %0 = alloca ptr, align 8
  store ptr %b, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %Base, ptr %1, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds ptr, ptr %3, i32 0
  %5 = load ptr, ptr %4, align 8
  %6 = call i64 %5(ptr %1)
  %7 = icmp eq i64 %6, 10
  call void @Assert(i1 %7)
  %8 = getelementptr inbounds %Base, ptr %1, i32 0, i32 0
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds ptr, ptr %9, i32 1
  %11 = load ptr, ptr %10, align 8
  %12 = call i64 %11(ptr %1)
  %13 = icmp eq i64 %12, 11
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Base, align 8
  %2 = getelementptr inbounds %Base, ptr %1, i32 0, i32 0
  store ptr @VTable_Base, ptr %2, align 8
  %3 = getelementptr inbounds %Base, ptr %1, i32 0, i32 1
  store i64 1, ptr %3, align 4
  %4 = load %Base, ptr %1, align 8
  call void @TestBase(ptr %1)
  %5 = alloca %Derived, align 8
  %6 = getelementptr inbounds %Derived, ptr %5, i32 0, i32 0
  store ptr @VTable_Derived, ptr %6, align 8
  %7 = getelementptr inbounds %Derived, ptr %5, i32 0, i32 1
  store i64 1, ptr %7, align 4
  %8 = getelementptr inbounds %Derived, ptr %5, i32 0, i32 2
  store i64 10, ptr %8, align 4
  %9 = load %Derived, ptr %5, align 8
  call void @TestDerived(ptr %5)
  %10 = load %Derived, ptr %5, align 8
  call void @TestDerived2(ptr %5)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %11 = load i64, ptr %0, align 4
  ret i64 %11
}
