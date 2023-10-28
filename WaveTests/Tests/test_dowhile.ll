; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.body, %entry
  %1 = phi i64 [ %4, %dowhile.body ], [ 0, %entry ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, 1
  store i64 %3, ptr %0, align 8
  %4 = add i64 %2, %1
  %5 = icmp slt i64 %3, 5
  br i1 %5, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.body
  %6 = icmp eq i64 %4, 10
  tail call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 0, ptr %7, align 8
  %8 = load i64, ptr %7, align 8
  %9 = add i64 %8, 1
  store i64 %9, ptr %7, align 8
  %10 = icmp eq i64 %8, 0
  tail call void @Assert(i1 %10)
  %11 = alloca i64, align 8
  store i64 5, ptr %11, align 8
  %12 = alloca i64, align 8
  store i64 3, ptr %12, align 8
  br label %dowhile.body4

dowhile.body4:                                    ; preds = %dowhile.body4, %dowhile.end
  %13 = phi i64 [ %spec.select, %dowhile.body4 ], [ 0, %dowhile.end ]
  %14 = load i64, ptr %11, align 8
  %15 = load i64, ptr %12, align 8
  %16 = icmp sgt i64 %14, %15
  %17 = add i64 %14, %13
  %spec.select = select i1 %16, i64 %17, i64 %13
  %18 = load i64, ptr %11, align 8
  %19 = add i64 %18, -1
  store i64 %19, ptr %11, align 8
  %20 = load i64, ptr %12, align 8
  %21 = add i64 %20, 1
  store i64 %21, ptr %12, align 8
  %22 = load i64, ptr %11, align 8
  %23 = icmp sgt i64 %22, 0
  %24 = icmp slt i64 %21, 10
  %25 = and i1 %23, %24
  br i1 %25, label %dowhile.body4, label %dowhile.end6

dowhile.end6:                                     ; preds = %dowhile.body4
  %26 = icmp eq i64 %spec.select, 5
  tail call void @Assert(i1 %26)
  %27 = alloca i64, align 8
  store i64 1, ptr %27, align 8
  br label %dowhile.body7

dowhile.body7:                                    ; preds = %if.end12, %dowhile.end6
  %28 = phi i64 [ %30, %if.end12 ], [ 0, %dowhile.end6 ]
  %29 = load i64, ptr %27, align 8
  %30 = add i64 %29, %28
  %31 = icmp sgt i64 %30, 9
  br i1 %31, label %dowhile.end9, label %if.end12

dowhile.end9:                                     ; preds = %dowhile.body7, %if.end12
  %32 = icmp eq i64 %30, 10
  tail call void @Assert(i1 %32)
  ret i64 0

if.end12:                                         ; preds = %dowhile.body7
  %33 = add i64 %29, 1
  store i64 %33, ptr %27, align 8
  %34 = icmp slt i64 %33, 6
  br i1 %34, label %dowhile.body7, label %dowhile.end9
}
