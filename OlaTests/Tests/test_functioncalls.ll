; ModuleID = 'test_functioncalls.ola'
source_filename = "test_functioncalls.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal i64 @Add(i64 %a, i64 %b) {
entry:
  %0 = add i64 %b, %a
  ret i64 %0
}

define internal double @Multiply(double %x, double %y) {
entry:
  %0 = fmul double %x, %y
  ret double %0
}

define internal i1 @LogicalAnd(i1 %p, i1 %q) {
entry:
  %0 = and i1 %p, %q
  ret i1 %0
}

define internal double @MixParams(i64 %a, double %b, i1 %c, ptr %arr, i64 %size) {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  %1 = icmp sgt i64 %size, 0
  br i1 %1, label %for.body, label %exit

for.body:                                         ; preds = %entry, %for.body
  %2 = phi i64 [ %6, %for.body ], [ 0, %entry ]
  %3 = load i64, ptr %0, align 8
  %4 = getelementptr inbounds ptr, ptr %arr, i64 %3
  %5 = load i64, ptr %4, align 4
  %6 = add i64 %5, %2
  %7 = add i64 %3, 1
  store i64 %7, ptr %0, align 8
  %8 = icmp slt i64 %7, %size
  br i1 %8, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  %9 = sitofp i64 %6 to double
  br label %exit

exit:                                             ; preds = %entry, %for.cond.for.end_crit_edge
  %.0 = phi double [ %9, %for.cond.for.end_crit_edge ], [ 0.000000e+00, %entry ]
  %10 = sitofp i64 %a to double
  %11 = fadd double %10, %b
  %12 = select i1 %c, double 1.000000e+00, double 0.000000e+00
  %13 = fadd double %11, %12
  %14 = fadd double %13, %.0
  ret double %14
}

define internal void @ConcatArrays(ptr %arr1, i64 %size1, ptr %arr2, i64 %size2, ptr %result) {
entry:
  %0 = alloca i64, align 8
  store i64 0, ptr %0, align 8
  %1 = icmp sgt i64 %size1, 0
  br i1 %1, label %for.body, label %for.end

for.body:                                         ; preds = %entry, %for.body
  %2 = load i64, ptr %0, align 8
  %3 = getelementptr inbounds ptr, ptr %result, i64 %2
  %4 = getelementptr inbounds ptr, ptr %arr1, i64 %2
  %5 = load ptr, ptr %4, align 8
  store ptr %5, ptr %3, align 8
  %6 = load i64, ptr %0, align 8
  %7 = add i64 %6, 1
  store i64 %7, ptr %0, align 8
  %8 = icmp slt i64 %7, %size1
  br i1 %8, label %for.body, label %for.end

for.end:                                          ; preds = %for.body, %entry
  %9 = alloca i64, align 8
  store i64 0, ptr %9, align 8
  %10 = icmp sgt i64 %size2, 0
  br i1 %10, label %for.body1, label %exit

for.body1:                                        ; preds = %for.end, %for.body1
  %11 = load i64, ptr %9, align 8
  %12 = add i64 %11, %size1
  %13 = getelementptr inbounds ptr, ptr %result, i64 %12
  %14 = getelementptr inbounds ptr, ptr %arr2, i64 %11
  %15 = load ptr, ptr %14, align 8
  store ptr %15, ptr %13, align 8
  %16 = load i64, ptr %9, align 8
  %17 = add i64 %16, 1
  store i64 %17, ptr %9, align 8
  %18 = icmp slt i64 %17, %size2
  br i1 %18, label %for.body1, label %exit

exit:                                             ; preds = %for.end, %for.body1
  ret void
}

define i64 @main() {
entry:
  %0 = tail call i64 @Add(i64 3, i64 5)
  %1 = icmp eq i64 %0, 8
  tail call void @Assert(i1 %1)
  %2 = tail call double @Multiply(double 2.500000e+00, double 3.000000e+00)
  %3 = fcmp oeq double %2, 7.500000e+00
  tail call void @Assert(i1 %3)
  %4 = tail call i1 @LogicalAnd(i1 true, i1 false)
  %5 = xor i1 %4, true
  tail call void @Assert(i1 %5)
  %6 = alloca [2 x i64], align 8
  store i64 10, ptr %6, align 8
  %7 = getelementptr inbounds [2 x i64], ptr %6, i64 0, i64 1
  store i64 20, ptr %7, align 8
  %8 = call double @MixParams(i64 1, double 2.500000e+00, i1 true, ptr nonnull %6, i64 2)
  %9 = fcmp oeq double %8, 3.450000e+01
  call void @Assert(i1 %9)
  %10 = alloca [2 x i64], align 8
  store i64 1, ptr %10, align 8
  %11 = getelementptr inbounds [2 x i64], ptr %10, i64 0, i64 1
  store i64 2, ptr %11, align 8
  %12 = alloca [2 x i64], align 8
  store i64 3, ptr %12, align 8
  %13 = getelementptr inbounds [2 x i64], ptr %12, i64 0, i64 1
  store i64 4, ptr %13, align 8
  %14 = alloca [4 x i64], align 8
  store i64 0, ptr %14, align 8
  %15 = getelementptr inbounds [4 x i64], ptr %14, i64 0, i64 1
  store i64 0, ptr %15, align 8
  %16 = getelementptr inbounds [4 x i64], ptr %14, i64 0, i64 2
  store i64 0, ptr %16, align 8
  %17 = getelementptr inbounds [4 x i64], ptr %14, i64 0, i64 3
  store i64 0, ptr %17, align 8
  call void @ConcatArrays(ptr nonnull %10, i64 2, ptr nonnull %12, i64 2, ptr nonnull %14)
  %18 = load i64, ptr %14, align 8
  %19 = icmp eq i64 %18, 1
  call void @Assert(i1 %19)
  %20 = load i64, ptr %15, align 8
  %21 = icmp eq i64 %20, 2
  call void @Assert(i1 %21)
  %22 = load i64, ptr %16, align 8
  %23 = icmp eq i64 %22, 3
  call void @Assert(i1 %23)
  %24 = load i64, ptr %17, align 8
  %25 = icmp eq i64 %24, 4
  call void @Assert(i1 %25)
  ret i64 0
}
