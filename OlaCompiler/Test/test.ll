; ModuleID = 'test.ola'
source_filename = "test.ola"

%D = type { i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"D::D__I"(ptr %this, i64 %x) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = getelementptr inbounds %D, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"D::D__I__I"(ptr %this, i64 %x, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %y, ptr %1, align 4
  %2 = getelementptr inbounds %D, ptr %this, i32 0, i32 0
  %3 = load i64, ptr %0, align 4
  %4 = load i64, ptr %1, align 4
  %5 = mul i64 %3, %4
  %6 = load i64, ptr %2, align 4
  store i64 %5, ptr %2, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

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
  call void @"D::D__I"(ptr %1, i64 5)
  %3 = alloca %D, align 8
  %4 = getelementptr inbounds %D, ptr %3, i32 0, i32 0
  store i64 0, ptr %4, align 4
  call void @"D::D__I__I"(ptr %3, i64 2, i64 3)
  %5 = call i64 @"D::X"(ptr %3)
  store i64 %5, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %6 = load i64, ptr %0, align 4
  ret i64 %6
}
