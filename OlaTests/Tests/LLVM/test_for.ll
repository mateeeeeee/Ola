; ModuleID = 'test_for.ola'
source_filename = "test_for.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestForLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %2, %3
  %5 = load i64, ptr %0, align 4
  store i64 %4, ptr %0, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %6 = load i64, ptr %1, align 4
  %7 = icmp sle i64 %6, 5
  br i1 %7, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %8 = load i64, ptr %1, align 4
  %9 = alloca ptr, align 8
  %10 = load i64, ptr %1, align 4
  store i64 %10, ptr %9, align 4
  %11 = add i64 %8, 1
  store i64 %11, ptr %1, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 15
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %for.end
  ret void
}

define internal void @TestForLoopBoolCondition() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %1 = load i64, ptr %0, align 4
  %2 = alloca ptr, align 8
  %3 = load i64, ptr %0, align 4
  store i64 %3, ptr %2, align 4
  %4 = add i64 %1, 1
  store i64 %4, ptr %0, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %5 = load i64, ptr %0, align 4
  %6 = icmp slt i64 %5, 3
  br i1 %6, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %7 = load i64, ptr %0, align 4
  %8 = icmp eq i64 %7, 3
  call void @Assert(i1 %8)
  br label %exit

exit:                                             ; preds = %for.end
  ret void
}

define internal void @TestForLoopMultipleExpressions() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 5, ptr %2, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %3 = load i64, ptr %1, align 4
  %4 = load i64, ptr %2, align 4
  %5 = add i64 %3, %4
  %6 = load i64, ptr %0, align 4
  %7 = add i64 %6, %5
  %8 = load i64, ptr %0, align 4
  store i64 %7, ptr %0, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %9 = load i64, ptr %1, align 4
  %10 = icmp sle i64 %9, 3
  br i1 %10, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %11 = load i64, ptr %1, align 4
  %12 = alloca ptr, align 8
  %13 = load i64, ptr %1, align 4
  store i64 %13, ptr %12, align 4
  %14 = add i64 %11, 1
  store i64 %14, ptr %1, align 4
  %15 = load i64, ptr %2, align 4
  %16 = alloca ptr, align 8
  %17 = load i64, ptr %2, align 4
  store i64 %17, ptr %16, align 4
  %18 = sub i64 %15, 1
  store i64 %18, ptr %2, align 4
  %19 = load i64, ptr %12, align 4
  %20 = load i64, ptr %16, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %21 = load i64, ptr %0, align 4
  %22 = icmp eq i64 %21, 18
  call void @Assert(i1 %22)
  br label %exit

exit:                                             ; preds = %for.end
  ret void
}

define internal void @TestNestedForLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %2 = load i64, ptr %0, align 4
  %3 = icmp slt i64 %2, 3
  br i1 %3, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %4 = load i64, ptr %0, align 4
  %5 = alloca ptr, align 8
  %6 = load i64, ptr %0, align 4
  store i64 %6, ptr %5, align 4
  %7 = add i64 %4, 1
  store i64 %7, ptr %0, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %8 = load i64, ptr %0, align 4
  %9 = icmp eq i64 %8, 3
  call void @Assert(i1 %9)
  %10 = load i64, ptr %1, align 4
  %11 = icmp eq i64 %10, 2
  call void @Assert(i1 %11)
  br label %exit

for.body1:                                        ; preds = %for.cond2
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.body
  %12 = load i64, ptr %1, align 4
  %13 = icmp slt i64 %12, 2
  br i1 %13, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %14 = load i64, ptr %1, align 4
  %15 = alloca ptr, align 8
  %16 = load i64, ptr %1, align 4
  store i64 %16, ptr %15, align 4
  %17 = add i64 %14, 1
  store i64 %17, ptr %1, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

exit:                                             ; preds = %for.end
  ret void
}

define internal void @TestForLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %2, %3
  %5 = load i64, ptr %0, align 4
  store i64 %4, ptr %0, align 4
  %6 = load i64, ptr %1, align 4
  %7 = icmp eq i64 %6, 3
  br i1 %7, label %if.then, label %if.end

for.cond:                                         ; preds = %for.iter, %entry
  %8 = load i64, ptr %1, align 4
  %9 = icmp sle i64 %8, 5
  br i1 %9, label %for.body, label %for.end

for.iter:                                         ; preds = %if.end
  %10 = load i64, ptr %1, align 4
  %11 = alloca ptr, align 8
  %12 = load i64, ptr %1, align 4
  store i64 %12, ptr %11, align 4
  %13 = add i64 %10, 1
  store i64 %13, ptr %1, align 4
  br label %for.cond

for.end:                                          ; preds = %if.then, %for.cond
  %14 = load i64, ptr %0, align 4
  %15 = icmp eq i64 %14, 6
  call void @Assert(i1 %15)
  br label %exit

if.then:                                          ; preds = %for.body
  br label %for.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %for.body
  br label %for.iter

break:                                            ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %for.end, %break, %if.else
  ret void
}

define internal void @TestForLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 3
  br i1 %3, label %if.then, label %if.end

for.cond:                                         ; preds = %for.iter, %entry
  %4 = load i64, ptr %1, align 4
  %5 = icmp sle i64 %4, 5
  br i1 %5, label %for.body, label %for.end

for.iter:                                         ; preds = %if.end, %if.then
  %6 = load i64, ptr %1, align 4
  %7 = alloca ptr, align 8
  %8 = load i64, ptr %1, align 4
  store i64 %8, ptr %7, align 4
  %9 = add i64 %6, 1
  store i64 %9, ptr %1, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %10 = load i64, ptr %0, align 4
  %11 = icmp eq i64 %10, 12
  call void @Assert(i1 %11)
  br label %exit

if.then:                                          ; preds = %for.body
  br label %for.iter

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %for.body
  %12 = load i64, ptr %0, align 4
  %13 = load i64, ptr %1, align 4
  %14 = add i64 %12, %13
  %15 = load i64, ptr %0, align 4
  store i64 %14, ptr %0, align 4
  br label %for.iter

continue:                                         ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %for.end, %continue, %if.else
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestForLoopInt()
  call void @TestForLoopBoolCondition()
  call void @TestForLoopMultipleExpressions()
  call void @TestNestedForLoops()
  call void @TestForLoopWithBreak()
  call void @TestForLoopWithContinue()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
