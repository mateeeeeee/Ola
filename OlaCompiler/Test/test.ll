; ModuleID = 'test.ola'
source_filename = "test.ola"

%D = type { i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @"D::X"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %D, ptr %this, i32 0, i32 0
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
  %1 = alloca %D, align 8
  %2 = getelementptr inbounds %D, ptr %1, i32 0, i32 0
  store i64 0, ptr %2, align 4
  %3 = call i64 @"D::X"(ptr %1)
  store i64 %3, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}
