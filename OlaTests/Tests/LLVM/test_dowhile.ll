; ModuleID = 'test_dowhile.ola'
source_filename = "test_dowhile.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestDoWhileLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %2, %3
  %5 = load i64, ptr %0, align 4
  store i64 %4, ptr %0, align 4
  %6 = load i64, ptr %1, align 4
  %7 = alloca ptr, align 8
  %8 = load i64, ptr %1, align 4
  store i64 %8, ptr %7, align 4
  %9 = add i64 %6, 1
  store i64 %9, ptr %1, align 4
  br label %dowhile.cond

dowhile.cond:                                     ; preds = %dowhile.body
  %10 = load i64, ptr %1, align 4
  %11 = icmp sle i64 %10, 5
  br i1 %11, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 15
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %dowhile.end
  ret void
}

define internal void @TestDoWhileLoopBool() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %2 = load i64, ptr %1, align 4
  %3 = alloca ptr, align 8
  %4 = load i64, ptr %1, align 4
  store i64 %4, ptr %3, align 4
  %5 = add i64 %2, 1
  store i64 %5, ptr %1, align 4
  %6 = load i64, ptr %1, align 4
  %7 = icmp eq i64 %6, 3
  br i1 %7, label %if.then, label %if.end

dowhile.cond:                                     ; preds = %if.end
  %8 = load i1, ptr %0, align 1
  br i1 %8, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %9 = load i64, ptr %1, align 4
  %10 = icmp eq i64 %9, 3
  call void @Assert(i1 %10)
  br label %exit

if.then:                                          ; preds = %dowhile.body
  %11 = load i1, ptr %0, align 1
  store i1 false, ptr %0, align 1
  br label %if.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %if.then, %dowhile.body
  br label %dowhile.cond

exit:                                             ; preds = %dowhile.end, %if.else
  ret void
}

define internal void @TestNestedDoWhileLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  br label %dowhile.body1

dowhile.cond:                                     ; preds = %dowhile.end3
  %2 = load i64, ptr %0, align 4
  %3 = icmp slt i64 %2, 3
  br i1 %3, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %4 = load i64, ptr %0, align 4
  %5 = icmp eq i64 %4, 3
  call void @Assert(i1 %5)
  %6 = load i64, ptr %1, align 4
  %7 = icmp eq i64 %6, 4
  call void @Assert(i1 %7)
  br label %exit

dowhile.body1:                                    ; preds = %dowhile.cond2, %dowhile.body
  %8 = load i64, ptr %1, align 4
  %9 = alloca ptr, align 8
  %10 = load i64, ptr %1, align 4
  store i64 %10, ptr %9, align 4
  %11 = add i64 %8, 1
  store i64 %11, ptr %1, align 4
  br label %dowhile.cond2

dowhile.cond2:                                    ; preds = %dowhile.body1
  %12 = load i64, ptr %1, align 4
  %13 = icmp slt i64 %12, 2
  br i1 %13, label %dowhile.body1, label %dowhile.end3

dowhile.end3:                                     ; preds = %dowhile.cond2
  %14 = load i64, ptr %0, align 4
  %15 = alloca ptr, align 8
  %16 = load i64, ptr %0, align 4
  store i64 %16, ptr %15, align 4
  %17 = add i64 %14, 1
  store i64 %17, ptr %0, align 4
  br label %dowhile.cond

exit:                                             ; preds = %dowhile.end
  ret void
}

define internal void @TestDoWhileLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = add i64 %2, %3
  %5 = load i64, ptr %0, align 4
  store i64 %4, ptr %0, align 4
  %6 = load i64, ptr %1, align 4
  %7 = alloca ptr, align 8
  %8 = load i64, ptr %1, align 4
  store i64 %8, ptr %7, align 4
  %9 = add i64 %6, 1
  store i64 %9, ptr %1, align 4
  %10 = load i64, ptr %1, align 4
  %11 = icmp sgt i64 %10, 5
  br i1 %11, label %if.then, label %if.end

dowhile.cond:                                     ; preds = %if.end
  br i1 true, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond, %if.then
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 15
  call void @Assert(i1 %13)
  br label %exit

if.then:                                          ; preds = %dowhile.body
  br label %dowhile.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %dowhile.body
  br label %dowhile.cond

break:                                            ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %dowhile.end, %break, %if.else
  ret void
}

define internal void @TestDoWhileLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %2 = load i64, ptr %1, align 4
  %3 = alloca ptr, align 8
  %4 = load i64, ptr %1, align 4
  store i64 %4, ptr %3, align 4
  %5 = add i64 %2, 1
  store i64 %5, ptr %1, align 4
  %6 = load i64, ptr %1, align 4
  %7 = srem i64 %6, 2
  %8 = icmp eq i64 %7, 0
  br i1 %8, label %if.then, label %if.end

dowhile.cond:                                     ; preds = %if.end, %if.then
  %9 = load i64, ptr %1, align 4
  %10 = icmp slt i64 %9, 5
  br i1 %10, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %11 = load i64, ptr %0, align 4
  %12 = icmp eq i64 %11, 9
  call void @Assert(i1 %12)
  br label %exit

if.then:                                          ; preds = %dowhile.body
  br label %dowhile.cond

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %dowhile.body
  %13 = load i64, ptr %0, align 4
  %14 = load i64, ptr %1, align 4
  %15 = add i64 %13, %14
  %16 = load i64, ptr %0, align 4
  store i64 %15, ptr %0, align 4
  br label %dowhile.cond

continue:                                         ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %dowhile.end, %continue, %if.else
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestDoWhileLoopInt()
  call void @TestDoWhileLoopBool()
  call void @TestNestedDoWhileLoops()
  call void @TestDoWhileLoopWithBreak()
  call void @TestDoWhileLoopWithContinue()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
