; ModuleID = 'test.ola'
source_filename = "test.ola"

%D = type { i64, i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal i64 @f__I(i64 %a) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %1, align 4
  ret i64 %2
}

define internal i64 @f__F(double %b) {
entry:
  %0 = alloca double, align 8
  store double %b, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 -1, ptr %1, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %1, align 4
  ret i64 %2
}

define internal i64 @f__F__F(double %a, double %b) {
entry:
  %0 = alloca double, align 8
  store double %a, ptr %0, align 8
  %1 = alloca double, align 8
  store double %b, ptr %1, align 8
  %2 = alloca i64, align 8
  store i64 -1, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %2, align 4
  ret i64 %3
}

define internal i64 @f__F__I(double %a, i64 %b) {
entry:
  %0 = alloca double, align 8
  store double %a, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %2, align 4
  ret i64 %3
}

define internal i64 @f__I__I(i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 1, ptr %2, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %2, align 4
  ret i64 %3
}

define i64 @"D::f__I"(ptr %this, i64 %a) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  %2 = getelementptr inbounds %D, ptr %this, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %1, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %1, align 4
  ret i64 %4
}

define i64 @"D::f__F"(ptr %this, double %b) {
entry:
  %0 = alloca double, align 8
  store double %b, ptr %0, align 8
  %1 = alloca i64, align 8
  %2 = getelementptr inbounds %D, ptr %this, i32 0, i32 2
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %1, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %1, align 4
  ret i64 %4
}

define i64 @"D::f__F__F"(ptr %this, double %a, double %b) {
entry:
  %0 = alloca double, align 8
  store double %a, ptr %0, align 8
  %1 = alloca double, align 8
  store double %b, ptr %1, align 8
  %2 = alloca i64, align 8
  %3 = getelementptr inbounds %D, ptr %this, i32 0, i32 2
  %4 = load ptr, ptr %3, align 8
  store ptr %4, ptr %2, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %2, align 4
  ret i64 %5
}

define i64 @"D::f__F__I"(ptr %this, double %a, i64 %b) {
entry:
  %0 = alloca double, align 8
  store double %a, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = getelementptr inbounds %D, ptr %this, i32 0, i32 1
  %4 = load ptr, ptr %3, align 8
  store ptr %4, ptr %2, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %2, align 4
  ret i64 %5
}

define i64 @"D::f__I__I"(ptr %this, i64 %a, i64 %b) {
entry:
  %0 = alloca i64, align 8
  store i64 %a, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %b, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = getelementptr inbounds %D, ptr %this, i32 0, i32 0
  %4 = load ptr, ptr %3, align 8
  store ptr %4, ptr %2, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %5 = load i64, ptr %2, align 4
  ret i64 %5
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @f__I(i64 1)
  %2 = icmp sgt i64 %1, 0
  call void @Assert(i1 %2)
  %3 = call i64 @f__F(double 1.000000e+00)
  %4 = icmp slt i64 %3, 0
  call void @Assert(i1 %4)
  %5 = call i64 @f__F__F(double 1.000000e+00, double 1.000000e+00)
  %6 = icmp slt i64 %5, 0
  call void @Assert(i1 %6)
  %7 = call i64 @f__F__I(double 1.000000e+00, i64 1)
  %8 = icmp eq i64 %7, 0
  call void @Assert(i1 %8)
  %9 = call i64 @f__I__I(i64 1, i64 1)
  %10 = icmp sgt i64 %9, 0
  call void @Assert(i1 %10)
  %11 = alloca %D, align 8
  %12 = getelementptr inbounds %D, ptr %11, i32 0, i32 0
  store i64 1, ptr %12, align 4
  %13 = getelementptr inbounds %D, ptr %11, i32 0, i32 1
  store i64 0, ptr %13, align 4
  %14 = getelementptr inbounds %D, ptr %11, i32 0, i32 2
  store i64 -1, ptr %14, align 4
  %15 = call i64 @"D::f__I"(ptr %11, i64 1)
  %16 = icmp sgt i64 %15, 0
  call void @Assert(i1 %16)
  %17 = call i64 @"D::f__F"(ptr %11, double 1.000000e+00)
  %18 = icmp slt i64 %17, 0
  call void @Assert(i1 %18)
  %19 = call i64 @"D::f__F__F"(ptr %11, double 1.000000e+00, double 1.000000e+00)
  %20 = icmp slt i64 %19, 0
  call void @Assert(i1 %20)
  %21 = call i64 @"D::f__F__I"(ptr %11, double 1.000000e+00, i64 1)
  %22 = icmp eq i64 %21, 0
  call void @Assert(i1 %22)
  %23 = call i64 @"D::f__I__I"(ptr %11, i64 1, i64 1)
  %24 = icmp sgt i64 %23, 0
  call void @Assert(i1 %24)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %25 = load i64, ptr %0, align 4
  ret i64 %25
}
