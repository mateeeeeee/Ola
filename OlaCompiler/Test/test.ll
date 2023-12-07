; ModuleID = 'test.ola'
source_filename = "test.ola"

%Derived = type { i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @"Derived::GetSum"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 1
  %2 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 0
  %3 = load i64, ptr %1, align 4
  %4 = load i64, ptr %2, align 4
  %5 = add i64 %3, %4
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Derived, align 8
  %2 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr inbounds %Derived, ptr %1, i32 0, i32 1
  store i64 2, ptr %3, align 4
  %4 = call i64 @"Derived::GetSum"(ptr %1)
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}
