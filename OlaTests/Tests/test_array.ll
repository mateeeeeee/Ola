; ModuleID = 'test_array.ola'
source_filename = "test_array.ola"

@GlobalArray1 = internal global [3 x i64] [i64 1, i64 1, i64 1]
@GlobalArray2 = internal global [5 x i64] [i64 1, i64 2, i64 3, i64 0, i64 0]
@GlobalArray3 = internal global [3 x i64] [i64 10, i64 20, i64 30]
@Global2dArray = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @modifyArray(ptr %arr) {
entry:
  store i64 100, ptr %arr, align 4
  ret void
}

define internal i64 @sumOfArray(ptr %arr, i64 %size) {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  %2 = icmp sgt i64 %size, 0
  br i1 %2, label %for.body.lr.ph, label %for.end

for.body.lr.ph:                                   ; preds = %entry
  %.promoted1 = load i64, ptr %1, align 8
  br label %for.body

for.body:                                         ; preds = %for.body.lr.ph, %for.body
  %3 = phi i64 [ %.promoted1, %for.body.lr.ph ], [ %7, %for.body ]
  %4 = phi i64 [ 0, %for.body.lr.ph ], [ %8, %for.body ]
  %5 = getelementptr inbounds ptr, ptr %arr, i64 %4
  %6 = load i64, ptr %5, align 4
  %7 = add i64 %6, %3
  %8 = add i64 %4, 1
  %9 = icmp slt i64 %8, %size
  br i1 %9, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  store i64 %7, ptr %1, align 8
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry
  %10 = load ptr, ptr %1, align 8
  store ptr %10, ptr %0, align 8
  %11 = load i64, ptr %0, align 8
  ret i64 %11
}

define i64 @main() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  %0 = load i64, ptr @GlobalArray3, align 16
  %1 = icmp eq i64 %0, 10
  tail call void @Assert(i1 %1)
  %2 = alloca [10 x i64], align 8
  store i64 1, ptr %2, align 8
  %3 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 1
  store i64 2, ptr %3, align 8
  %4 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 2
  store i64 0, ptr %4, align 8
  %5 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 3
  store i64 0, ptr %5, align 8
  %6 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 4
  store i64 0, ptr %6, align 8
  %7 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 5
  store i64 0, ptr %7, align 8
  %8 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 6
  store i64 0, ptr %8, align 8
  %9 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 7
  store i64 0, ptr %9, align 8
  %10 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 8
  store i64 0, ptr %10, align 8
  %11 = getelementptr inbounds [10 x i64], ptr %2, i64 0, i64 9
  store i64 0, ptr %11, align 8
  tail call void @Assert(i1 true)
  %12 = load i64, ptr %8, align 8
  %13 = icmp eq i64 %12, 0
  tail call void @Assert(i1 %13)
  %14 = call i64 @sumOfArray(ptr nonnull %2, i64 10)
  %15 = icmp eq i64 %14, 3
  call void @Assert(i1 %15)
  %16 = alloca [3 x i64], align 8
  store i64 -5, ptr %16, align 8
  %17 = getelementptr inbounds [3 x i64], ptr %16, i64 0, i64 1
  store i64 0, ptr %17, align 8
  %18 = getelementptr inbounds [3 x i64], ptr %16, i64 0, i64 2
  store i64 5, ptr %18, align 8
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @modifyArray(ptr nonnull %16)
  %19 = load i64, ptr %16, align 8
  %20 = icmp eq i64 %19, 100
  call void @Assert(i1 %20)
  %21 = load i64, ptr %16, align 8
  %22 = icmp eq i64 %21, 100
  call void @Assert(i1 %22)
  store i64 1000, ptr %16, align 8
  call void @Assert(i1 true)
  %23 = load i64, ptr %16, align 8
  %24 = icmp eq i64 %23, 1000
  call void @Assert(i1 %24)
  %25 = alloca [2 x [2 x i64]], align 8
  store i64 1, ptr %25, align 8
  %.repack22 = getelementptr inbounds [2 x i64], ptr %25, i64 0, i64 1
  store i64 2, ptr %.repack22, align 8
  %26 = getelementptr inbounds [2 x [2 x i64]], ptr %25, i64 0, i64 1
  store i64 3, ptr %26, align 8
  %.repack23 = getelementptr inbounds [2 x [2 x i64]], ptr %25, i64 0, i64 1, i64 1
  store i64 4, ptr %.repack23, align 8
  %27 = load i64, ptr getelementptr inbounds ([2 x [2 x i64]], ptr @Global2dArray, i64 0, i64 0, i64 1), align 8
  %28 = load i64, ptr @Global2dArray, align 16
  %29 = add i64 %27, %28
  %30 = getelementptr inbounds ptr, ptr %25, i64 1
  %31 = load i64, ptr %30, align 8
  %32 = load i64, ptr %25, align 8
  %33 = add i64 %31, %32
  %34 = getelementptr inbounds [2 x [2 x i64]], ptr %25, i64 0, i64 1
  %35 = load i64, ptr getelementptr inbounds ([2 x [2 x i64]], ptr @Global2dArray, i64 0, i64 1, i64 1), align 8
  %36 = load i64, ptr getelementptr inbounds ([2 x [2 x i64]], ptr @Global2dArray, i64 0, i64 1, i64 0), align 16
  %37 = add i64 %36, %29
  %38 = add i64 %35, %37
  %39 = getelementptr inbounds [2 x [2 x i64]], ptr %25, i64 0, i64 1, i64 1
  %40 = load i64, ptr %39, align 8
  %41 = load i64, ptr %34, align 8
  %42 = add i64 %41, %33
  %43 = add i64 %40, %42
  %44 = icmp eq i64 %43, 10
  call void @Assert(i1 %44)
  %45 = icmp eq i64 %38, 10
  call void @Assert(i1 %45)
  ret i64 0
}
