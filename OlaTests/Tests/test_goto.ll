; ModuleID = 'test_goto.ola'
source_filename = "test_goto.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestGotoNestedLoops() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %for.body

label.Found:                                      ; preds = %for.body1, %for.end4
  %2 = load i64, ptr %0, align 8
  %3 = load i64, ptr %1, align 8
  %4 = mul i64 %3, %2
  %5 = icmp eq i64 %4, 5
  tail call void @Assert(i1 %5)
  ret void

for.body:                                         ; preds = %entry, %for.end4
  store i64 0, ptr %1, align 8
  %6 = load i64, ptr %0, align 8
  br label %for.body1

for.body1:                                        ; preds = %for.body, %if.end
  %7 = load i64, ptr %1, align 8
  %8 = mul i64 %7, %6
  %9 = icmp eq i64 %8, 5
  br i1 %9, label %label.Found, label %if.end

for.end4:                                         ; preds = %if.end
  %10 = load i64, ptr %0, align 8
  %11 = add i64 %10, 1
  store i64 %11, ptr %0, align 8
  %12 = icmp slt i64 %11, 10
  br i1 %12, label %for.body, label %label.Found

if.end:                                           ; preds = %for.body1
  %13 = add i64 %7, 1
  store i64 %13, ptr %1, align 8
  %14 = icmp slt i64 %13, 10
  br i1 %14, label %for.body1, label %for.end4
}

define internal i64 @TestGotoErrorHandling() {
entry:
  %0 = alloca i64, align 8
  store ptr inttoptr (i64 -1 to ptr), ptr %0, align 8
  %1 = load i64, ptr %0, align 8
  ret i64 %1
}

define internal i64 @TestGotoEndOfFunction() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  %3 = load i64, ptr %0, align 8
  ret i64 %3
}

define i64 @main() {
entry:
  tail call void @TestGotoNestedLoops()
  %0 = tail call i64 @TestGotoErrorHandling()
  %1 = icmp eq i64 %0, -1
  tail call void @Assert(i1 %1)
  %2 = tail call i64 @TestGotoEndOfFunction()
  %3 = icmp eq i64 %2, 0
  tail call void @Assert(i1 %3)
  ret i64 0
}
