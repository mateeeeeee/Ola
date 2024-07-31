; ModuleID = 'test_while.ola'
source_filename = "test_while.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestWhileLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i64, ptr %1, align 4
  %3 = icmp sle i64 %2, 5
  br i1 %3, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %4 = load i64, ptr %0, align 4
  %5 = load i64, ptr %1, align 4
  %6 = add i64 %4, %5
  %7 = load i64, ptr %0, align 4
  store i64 %6, ptr %0, align 4
  %8 = load i64, ptr %1, align 4
  %9 = alloca ptr, align 8
  %10 = load i64, ptr %1, align 4
  store i64 %10, ptr %9, align 4
  %11 = add i64 %8, 1
  store i64 %11, ptr %1, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 15
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %while.end
  ret void
}

define internal void @TestWhileLoopBool() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %2 = load i1, ptr %0, align 1
  br i1 %2, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %3 = load i64, ptr %1, align 4
  %4 = alloca ptr, align 8
  %5 = load i64, ptr %1, align 4
  store i64 %5, ptr %4, align 4
  %6 = add i64 %3, 1
  store i64 %6, ptr %1, align 4
  %7 = load i64, ptr %1, align 4
  %8 = icmp eq i64 %7, 3
  br i1 %8, label %if.then, label %if.end

while.end:                                        ; preds = %while.cond
  %9 = load i64, ptr %1, align 4
  %10 = icmp eq i64 %9, 3
  call void @Assert(i1 %10)
  br label %exit

if.then:                                          ; preds = %while.body
  %11 = load i1, ptr %0, align 1
  store i1 false, ptr %0, align 1
  br label %if.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %if.then, %while.body
  br label %while.cond

exit:                                             ; preds = %while.end, %if.else
  ret void
}

define internal void @TestNestedWhileLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.end3, %entry
  %2 = load i64, ptr %0, align 4
  %3 = icmp slt i64 %2, 3
  br i1 %3, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  br label %while.cond1

while.end:                                        ; preds = %while.cond
  %4 = load i64, ptr %0, align 4
  %5 = icmp eq i64 %4, 3
  call void @Assert(i1 %5)
  %6 = load i64, ptr %1, align 4
  %7 = icmp eq i64 %6, 2
  call void @Assert(i1 %7)
  br label %exit

while.cond1:                                      ; preds = %while.body2, %while.body
  %8 = load i64, ptr %1, align 4
  %9 = icmp slt i64 %8, 2
  br i1 %9, label %while.body2, label %while.end3

while.body2:                                      ; preds = %while.cond1
  %10 = load i64, ptr %1, align 4
  %11 = alloca ptr, align 8
  %12 = load i64, ptr %1, align 4
  store i64 %12, ptr %11, align 4
  %13 = add i64 %10, 1
  store i64 %13, ptr %1, align 4
  br label %while.cond1

while.end3:                                       ; preds = %while.cond1
  %14 = load i64, ptr %0, align 4
  %15 = alloca ptr, align 8
  %16 = load i64, ptr %0, align 4
  store i64 %16, ptr %15, align 4
  %17 = add i64 %14, 1
  store i64 %17, ptr %0, align 4
  br label %while.cond

exit:                                             ; preds = %while.end
  ret void
}

define internal void @TestWhileLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  br i1 true, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
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

while.end:                                        ; preds = %if.then, %while.cond
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 15
  call void @Assert(i1 %13)
  br label %exit

if.then:                                          ; preds = %while.body
  br label %while.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %while.body
  br label %while.cond

break:                                            ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %while.end, %break, %if.else
  ret void
}

define internal void @TestWhileLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %if.then, %entry
  %2 = load i64, ptr %1, align 4
  %3 = icmp slt i64 %2, 5
  br i1 %3, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %4 = load i64, ptr %1, align 4
  %5 = alloca ptr, align 8
  %6 = load i64, ptr %1, align 4
  store i64 %6, ptr %5, align 4
  %7 = add i64 %4, 1
  store i64 %7, ptr %1, align 4
  %8 = load i64, ptr %1, align 4
  %9 = srem i64 %8, 2
  %10 = icmp eq i64 %9, 0
  br i1 %10, label %if.then, label %if.end

while.end:                                        ; preds = %while.cond
  %11 = load i64, ptr %0, align 4
  %12 = icmp eq i64 %11, 9
  call void @Assert(i1 %12)
  br label %exit

if.then:                                          ; preds = %while.body
  br label %while.cond

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %while.body
  %13 = load i64, ptr %0, align 4
  %14 = load i64, ptr %1, align 4
  %15 = add i64 %13, %14
  %16 = load i64, ptr %0, align 4
  store i64 %15, ptr %0, align 4
  br label %while.cond

continue:                                         ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %while.end, %continue, %if.else
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestWhileLoopInt()
  call void @TestWhileLoopBool()
  call void @TestNestedWhileLoops()
  call void @TestWhileLoopWithBreak()
  call void @TestWhileLoopWithContinue()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
