; ModuleID = 'test_goto.ola'
source_filename = "test_goto.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestGotoNestedLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  %2 = alloca i64, align 8
  %3 = load i64, ptr %1, align 4
  store i64 0, ptr %1, align 4
  br label %for.cond

label.Found:                                      ; preds = %for.end, %if.then
  %4 = load i64, ptr %1, align 4
  %5 = load i64, ptr %2, align 4
  %6 = mul i64 %4, %5
  %7 = load i64, ptr %0, align 4
  %8 = icmp eq i64 %6, %7
  call void @Assert(i1 %8)
  br label %exit

for.body:                                         ; preds = %for.cond
  %9 = load i64, ptr %2, align 4
  store i64 0, ptr %2, align 4
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %10 = load i64, ptr %1, align 4
  %11 = icmp slt i64 %10, 10
  br i1 %11, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %12 = load i64, ptr %1, align 4
  %13 = alloca ptr, align 8
  %14 = load i64, ptr %1, align 4
  store i64 %14, ptr %13, align 4
  %15 = add i64 %12, 1
  store i64 %15, ptr %1, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %label.Found

for.body1:                                        ; preds = %for.cond2
  %16 = load i64, ptr %1, align 4
  %17 = load i64, ptr %2, align 4
  %18 = mul i64 %16, %17
  %19 = load i64, ptr %0, align 4
  %20 = icmp eq i64 %18, %19
  br i1 %20, label %if.then, label %if.end

for.cond2:                                        ; preds = %for.iter3, %for.body
  %21 = load i64, ptr %2, align 4
  %22 = icmp slt i64 %21, 10
  br i1 %22, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %if.end
  %23 = load i64, ptr %2, align 4
  %24 = alloca ptr, align 8
  %25 = load i64, ptr %2, align 4
  store i64 %25, ptr %24, align 4
  %26 = add i64 %23, 1
  store i64 %26, ptr %2, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

if.then:                                          ; preds = %for.body1
  br label %label.Found

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %for.body1
  br label %for.iter3

goto:                                             ; No predecessors!
  %nop5 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %label.Found, %goto, %if.else
  ret void
}

define internal i64 @TestGotoErrorHandling() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 1, ptr %2, align 4
  %3 = load i64, ptr %2, align 4
  %4 = icmp ne i64 %3, 0
  br i1 %4, label %if.then, label %if.end

label.HandleError:                                ; preds = %return, %if.then
  %5 = load i64, ptr %1, align 4
  store i64 -1, ptr %1, align 4
  %6 = load i64, ptr %1, align 4
  store i64 %6, ptr %0, align 4
  br label %exit

return1:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.then:                                          ; preds = %entry
  br label %label.HandleError

if.else:                                          ; No predecessors!
  %nop2 = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %entry
  %7 = load i64, ptr %1, align 4
  store i64 42, ptr %1, align 4
  %8 = load i64, ptr %1, align 4
  store i64 %8, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  br label %label.HandleError

goto:                                             ; No predecessors!
  %nop3 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %goto, %if.else, %return1, %label.HandleError, %if.end
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}

define internal i64 @TestGotoEndOfFunction() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp ne i64 %2, 0
  br i1 %3, label %if.then, label %if.end

label.CleanUpAndReturn:                           ; preds = %if.end, %if.then
  %4 = load i64, ptr %1, align 4
  store i64 %4, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.then:                                          ; preds = %entry
  br label %label.CleanUpAndReturn

if.else:                                          ; No predecessors!
  %nop1 = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %entry
  br label %label.CleanUpAndReturn

goto:                                             ; No predecessors!
  %nop2 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %goto, %if.else, %return, %label.CleanUpAndReturn
  %5 = load i64, ptr %0, align 4
  ret i64 %5
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestGotoNestedLoops()
  %1 = call i64 @TestGotoErrorHandling()
  %2 = alloca i64, align 8
  store i64 %1, ptr %2, align 4
  %3 = load i64, ptr %2, align 4
  %4 = icmp eq i64 %3, -1
  call void @Assert(i1 %4)
  %5 = call i64 @TestGotoEndOfFunction()
  %6 = alloca i64, align 8
  store i64 %5, ptr %6, align 4
  %7 = load i64, ptr %6, align 4
  %8 = icmp eq i64 %7, 0
  call void @Assert(i1 %8)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}
