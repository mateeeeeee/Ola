; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

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

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestWhileLoopWithBreak()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
