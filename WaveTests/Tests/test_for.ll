; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  br label %for.cond

for.body:                                         ; preds = %for.cond
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %storemerge9 = phi i64 [ %4, %for.iter ], [ 1, %entry ]
  %.0 = phi i64 [ %3, %for.iter ], [ 0, %entry ]
  store i64 %storemerge9, ptr %0, align 8
  %1 = icmp slt i64 %storemerge9, 6
  br i1 %1, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %.0, %2
  %4 = add i64 %2, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %5 = icmp eq i64 %.0, 15
  call void @Assert(i1 %5)
  %6 = alloca i64, align 8
  store i64 1, ptr %6, align 8
  %7 = alloca i64, align 8
  br label %for.cond2

for.body1:                                        ; preds = %for.cond2
  %8 = load i64, ptr %6, align 8
  %9 = load i64, ptr %7, align 8
  %10 = mul i64 %8, %9
  store i64 %10, ptr %6, align 8
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.end
  %storemerge = phi i64 [ %13, %for.iter3 ], [ 2, %for.end ]
  store i64 %storemerge, ptr %7, align 8
  %11 = icmp slt i64 %storemerge, 11
  br i1 %11, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %12 = load i64, ptr %7, align 8
  %13 = add i64 %12, 2
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  %14 = load i64, ptr %6, align 8
  %15 = icmp eq i64 %14, 3840
  call void @Assert(i1 %15)
  %16 = alloca i64, align 8
  store i64 1, ptr %16, align 8
  %17 = alloca i64, align 8
  store i64 5, ptr %17, align 8
  br label %for.cond6

for.body5:                                        ; preds = %for.cond6
  %18 = load i64, ptr %16, align 8
  %19 = load i64, ptr %17, align 8
  %20 = mul i64 %18, %19
  store i64 %20, ptr %16, align 8
  %21 = add i64 %19, -1
  store i64 %21, ptr %17, align 8
  br label %for.iter7

for.cond6:                                        ; preds = %for.iter7, %for.end4
  %22 = load i64, ptr %17, align 8
  %23 = icmp sgt i64 %22, 0
  br i1 %23, label %for.body5, label %for.end8

for.iter7:                                        ; preds = %for.body5
  br label %for.cond6

for.end8:                                         ; preds = %for.cond6
  %24 = load i64, ptr %16, align 8
  %25 = icmp eq i64 %24, 120
  call void @Assert(i1 %25)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %for.end8
  ret i64 0
}
