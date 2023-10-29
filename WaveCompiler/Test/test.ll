; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = load i64, ptr %1, align 4
  %4 = sub i64 0, %3
  store i64 %4, ptr %2, align 4
  %5 = load i64, ptr %2, align 4
  %6 = icmp eq i64 %5, -5
  call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 10, ptr %7, align 4
  %8 = alloca i64, align 8
  %9 = load i64, ptr %7, align 4
  %10 = load ptr, ptr %7, align 8
  store ptr %10, ptr %8, align 8
  %11 = load i64, ptr %8, align 4
  %12 = icmp eq i64 %11, 10
  call void @Assert(i1 %12)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %13 = load i64, ptr %0, align 4
  ret i64 %13
}
