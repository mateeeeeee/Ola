; ModuleID = 'test_ifelse.ola'
source_filename = "test_ifelse.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIfElseBasic() {
entry:
  %0 = alloca i64, align 8
  store i64 10, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 20, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = icmp slt i64 %2, %3
  br i1 %4, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @Assert(i1 true)
  br label %if.end

if.else:                                          ; preds = %entry
  call void @Assert(i1 false)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %if.end
  ret void
}

define internal void @TestIfElseMultipleConditions() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = icmp sgt i64 %2, %3
  br i1 %4, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @Assert(i1 false)
  br label %if.end

if.else:                                          ; preds = %entry
  %5 = load i64, ptr %0, align 4
  %6 = load i64, ptr %1, align 4
  %7 = icmp slt i64 %5, %6
  br i1 %7, label %if.then1, label %if.else2

if.end:                                           ; preds = %if.end3, %if.then
  %nop = alloca i1, align 1
  br label %exit

if.then1:                                         ; preds = %if.else
  call void @Assert(i1 false)
  br label %if.end3

if.else2:                                         ; preds = %if.else
  call void @Assert(i1 true)
  br label %if.end3

if.end3:                                          ; preds = %if.else2, %if.then1
  %nop4 = alloca i1, align 1
  br label %if.end

exit:                                             ; preds = %if.end
  ret void
}

define internal void @TestNestedIfElse() {
entry:
  %0 = alloca i64, align 8
  store i64 42, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = srem i64 %1, 2
  %3 = icmp eq i64 %2, 0
  br i1 %3, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %4 = load i64, ptr %0, align 4
  %5 = icmp sgt i64 %4, 0
  br i1 %5, label %if.then1, label %if.else2

if.else:                                          ; preds = %entry
  call void @Assert(i1 false)
  br label %if.end

if.end:                                           ; preds = %if.end3, %if.else
  %nop = alloca i1, align 1
  br label %exit

if.then1:                                         ; preds = %if.then
  call void @Assert(i1 true)
  br label %if.end3

if.else2:                                         ; preds = %if.then
  call void @Assert(i1 false)
  br label %if.end3

if.end3:                                          ; preds = %if.else2, %if.then1
  %nop4 = alloca i1, align 1
  br label %if.end

exit:                                             ; preds = %if.end
  ret void
}

define internal void @TestComplexNestedIfElse() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 5, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 5, ptr %2, align 4
  %3 = load i64, ptr %0, align 4
  %4 = icmp sgt i64 %3, 0
  br i1 %4, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %5 = load i64, ptr %1, align 4
  %6 = icmp slt i64 %5, 10
  br i1 %6, label %if.then1, label %if.else2

if.else:                                          ; preds = %entry
  %7 = load i64, ptr %1, align 4
  %8 = icmp eq i64 %7, 0
  br i1 %8, label %if.then7, label %if.else8

if.end:                                           ; preds = %if.end9, %if.end3
  %nop = alloca i1, align 1
  br label %exit

if.then1:                                         ; preds = %if.then
  %9 = load i64, ptr %2, align 4
  %10 = icmp eq i64 %9, 5
  br i1 %10, label %if.then4, label %if.else5

if.else2:                                         ; preds = %if.then
  call void @Assert(i1 false)
  br label %if.end3

if.end3:                                          ; preds = %if.end6, %if.else2
  %nop13 = alloca i1, align 1
  br label %if.end

if.then4:                                         ; preds = %if.then1
  call void @Assert(i1 true)
  br label %if.end6

if.else5:                                         ; preds = %if.then1
  call void @Assert(i1 false)
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.then4
  %nop14 = alloca i1, align 1
  br label %if.end3

if.then7:                                         ; preds = %if.else
  call void @Assert(i1 false)
  br label %if.end9

if.else8:                                         ; preds = %if.else
  %11 = load i64, ptr %2, align 4
  %12 = icmp sgt i64 %11, 0
  br i1 %12, label %if.then10, label %if.else11

if.end9:                                          ; preds = %if.end12, %if.then7
  %nop15 = alloca i1, align 1
  br label %if.end

if.then10:                                        ; preds = %if.else8
  call void @Assert(i1 false)
  br label %if.end12

if.else11:                                        ; preds = %if.else8
  call void @Assert(i1 false)
  br label %if.end12

if.end12:                                         ; preds = %if.else11, %if.then10
  %nop16 = alloca i1, align 1
  br label %if.end9

exit:                                             ; preds = %if.end
  ret void
}

define internal void @TestIfElseLogicalOperators() {
entry:
  %0 = alloca i64, align 8
  store i64 15, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = icmp sgt i64 %1, 10
  %3 = load i64, ptr %0, align 4
  %4 = icmp slt i64 %3, 20
  %5 = and i1 %2, %4
  %6 = icmp ne i1 %5, false
  br i1 %6, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @Assert(i1 true)
  br label %if.end

if.else:                                          ; preds = %entry
  call void @Assert(i1 false)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %if.end
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestIfElseBasic()
  call void @TestIfElseMultipleConditions()
  call void @TestNestedIfElse()
  call void @TestComplexNestedIfElse()
  call void @TestIfElseLogicalOperators()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
