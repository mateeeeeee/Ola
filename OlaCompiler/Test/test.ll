; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalArray1 = internal global [3 x i64] [i64 1, i64 1, i64 1]
@GlobalArray2 = internal global [5 x i64] [i64 1, i64 2, i64 3, i64 0, i64 0]
@GlobalArray3 = internal global [3 x i64] [i64 10, i64 20, i64 30]
@Global2dArray = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @modifyArray__I0(ptr %arr) {
entry:
  %0 = alloca ptr, align 8
  store ptr %arr, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds ptr, ptr %1, i64 0
  %3 = load i64, ptr %2, align 4
  store i64 100, ptr %2, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @modifyArrayCopy__I3(ptr %arr) {
entry:
  %0 = alloca ptr, align 8
  store ptr %arr, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds ptr, ptr %1, i64 0
  %3 = load i64, ptr %2, align 4
  store i64 100, ptr %2, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal i64 @sumOfArray__I0__I(ptr %arr, i64 %size) {
entry:
  %0 = alloca ptr, align 8
  store ptr %arr, ptr %0, align 8
  %1 = alloca i64, align 8
  store i64 %size, ptr %1, align 4
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  store i64 0, ptr %3, align 4
  %4 = alloca i64, align 8
  store i64 0, ptr %4, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %5 = load i64, ptr %4, align 4
  %6 = load ptr, ptr %0, align 8
  %7 = getelementptr inbounds ptr, ptr %6, i64 %5
  %8 = load i64, ptr %3, align 4
  %9 = load i64, ptr %7, align 4
  %10 = add i64 %8, %9
  %11 = load i64, ptr %3, align 4
  store i64 %10, ptr %3, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %12 = load i64, ptr %4, align 4
  %13 = load i64, ptr %1, align 4
  %14 = icmp slt i64 %12, %13
  br i1 %14, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %15 = load i64, ptr %4, align 4
  %16 = add i64 %15, 1
  store i64 %16, ptr %4, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %17 = load ptr, ptr %3, align 8
  store ptr %17, ptr %2, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %for.end
  %18 = load i64, ptr %2, align 4
  ret i64 %18
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  %1 = load i64, ptr @GlobalArray3, align 4
  %2 = icmp eq i64 %1, 10
  call void @Assert(i1 %2)
  %3 = alloca [10 x i64], align 8
  %4 = getelementptr [10 x i64], ptr %3, i64 0, i64 0
  store i64 1, ptr %4, align 4
  %5 = getelementptr [10 x i64], ptr %3, i64 0, i64 1
  store i64 2, ptr %5, align 4
  %6 = getelementptr [10 x i64], ptr %3, i64 0, i64 2
  store i64 0, ptr %6, align 4
  %7 = getelementptr [10 x i64], ptr %3, i64 0, i64 3
  store i64 0, ptr %7, align 4
  %8 = getelementptr [10 x i64], ptr %3, i64 0, i64 4
  store i64 0, ptr %8, align 4
  %9 = getelementptr [10 x i64], ptr %3, i64 0, i64 5
  store i64 0, ptr %9, align 4
  %10 = getelementptr [10 x i64], ptr %3, i64 0, i64 6
  store i64 0, ptr %10, align 4
  %11 = getelementptr [10 x i64], ptr %3, i64 0, i64 7
  store i64 0, ptr %11, align 4
  %12 = getelementptr [10 x i64], ptr %3, i64 0, i64 8
  store i64 0, ptr %12, align 4
  %13 = getelementptr [10 x i64], ptr %3, i64 0, i64 9
  store i64 0, ptr %13, align 4
  call void @Assert(i1 true)
  %14 = getelementptr [10 x i64], ptr %3, i64 0, i64 6
  %15 = load i64, ptr %14, align 4
  %16 = icmp eq i64 %15, 0
  call void @Assert(i1 %16)
  %17 = call i64 @sumOfArray__I0__I(ptr %3, i64 10)
  %18 = icmp eq i64 %17, 3
  call void @Assert(i1 %18)
  %19 = alloca [3 x i64], align 8
  %20 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  store i64 -5, ptr %20, align 4
  %21 = getelementptr [3 x i64], ptr %19, i64 0, i64 1
  store i64 0, ptr %21, align 4
  %22 = getelementptr [3 x i64], ptr %19, i64 0, i64 2
  store i64 5, ptr %22, align 4
  %23 = getelementptr [3 x i64], ptr %19, i64 0, i64 1
  %24 = load i64, ptr %23, align 4
  %25 = icmp eq i64 %24, 0
  call void @Assert(i1 %25)
  call void @Assert(i1 true)
  %26 = alloca ptr, align 8
  %27 = getelementptr inbounds [3 x i64], ptr %19, i64 0, i64 0
  store ptr %27, ptr %26, align 8
  call void @modifyArrayCopy__I3(ptr %19)
  %28 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %29 = load i64, ptr %28, align 4
  %30 = icmp eq i64 %29, -5
  call void @Assert(i1 %30)
  %31 = load ptr, ptr %26, align 8
  %32 = getelementptr inbounds ptr, ptr %31, i64 0
  %33 = load i64, ptr %32, align 4
  %34 = icmp eq i64 %33, -5
  call void @Assert(i1 %34)
  call void @modifyArray__I0(ptr %19)
  %35 = load ptr, ptr %26, align 8
  %36 = getelementptr inbounds ptr, ptr %35, i64 0
  %37 = load i64, ptr %36, align 4
  store i64 1000, ptr %36, align 4
  %38 = alloca i64, align 8
  store i64 0, ptr %38, align 4
  %39 = alloca i64, align 8
  store i64 0, ptr %39, align 4
  %40 = alloca [2 x [2 x i64]], align 8
  %41 = getelementptr [2 x [2 x i64]], ptr %40, i64 0, i64 0
  store [2 x i64] [i64 1, i64 2], ptr %41, align 4
  %42 = getelementptr [2 x [2 x i64]], ptr %40, i64 0, i64 1
  store [2 x i64] [i64 3, i64 4], ptr %42, align 4
  %43 = alloca i64, align 8
  store i64 0, ptr %43, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %44 = alloca i64, align 8
  store i64 0, ptr %44, align 4
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %45 = load i64, ptr %43, align 4
  %46 = icmp slt i64 %45, 2
  br i1 %46, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %47 = load i64, ptr %43, align 4
  %48 = add i64 %47, 1
  store i64 %48, ptr %43, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

for.body1:                                        ; preds = %for.cond2
  %49 = load i64, ptr %43, align 4
  %50 = getelementptr [2 x [2 x i64]], ptr %40, i64 0, i64 %49
  %51 = load i64, ptr %44, align 4
  %52 = getelementptr inbounds ptr, ptr %50, i64 %51
  %53 = load i64, ptr %38, align 4
  %54 = load i64, ptr %52, align 4
  %55 = add i64 %53, %54
  %56 = load i64, ptr %38, align 4
  store i64 %55, ptr %38, align 4
  %57 = load i64, ptr %43, align 4
  %58 = mul i64 %57, 2
  %59 = getelementptr inbounds ptr, ptr @Global2dArray, i64 %58
  %60 = load i64, ptr %44, align 4
  %61 = getelementptr inbounds ptr, ptr %59, i64 %60
  %62 = load i64, ptr %39, align 4
  %63 = load i64, ptr %61, align 4
  %64 = add i64 %62, %63
  %65 = load i64, ptr %39, align 4
  store i64 %64, ptr %39, align 4
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.body
  %66 = load i64, ptr %44, align 4
  %67 = icmp slt i64 %66, 2
  br i1 %67, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %68 = load i64, ptr %44, align 4
  %69 = add i64 %68, 1
  store i64 %69, ptr %44, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

exit:                                             ; preds = %return, %for.end
  %70 = load i64, ptr %0, align 4
  ret i64 %70
}
