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
  %storemerge26 = phi i64 [ %4, %for.iter ], [ 1, %entry ]
  %.0 = phi i64 [ %3, %for.iter ], [ 0, %entry ]
  store i64 %storemerge26, ptr %0, align 8
  %1 = icmp slt i64 %storemerge26, 6
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
  store i64 0, ptr %6, align 8
  %7 = alloca i64, align 8
  br label %for.cond2

for.body1:                                        ; preds = %for.cond2
  %8 = load i64, ptr %7, align 8
  %9 = and i64 %8, 1
  %10 = icmp eq i64 %9, 0
  br i1 %10, label %if.then, label %if.end

for.cond2:                                        ; preds = %for.iter3, %for.end
  %storemerge25 = phi i64 [ %13, %for.iter3 ], [ 1, %for.end ]
  store i64 %storemerge25, ptr %7, align 8
  %11 = icmp slt i64 %storemerge25, 6
  br i1 %11, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %if.end, %if.then
  %12 = load i64, ptr %7, align 8
  %13 = add i64 %12, 1
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  %14 = load i64, ptr %6, align 8
  %15 = icmp eq i64 %14, 9
  call void @Assert(i1 %15)
  %16 = alloca i64, align 8
  store i64 0, ptr %16, align 8
  %17 = alloca i64, align 8
  br label %for.cond6

if.then:                                          ; preds = %for.body1
  br label %for.iter3

if.else:                                          ; No predecessors!
  br label %exit

if.end:                                           ; preds = %for.body1
  %18 = load i64, ptr %6, align 8
  %19 = load i64, ptr %7, align 8
  %20 = add i64 %18, %19
  store i64 %20, ptr %6, align 8
  br label %for.iter3

continue:                                         ; No predecessors!
  br label %exit

for.body5:                                        ; preds = %for.cond6
  %21 = load i64, ptr %16, align 8
  %22 = load i64, ptr %17, align 8
  %23 = add i64 %21, %22
  store i64 %23, ptr %16, align 8
  %24 = icmp eq i64 %22, 5
  br i1 %24, label %if.then9, label %if.end11

for.cond6:                                        ; preds = %for.iter7, %for.end4
  %storemerge24 = phi i64 [ %27, %for.iter7 ], [ 1, %for.end4 ]
  store i64 %storemerge24, ptr %17, align 8
  %25 = icmp slt i64 %storemerge24, 11
  br i1 %25, label %for.body5, label %for.end8.loopexit

for.iter7:                                        ; preds = %if.end11
  %26 = load i64, ptr %17, align 8
  %27 = add i64 %26, 1
  br label %for.cond6

for.end8.loopexit:                                ; preds = %for.cond6
  br label %for.end8

for.end8:                                         ; preds = %for.end8.loopexit, %if.then9
  %28 = load i64, ptr %16, align 8
  %29 = icmp eq i64 %28, 15
  call void @Assert(i1 %29)
  %30 = alloca i64, align 8
  store i64 1, ptr %30, align 8
  %31 = alloca i64, align 8
  br label %for.cond13

if.then9:                                         ; preds = %for.body5
  br label %for.end8

if.else10:                                        ; No predecessors!
  br label %exit

if.end11:                                         ; preds = %for.body5
  br label %for.iter7

break:                                            ; No predecessors!
  br label %exit

for.body12:                                       ; preds = %for.cond13
  %32 = load i64, ptr %30, align 8
  %33 = load i64, ptr %31, align 8
  %34 = mul i64 %32, %33
  store i64 %34, ptr %30, align 8
  br label %for.iter14

for.cond13:                                       ; preds = %for.iter14, %for.end8
  %storemerge = phi i64 [ %37, %for.iter14 ], [ 2, %for.end8 ]
  store i64 %storemerge, ptr %31, align 8
  %35 = icmp slt i64 %storemerge, 11
  br i1 %35, label %for.body12, label %for.end15

for.iter14:                                       ; preds = %for.body12
  %36 = load i64, ptr %31, align 8
  %37 = add i64 %36, 2
  br label %for.cond13

for.end15:                                        ; preds = %for.cond13
  %38 = load i64, ptr %30, align 8
  %39 = icmp eq i64 %38, 3840
  call void @Assert(i1 %39)
  %40 = alloca i64, align 8
  store i64 1, ptr %40, align 8
  %41 = alloca i64, align 8
  store i64 5, ptr %41, align 8
  br label %for.cond17

for.body16:                                       ; preds = %for.cond17
  %42 = load i64, ptr %40, align 8
  %43 = load i64, ptr %41, align 8
  %44 = mul i64 %42, %43
  store i64 %44, ptr %40, align 8
  %45 = add i64 %43, -1
  store i64 %45, ptr %41, align 8
  br label %for.iter18

for.cond17:                                       ; preds = %for.iter18, %for.end15
  %46 = load i64, ptr %41, align 8
  %47 = icmp sgt i64 %46, 0
  br i1 %47, label %for.body16, label %for.end19

for.iter18:                                       ; preds = %for.body16
  br label %for.cond17

for.end19:                                        ; preds = %for.cond17
  %48 = load i64, ptr %40, align 8
  %49 = icmp eq i64 %48, 120
  call void @Assert(i1 %49)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %break, %if.else10, %continue, %if.else, %for.end19
  ret i64 0
}
