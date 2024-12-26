; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %0 = add i64 %.0, %.01
  %1 = alloca ptr, align 8
  store i64 %.0, ptr %1, align 4
  %2 = add i64 %.0, 1
  br label %for.cond

for.cond:                                         ; preds = %for.body, %entry
  %.01 = phi i64 [ 0, %entry ], [ %0, %for.body ]
  %.0 = phi i64 [ 1, %entry ], [ %2, %for.body ]
  %3 = icmp sle i64 %.0, 5
  br i1 %3, label %for.body, label %for.end

for.end:                                          ; preds = %for.cond
  %4 = icmp eq i64 %.01, 15
  call void @Assert(i1 %4)
  ret i64 0
}
