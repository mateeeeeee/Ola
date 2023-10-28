; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %while.body

while.body:                                       ; preds = %entry, %while.body
  %1 = phi i64 [ 0, %entry ], [ %3, %while.body ]
  %2 = load i64, ptr %0, align 8
  %3 = add i64 %2, %1
  %4 = add i64 %2, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp slt i64 %4, 6
  br i1 %5, label %while.body, label %while.cond.while.end_crit_edge

while.cond.while.end_crit_edge:                   ; preds = %while.body
  %6 = icmp eq i64 %3, 15
  tail call void @Assert(i1 %6)
  %7 = alloca i64, align 8
  store i64 0, ptr %7, align 8
  %8 = load i64, ptr %7, align 8
  %9 = icmp eq i64 %8, 0
  tail call void @Assert(i1 %9)
  %10 = alloca i64, align 8
  store i64 5, ptr %10, align 8
  %11 = alloca i64, align 8
  store i64 0, ptr %11, align 8
  br label %while.body5

while.body5:                                      ; preds = %while.body5, %while.cond.while.end_crit_edge
  %12 = load i64, ptr %11, align 8
  %13 = add i64 %12, 1
  store i64 %13, ptr %11, align 8
  %14 = icmp eq i64 %13, 5
  br i1 %14, label %if.then, label %while.body5

if.then:                                          ; preds = %while.body5
  %15 = load i64, ptr %11, align 8
  %16 = load i64, ptr %10, align 8
  %17 = icmp eq i64 %15, %16
  tail call void @Assert(i1 %17)
  %18 = alloca i64, align 8
  store i64 0, ptr %18, align 8
  %19 = alloca i64, align 8
  store i64 0, ptr %19, align 8
  %.promoted = load i64, ptr %18, align 8
  br label %while.body8

while.body8:                                      ; preds = %if.then, %while.body8
  %20 = phi i64 [ %.promoted, %if.then ], [ %26, %while.body8 ]
  %21 = load i64, ptr %19, align 8
  %22 = add i64 %21, 1
  store i64 %22, ptr %19, align 8
  %23 = and i64 %22, 1
  %24 = icmp eq i64 %23, 0
  %25 = add i64 %22, %20
  %26 = select i1 %24, i64 %20, i64 %25
  %27 = load i64, ptr %19, align 8
  %28 = icmp slt i64 %27, 5
  br i1 %28, label %while.body8, label %while.cond7.while.end9_crit_edge

while.cond7.while.end9_crit_edge:                 ; preds = %while.body8
  store i64 %26, ptr %18, align 8
  %29 = load i64, ptr %18, align 8
  %30 = icmp eq i64 %29, 9
  tail call void @Assert(i1 %30)
  ret i64 0
}
