; ModuleID = 'test_dowhile.ola'
source_filename = "test_dowhile.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestDoWhileLoopInt() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.body, %entry
  %1 = phi i64 [ %4, %dowhile.body ], [ 0, %entry ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = add i64 %2, %1
  %5 = icmp slt i64 %3, 6
  br i1 %5, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.body
  %6 = icmp eq i64 %4, 15
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestDoWhileLoopBool() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.body, %entry
  %1 = phi i1 [ %spec.select, %dowhile.body ], [ true, %entry ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = icmp eq i64 %3, 3
  %spec.select = select i1 %4, i1 false, i1 %1
  br i1 %spec.select, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.body
  %5 = load i64, ptr %0, align 8
  %6 = icmp eq i64 %5, 3
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestNestedDoWhileLoops() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.end3, %entry
  br label %dowhile.body1

dowhile.end:                                      ; preds = %dowhile.end3
  %2 = icmp eq i64 %9, 3
  tail call void @Assert(i1 %2)
  %3 = load i64, ptr %1, align 8
  %4 = icmp eq i64 %3, 4
  tail call void @Assert(i1 %4)
  ret void

dowhile.body1:                                    ; preds = %dowhile.body1, %dowhile.body
  %5 = load i64, ptr %1, align 8
  %6 = add i64 %5, 1
  store i64 %6, ptr %1, align 8
  %7 = icmp slt i64 %6, 2
  br i1 %7, label %dowhile.body1, label %dowhile.end3

dowhile.end3:                                     ; preds = %dowhile.body1
  %8 = load i64, ptr %0, align 8
  %9 = add i64 %8, 1
  store i64 %9, ptr %0, align 8
  %10 = icmp slt i64 %9, 3
  br i1 %10, label %dowhile.body, label %dowhile.end
}

define internal void @TestDoWhileLoopWithBreak() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.body, %entry
  %1 = phi i64 [ 0, %entry ], [ %3, %dowhile.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp sgt i64 %4, 5
  br i1 %5, label %if.then, label %dowhile.body

if.then:                                          ; preds = %dowhile.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  ret void
}

define internal void @TestDoWhileLoopWithContinue() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.body, %entry
  %1 = phi i64 [ %7, %dowhile.body ], [ 0, %entry ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = and i64 %3, 1
  %5 = icmp eq i64 %4, 0
  %6 = add i64 %3, %1
  %7 = select i1 %5, i64 %1, i64 %6
  %8 = load i64, ptr %0, align 8
  %9 = icmp slt i64 %8, 5
  br i1 %9, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.body
  %10 = icmp eq i64 %7, 9
  tail call void @Assert(i1 %10)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestDoWhileLoopInt()
  tail call void @TestDoWhileLoopBool()
  tail call void @TestNestedDoWhileLoops()
  tail call void @TestDoWhileLoopWithBreak()
  tail call void @TestDoWhileLoopWithContinue()
  ret i64 0
}
