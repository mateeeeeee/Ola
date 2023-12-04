; ModuleID = 'test_while.ola'
source_filename = "test_while.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestWhileLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %while.body

while.body:                                       ; preds = %entry, %while.body
  %1 = phi i64 [ 0, %entry ], [ %3, %while.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp slt i64 %4, 6
  br i1 %5, label %while.body, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestWhileLoopBool() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %while.body

while.body:                                       ; preds = %entry, %while.body
  %1 = phi i1 [ true, %entry ], [ %spec.select, %while.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = icmp eq i64 %3, 3
  %spec.select = select i1 %4, i1 false, i1 %1
  br i1 %spec.select, label %while.body, label %while.end

while.end:                                        ; preds = %while.body
  %5 = load i64, ptr %0, align 8
  %6 = icmp eq i64 %5, 3
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestNestedWhileLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  br label %while.body

while.body:                                       ; preds = %entry, %while.end3
  %2 = load i64, ptr %1, align 8
  %3 = icmp slt i64 %2, 2
  br i1 %3, label %while.body2, label %while.end3

while.end:                                        ; preds = %while.end3
  %4 = load i64, ptr %0, align 8
  %5 = icmp eq i64 %4, 3
  tail call void @Assert(i1 %5)
  %6 = load i64, ptr %1, align 8
  %7 = icmp eq i64 %6, 2
  tail call void @Assert(i1 %7)
  ret void

while.body2:                                      ; preds = %while.body, %while.body2
  %8 = load i64, ptr %1, align 8
  %9 = add i64 %8, 1
  store i64 %9, ptr %1, align 8
  %10 = icmp slt i64 %9, 2
  br i1 %10, label %while.body2, label %while.end3

while.end3:                                       ; preds = %while.body2, %while.body
  %11 = load i64, ptr %0, align 8
  %12 = add i64 %11, 1
  store i64 %12, ptr %0, align 8
  %13 = icmp slt i64 %12, 3
  br i1 %13, label %while.body, label %while.end
}

define internal void @TestWhileLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %while.body

while.body:                                       ; preds = %while.body, %entry
  %1 = phi i64 [ 0, %entry ], [ %3, %while.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp sgt i64 %4, 5
  br i1 %5, label %if.then, label %while.body

if.then:                                          ; preds = %while.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestWhileLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %while.body

while.body:                                       ; preds = %entry, %while.body
  %1 = phi i64 [ 0, %entry ], [ %7, %while.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = and i64 %3, 1
  %5 = icmp eq i64 %4, 0
  %6 = add i64 %3, %1
  %7 = select i1 %5, i64 %1, i64 %6
  %8 = load i64, ptr %0, align 8
  %9 = icmp slt i64 %8, 5
  br i1 %9, label %while.body, label %while.end

while.end:                                        ; preds = %while.body
  %10 = icmp eq i64 %7, 9
  tail call void @Assert(i1 %10)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestWhileLoopInt()
  tail call void @TestWhileLoopBool()
  tail call void @TestNestedWhileLoops()
  tail call void @TestWhileLoopWithBreak()
  tail call void @TestWhileLoopWithContinue()
  ret i64 0
}
