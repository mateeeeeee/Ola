; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define internal i64 @square(i64 %x) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = mul i64 %x, %x
  ret i64 %0
}

define internal i64 @add(i64 %a, i64 %b) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = add i64 %a, %b
  ret i64 %0
}

define internal i1 @isEven(i64 %x) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = and i64 %x, 1
  %1 = icmp eq i64 %0, 0
  ret i1 %1
}

define internal i64 @fma(i64 %a, i64 %b, i64 %c) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = mul i64 %a, %b
  %1 = add i64 %0, %c
  ret i64 %1
}

define internal i1 @isInRange(i64 %x, i64 %lowerBound, i64 %upperBound) {
entry:
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  %0 = icmp sge i64 %x, %lowerBound
  %1 = icmp sle i64 %x, %upperBound
  %2 = and i1 %0, %1
  ret i1 %2
}

define i64 @main() {
entry:
  %0 = call i64 @square(i64 5)
  %1 = icmp eq i64 %0, 25
  call void @Assert(i1 %1)
  %2 = call i1 @isEven(i64 8)
  call void @Assert(i1 %2)
  %3 = call i64 @square(i64 -4)
  %4 = icmp eq i64 %3, 16
  call void @Assert(i1 %4)
  %5 = call i1 @isEven(i64 7)
  %6 = xor i1 %5, true
  call void @Assert(i1 %6)
  %7 = call i64 @add(i64 5, i64 12)
  %8 = icmp eq i64 %7, 17
  call void @Assert(i1 %8)
  %9 = call i64 @fma(i64 2, i64 3, i64 4)
  %10 = icmp eq i64 %9, 10
  call void @Assert(i1 %10)
  %11 = call i1 @isInRange(i64 5, i64 1, i64 10)
  call void @Assert(i1 %11)
  %12 = call i64 @fma(i64 6, i64 2, i64 8)
  %13 = icmp eq i64 %12, 20
  call void @Assert(i1 %13)
  %14 = call i1 @isInRange(i64 5, i64 6, i64 10)
  %15 = xor i1 %14, true
  call void @Assert(i1 %15)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  ret i64 0
}
