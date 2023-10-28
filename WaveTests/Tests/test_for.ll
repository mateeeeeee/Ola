; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %for.body

for.body:                                         ; preds = %entry, %for.body
  %1 = phi i64 [ 0, %entry ], [ %3, %for.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp slt i64 %4, 6
  br i1 %5, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 0, ptr %7, align 8
  %8 = alloca i64, align 8
  store i64 1, ptr %8, align 8
  %.promoted31 = load i64, ptr %7, align 8
  br label %for.body1

for.body1:                                        ; preds = %for.cond.for.end_crit_edge, %for.body1
  %9 = phi i64 [ %.promoted31, %for.cond.for.end_crit_edge ], [ %14, %for.body1 ]
  %10 = load i64, ptr %8, align 8
  %11 = and i64 %10, 1
  %12 = icmp eq i64 %11, 0
  %13 = add i64 %10, %9
  %14 = select i1 %12, i64 %9, i64 %13
  %15 = load i64, ptr %8, align 8
  %16 = add i64 %15, 1
  store i64 %16, ptr %8, align 8
  %17 = icmp slt i64 %16, 6
  br i1 %17, label %for.body1, label %for.cond2.for.end4_crit_edge

for.cond2.for.end4_crit_edge:                     ; preds = %for.body1
  store i64 %14, ptr %7, align 8
  %18 = load i64, ptr %7, align 8
  %19 = icmp eq i64 %18, 9
  tail call void @Assert(i1 %19)
  %20 = alloca i64, align 8
  store i64 0, ptr %20, align 8
  %21 = alloca i64, align 8
  store i64 1, ptr %21, align 8
  %.promoted28 = load i64, ptr %20, align 8
  br label %for.body5

for.body5:                                        ; preds = %for.cond2.for.end4_crit_edge, %if.end11
  %22 = phi i64 [ %.promoted28, %for.cond2.for.end4_crit_edge ], [ %24, %if.end11 ]
  %23 = load i64, ptr %21, align 8
  %24 = add i64 %23, %22
  %25 = icmp eq i64 %23, 5
  br i1 %25, label %if.then9, label %if.end11

for.cond6.for.end8.loopexit_crit_edge:            ; preds = %if.end11
  store i64 %24, ptr %20, align 8
  br label %for.end8

for.end8:                                         ; preds = %for.cond6.for.end8.loopexit_crit_edge, %if.then9
  %26 = load i64, ptr %20, align 8
  %27 = icmp eq i64 %26, 15
  tail call void @Assert(i1 %27)
  %28 = alloca i64, align 8
  store i64 1, ptr %28, align 8
  %.promoted24 = load i64, ptr %28, align 8
  %29 = mul i64 %.promoted24, 3840
  store i64 %29, ptr %28, align 8
  %30 = load i64, ptr %28, align 8
  %31 = icmp eq i64 %30, 3840
  tail call void @Assert(i1 %31)
  %32 = alloca i64, align 8
  store i64 1, ptr %32, align 8
  %33 = alloca i64, align 8
  store i64 5, ptr %33, align 8
  %.promoted = load i64, ptr %32, align 8
  br label %for.body16

if.then9:                                         ; preds = %for.body5
  store i64 %24, ptr %20, align 8
  br label %for.end8

if.end11:                                         ; preds = %for.body5
  %34 = add i64 %23, 1
  store i64 %34, ptr %21, align 8
  %35 = icmp slt i64 %34, 11
  br i1 %35, label %for.body5, label %for.cond6.for.end8.loopexit_crit_edge

for.body16:                                       ; preds = %for.end8, %for.body16
  %36 = phi i64 [ %.promoted, %for.end8 ], [ %39, %for.body16 ]
  %37 = load i64, ptr %33, align 8
  %38 = add i64 %37, -1
  store i64 %38, ptr %33, align 8
  %39 = mul i64 %37, %36
  %40 = icmp sgt i64 %38, 0
  br i1 %40, label %for.body16, label %for.cond17.for.end19_crit_edge

for.cond17.for.end19_crit_edge:                   ; preds = %for.body16
  store i64 %39, ptr %32, align 8
  %41 = load i64, ptr %32, align 8
  %42 = icmp eq i64 %41, 120
  tail call void @Assert(i1 %42)
  ret i64 0
}
