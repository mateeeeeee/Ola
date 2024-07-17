; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal i64 @TestIfElse() {
entry:
  ret i64 10
}

define internal i64 @TestWhile() {
entry:
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %.04 = phi i64 [ 0, %entry ], [ %3, %if.end ]
  %0 = icmp slt i64 %.04, 10
  br i1 %0, label %while.body, label %exit

while.body:                                       ; preds = %while.cond
  %1 = icmp eq i64 %.04, 5
  br i1 %1, label %if.then, label %if.end

if.then:                                          ; preds = %while.body
  %2 = shl i64 %.04, 1
  br label %exit

if.end:                                           ; preds = %while.body
  %3 = add i64 %.04, 1
  br label %while.cond

exit:                                             ; preds = %while.cond, %if.then
  %.0 = phi i64 [ %2, %if.then ], [ 0, %while.cond ]
  ret i64 %.0
}

define i64 @main() {
entry:
  %0 = call i64 @TestIfElse()
  %1 = icmp eq i64 %0, 10
  call void @Assert(i1 %1)
  %2 = call i64 @TestWhile()
  %3 = icmp eq i64 %2, 10
  call void @Assert(i1 %3)
  ret i64 0
}
