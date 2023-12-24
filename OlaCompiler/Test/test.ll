; ModuleID = 'test.ola'
source_filename = "test.ola"

%B = type { i64 }
%D = type { i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"B::B__I"(ptr %this, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %y, ptr %0, align 4
  %1 = getelementptr inbounds %B, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"B::B__I__I"(ptr %this, i64 %x, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %y, ptr %1, align 4
  %2 = getelementptr inbounds %B, ptr %this, i32 0, i32 0
  %3 = load i64, ptr %0, align 4
  %4 = load i64, ptr %1, align 4
  %5 = mul i64 %3, %4
  %6 = load i64, ptr %2, align 4
  store i64 %5, ptr %2, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"D::D__I"(ptr %this, i64 %x) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = mul i64 %1, 2
  call void @"B::B__I"(ptr %this, i64 %2)
  %3 = getelementptr inbounds %D, ptr %this, i32 0, i32 1
  %4 = load i64, ptr %3, align 4
  %5 = load i64, ptr %0, align 4
  %6 = load ptr, ptr %0, align 8
  store ptr %6, ptr %3, align 8
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
  %2 = load i64, ptr %0, align 4
  %3 = mul i64 %2, 2
  %4 = load i64, ptr %1, align 4
  %5 = mul i64 %4, 2
  call void @"B::B__I__I"(ptr %this, i64 %3, i64 %5)
  %6 = getelementptr inbounds %D, ptr %this, i32 0, i32 1
  %7 = load i64, ptr %0, align 4
  %8 = load i64, ptr %1, align 4
  %9 = mul i64 %7, %8
  %10 = load i64, ptr %6, align 4
  store i64 %9, ptr %6, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %D, align 8
  %2 = getelementptr inbounds %D, ptr %1, i32 0, i32 0
  store i64 0, ptr %2, align 4
  %3 = getelementptr inbounds %D, ptr %1, i32 0, i32 1
  store i64 0, ptr %3, align 4
  call void @"D::D__I"(ptr %1, i64 5)
  %4 = alloca %D, align 8
  %5 = getelementptr inbounds %D, ptr %4, i32 0, i32 0
  store i64 0, ptr %5, align 4
  %6 = getelementptr inbounds %D, ptr %4, i32 0, i32 1
  store i64 0, ptr %6, align 4
  call void @"D::D__I__I"(ptr %4, i64 2, i64 3)
  %7 = getelementptr inbounds %D, ptr %1, i32 0, i32 1
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 5
  call void @Assert(i1 %9)
  %10 = getelementptr inbounds %D, ptr %1, i32 0, i32 0
  %11 = load i64, ptr %10, align 4
  %12 = icmp eq i64 %11, 10
  call void @Assert(i1 %12)
  %13 = getelementptr inbounds %D, ptr %4, i32 0, i32 1
  %14 = load i64, ptr %13, align 4
  %15 = icmp eq i64 %14, 6
  call void @Assert(i1 %15)
  %16 = getelementptr inbounds %D, ptr %4, i32 0, i32 0
  %17 = load i64, ptr %16, align 4
  %18 = icmp eq i64 %17, 24
  call void @Assert(i1 %18)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %19 = load i64, ptr %0, align 4
  ret i64 %19
}
