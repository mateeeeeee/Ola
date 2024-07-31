; ModuleID = 'test_shift.ola'
source_filename = "test_shift.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestShiftOperatorsIntegers() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 2, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = shl i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 20
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %1, align 4
  %10 = ashr i64 %8, %9
  %11 = alloca i64, align 8
  store i64 %10, ptr %11, align 4
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 1
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestCompoundShiftOperatorsIntegers() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 2, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = shl i64 %2, %3
  %5 = load i64, ptr %0, align 4
  store i64 %4, ptr %0, align 4
  %6 = load i64, ptr %0, align 4
  %7 = icmp eq i64 %6, 20
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %1, align 4
  %10 = ashr i64 %8, %9
  %11 = load i64, ptr %0, align 4
  store i64 %10, ptr %0, align 4
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 5
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestShiftOperatorsIntegers()
  call void @TestCompoundShiftOperatorsIntegers()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
