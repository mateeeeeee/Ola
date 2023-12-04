; ModuleID = 'test_for.ola'
source_filename = "test_for.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestForLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.body
  %1 = phi i64 [ 0, %entry ], [ %3, %for.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp slt i64 %4, 6
  br i1 %5, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestForLoopBoolCondition() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.body
  %1 = load i64, ptr %0, align 8
  %2 = add i64 %1, 1
  store i64 %2, ptr %0, align 8
  %3 = icmp slt i64 %2, 3
  br i1 %3, label %for.body, label %for.end

for.end:                                          ; preds = %for.body
  %4 = load i64, ptr %0, align 8
  %5 = icmp eq i64 %4, 3
  tail call void @Assert(i1 %5)
  ret void
}

define internal void @TestForLoopMultipleExpressions() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.body
  %2 = phi i64 [ 0, %entry ], [ %6, %for.body ]
  %3 = load i64, ptr %1, align 8
  %4 = load i64, ptr %0, align 8
  %5 = add i64 %3, %4
  %6 = add i64 %5, %2
  %7 = add i64 %4, 1
  store i64 %7, ptr %0, align 8
  %8 = add i64 %3, -1
  store i64 %8, ptr %1, align 8
  %9 = icmp slt i64 %7, 4
  br i1 %9, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  %10 = icmp eq i64 %6, 18
  tail call void @Assert(i1 %10)
  ret void
}

define internal void @TestNestedForLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.end4
  %2 = load i64, ptr %1, align 8
  %3 = icmp slt i64 %2, 2
  br i1 %3, label %for.body1, label %for.end4

for.end:                                          ; preds = %for.end4
  %4 = load i64, ptr %0, align 8
  %5 = icmp eq i64 %4, 3
  tail call void @Assert(i1 %5)
  %6 = load i64, ptr %1, align 8
  %7 = icmp eq i64 %6, 2
  tail call void @Assert(i1 %7)
  ret void

for.body1:                                        ; preds = %for.body, %for.body1
  %8 = load i64, ptr %1, align 8
  %9 = add i64 %8, 1
  store i64 %9, ptr %1, align 8
  %10 = icmp slt i64 %9, 2
  br i1 %10, label %for.body1, label %for.end4

for.end4:                                         ; preds = %for.body1, %for.body
  %11 = load i64, ptr %0, align 8
  %12 = add i64 %11, 1
  store i64 %12, ptr %0, align 8
  %13 = icmp slt i64 %12, 3
  br i1 %13, label %for.body, label %for.end
}

define internal void @TestForLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %if.end
  %1 = phi i64 [ 0, %entry ], [ %3, %if.end ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = icmp eq i64 %2, 3
  br i1 %4, label %for.end, label %if.end

for.end:                                          ; preds = %for.body, %if.end
  %.1 = phi i64 [ %3, %if.end ], [ %3, %for.body ]
  %5 = icmp eq i64 %.1, 6
  tail call void @Assert(i1 %5)
  ret void

if.end:                                           ; preds = %for.body
  %6 = add i64 %2, 1
  store i64 %6, ptr %0, align 8
  %7 = icmp slt i64 %6, 6
  br i1 %7, label %for.body, label %for.end
}

define internal void @TestForLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.body
  %1 = phi i64 [ 0, %entry ], [ %5, %for.body ]
  %2 = load i64, ptr %0, align 8
  %3 = icmp eq i64 %2, 3
  %4 = add i64 %2, %1
  %5 = select i1 %3, i64 %1, i64 %4
  %6 = load i64, ptr %0, align 8
  %7 = add i64 %6, 1
  store i64 %7, ptr %0, align 8
  %8 = icmp slt i64 %7, 6
  br i1 %8, label %for.body, label %for.end

for.end:                                          ; preds = %for.body
  %9 = icmp eq i64 %5, 12
  tail call void @Assert(i1 %9)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestForLoopInt()
  tail call void @TestForLoopBoolCondition()
  tail call void @TestForLoopMultipleExpressions()
  tail call void @TestNestedForLoops()
  tail call void @TestForLoopWithBreak()
  tail call void @TestForLoopWithContinue()
  ret i64 0
}
