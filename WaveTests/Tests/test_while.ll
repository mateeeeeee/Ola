; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %storemerge = phi i64 [ %4, %while.body ], [ 1, %entry ]
  %.0 = phi i64 [ %3, %while.body ], [ 0, %entry ]
  store i64 %storemerge, ptr %0, align 8
  %1 = icmp slt i64 %storemerge, 6
  br i1 %1, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %.0, %2
  %4 = add i64 %2, 1
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %5 = icmp eq i64 %.0, 15
  call void @Assert(i1 %5)
  %6 = alloca i64, align 8
  store i64 0, ptr %6, align 8
  br label %while.cond1

while.cond1:                                      ; preds = %while.body2, %while.end
  %7 = load i64, ptr %6, align 8
  %8 = icmp sgt i64 %7, 0
  br i1 %8, label %while.body2, label %while.end3

while.body2:                                      ; preds = %while.cond1
  call void @Assert(i1 false)
  br label %while.cond1

while.end3:                                       ; preds = %while.cond1
  %9 = load i64, ptr %6, align 8
  %10 = icmp eq i64 %9, 0
  call void @Assert(i1 %10)
  %11 = alloca i64, align 8
  store i64 5, ptr %11, align 8
  %12 = alloca i64, align 8
  store i64 0, ptr %12, align 8
  br label %while.cond4

while.cond4:                                      ; preds = %if.end, %while.end3
  br i1 true, label %while.body5, label %while.end6.loopexit

while.body5:                                      ; preds = %while.cond4
  %13 = load i64, ptr %12, align 8
  %14 = add i64 %13, 1
  store i64 %14, ptr %12, align 8
  %15 = load i64, ptr %11, align 8
  %16 = icmp eq i64 %14, %15
  br i1 %16, label %if.then, label %if.end

while.end6.loopexit:                              ; preds = %while.cond4
  br label %while.end6

while.end6:                                       ; preds = %while.end6.loopexit, %if.then
  %17 = load i64, ptr %12, align 8
  %18 = load i64, ptr %11, align 8
  %19 = icmp eq i64 %17, %18
  call void @Assert(i1 %19)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

if.then:                                          ; preds = %while.body5
  br label %while.end6

if.else:                                          ; No predecessors!
  br label %exit

if.end:                                           ; preds = %while.body5
  br label %while.cond4

break:                                            ; No predecessors!
  br label %exit

exit:                                             ; preds = %break, %if.else, %return, %while.end6
  ret i64 0
}
