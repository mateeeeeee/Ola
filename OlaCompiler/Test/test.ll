; ModuleID = 'test.ola'
source_filename = "test.ola"

%B = type { i64 }
%D = type { i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

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
  call void @"D::D__I"(ptr %this, i64 %2)
  %3 = getelementptr inbounds %D, ptr %this, i32 0, i32 1
  %4 = getelementptr inbounds %D, ptr %this, i32 0, i32 1
  %5 = load i64, ptr %4, align 4
  %6 = load i64, ptr %1, align 4
  %7 = mul i64 %5, %6
  %8 = load i64, ptr %3, align 4
  store i64 %7, ptr %3, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @Test__D(%D %d) {
entry:
  %0 = alloca %D, align 8
  store %D %d, ptr %0, align 4
  %1 = getelementptr inbounds %D, ptr %0, i32 0, i32 1
  %2 = load i64, ptr %1, align 4
  call void @PrintInt(i64 %2)
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
  %4 = getelementptr inbounds %D, ptr %1, i32 0, i32 1
  %5 = load i64, ptr %4, align 4
  %6 = icmp eq i64 %5, 5
  call void @Assert(i1 %6)
  %7 = getelementptr inbounds %D, ptr %1, i32 0, i32 0
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 10
  call void @Assert(i1 %9)
  %10 = alloca %D, align 8
  %11 = getelementptr inbounds %D, ptr %10, i32 0, i32 0
  store i64 0, ptr %11, align 4
  %12 = getelementptr inbounds %D, ptr %10, i32 0, i32 1
  store i64 0, ptr %12, align 4
  call void @"D::D__I__I"(ptr %10, i64 2, i64 3)
  %13 = getelementptr inbounds %D, ptr %10, i32 0, i32 1
  %14 = load i64, ptr %13, align 4
  %15 = icmp eq i64 %14, 6
  call void @Assert(i1 %15)
  %16 = getelementptr inbounds %D, ptr %10, i32 0, i32 0
  %17 = load i64, ptr %16, align 4
  %18 = icmp eq i64 %17, 4
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
