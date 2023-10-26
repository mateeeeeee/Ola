; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %.0 = phi i64 [ 0, %entry ], [ %3, %dowhile.cond ]
  %1 = load i64, ptr %0, align 8
  %2 = add i64 %1, 1
  store i64 %2, ptr %0, align 8
  br label %dowhile.cond

dowhile.cond:                                     ; preds = %dowhile.body
  %3 = add i64 %.0, %1
  %4 = load i64, ptr %0, align 8
  %5 = icmp slt i64 %4, 5
  br i1 %5, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %6 = icmp eq i64 %3, 10
  call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 10, ptr %7, align 8
  %8 = alloca i64, align 8
  store i64 0, ptr %8, align 8
  br label %dowhile.body1

dowhile.body1:                                    ; preds = %dowhile.cond2, %dowhile.end
  %9 = load i64, ptr %8, align 8
  %10 = add i64 %9, 1
  store i64 %10, ptr %8, align 8
  br label %dowhile.cond2

dowhile.cond2:                                    ; preds = %dowhile.body1
  %11 = load i64, ptr %7, align 8
  %12 = icmp slt i64 %11, 10
  br i1 %12, label %dowhile.body1, label %dowhile.end3

dowhile.end3:                                     ; preds = %dowhile.cond2
  %13 = load i64, ptr %8, align 8
  %14 = icmp eq i64 %13, 1
  call void @Assert(i1 %14)
  %15 = alloca i64, align 8
  store i64 5, ptr %15, align 8
  %16 = alloca i64, align 8
  store i64 3, ptr %16, align 8
  %17 = alloca i64, align 8
  store i64 0, ptr %17, align 8
  br label %dowhile.body4

dowhile.body4:                                    ; preds = %dowhile.cond5, %dowhile.end3
  %18 = load i64, ptr %15, align 8
  %19 = load i64, ptr %16, align 8
  %20 = icmp sgt i64 %18, %19
  br i1 %20, label %if.then, label %if.end

dowhile.cond5:                                    ; preds = %if.end
  %21 = load i64, ptr %15, align 8
  %22 = icmp sgt i64 %21, 0
  %23 = load i64, ptr %16, align 8
  %24 = icmp slt i64 %23, 10
  %25 = and i1 %22, %24
  br i1 %25, label %dowhile.body4, label %dowhile.end6

dowhile.end6:                                     ; preds = %dowhile.cond5
  %26 = load i64, ptr %17, align 8
  %27 = icmp eq i64 %26, 5
  call void @Assert(i1 %27)
  %28 = alloca i64, align 8
  store i64 1, ptr %28, align 8
  %29 = alloca i64, align 8
  store i64 0, ptr %29, align 8
  br label %dowhile.body7

if.then:                                          ; preds = %dowhile.body4
  %30 = load i64, ptr %17, align 8
  %31 = load i64, ptr %15, align 8
  %32 = add i64 %30, %31
  store i64 %32, ptr %17, align 8
  br label %if.end

if.else:                                          ; No predecessors!
  br label %exit

if.end:                                           ; preds = %if.then, %dowhile.body4
  %33 = load i64, ptr %15, align 8
  %34 = add i64 %33, -1
  store i64 %34, ptr %15, align 8
  %35 = load i64, ptr %16, align 8
  %36 = add i64 %35, 1
  store i64 %36, ptr %16, align 8
  br label %dowhile.cond5

dowhile.body7:                                    ; preds = %dowhile.cond8, %dowhile.end6
  %37 = load i64, ptr %29, align 8
  %38 = load i64, ptr %28, align 8
  %39 = add i64 %37, %38
  store i64 %39, ptr %29, align 8
  %40 = icmp sgt i64 %39, 9
  br i1 %40, label %if.then10, label %if.end12

dowhile.cond8:                                    ; preds = %if.end12
  %41 = load i64, ptr %28, align 8
  %42 = icmp slt i64 %41, 6
  br i1 %42, label %dowhile.body7, label %dowhile.end9.loopexit

dowhile.end9.loopexit:                            ; preds = %dowhile.cond8
  br label %dowhile.end9

dowhile.end9:                                     ; preds = %dowhile.end9.loopexit, %if.then10
  %43 = load i64, ptr %29, align 8
  %44 = icmp eq i64 %43, 10
  call void @Assert(i1 %44)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

if.then10:                                        ; preds = %dowhile.body7
  br label %dowhile.end9

if.else11:                                        ; No predecessors!
  br label %exit

if.end12:                                         ; preds = %dowhile.body7
  %45 = load i64, ptr %28, align 8
  %46 = add i64 %45, 1
  store i64 %46, ptr %28, align 8
  br label %dowhile.cond8

break:                                            ; No predecessors!
  br label %exit

exit:                                             ; preds = %break, %if.else11, %return, %if.else, %dowhile.end9
  ret i64 0
}
