; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @modifyArray(ptr %arr) {
entry:
  %0 = alloca ptr, align 8
  store ptr %arr, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds ptr, ptr %1, i64 0
  %3 = load i64, ptr %2, align 4
  store i64 100, ptr %2, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @modifyArray2([3 x i64] %arr) {
entry:
  %0 = alloca [3 x i64], align 8
  store [3 x i64] %arr, ptr %0, align 4
  %1 = getelementptr [3 x i64], ptr %0, i64 0, i64 0
  %2 = load i64, ptr %1, align 4
  store i64 100, ptr %1, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [3 x i64], align 8
  %2 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr [3 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [3 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = load [3 x i64], ptr %1, align 4
  call void @modifyArray2([3 x i64] %5)
  %6 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  %7 = load i64, ptr %6, align 4
  %8 = icmp eq i64 %7, 1
  call void @Assert(i1 %8)
  call void @modifyArray(ptr %1)
  %9 = getelementptr [3 x i64], ptr %1, i64 0, i64 0
  %10 = load i64, ptr %9, align 4
  %11 = icmp eq i64 %10, 100
  call void @Assert(i1 %11)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %12 = load i64, ptr %0, align 4
  ret i64 %12
}
