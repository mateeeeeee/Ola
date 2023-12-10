; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalArray1 = internal global [3 x i64] [i64 1, i64 1, i64 1]
@GlobalArray2 = internal global [5 x i64] [i64 1, i64 2, i64 3, i64 0, i64 0]
@GlobalArray3 = internal global [3 x i64] [i64 10, i64 20, i64 30]
@Global2dArray = internal global [2 x [2 x i64]] [[2 x i64] [i64 1, i64 2], [2 x i64] [i64 3, i64 4]]

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @modifyArray(ptr %arr) {
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

define internal i64 @sumOfArray(ptr %arr, i64 %size) {
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
  %17 = call i64 @sumOfArray(ptr %3, i64 10)
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
  call void @modifyArray(ptr %19)
  %28 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %29 = load i64, ptr %28, align 4
  %30 = icmp eq i64 %29, 100
  call void @Assert(i1 %30)
  %31 = load ptr, ptr %26, align 8
  %32 = getelementptr inbounds ptr, ptr %31, i64 0
  %33 = load i64, ptr %32, align 4
  %34 = icmp eq i64 %33, 100
  call void @Assert(i1 %34)
  %35 = load ptr, ptr %26, align 8
  %36 = getelementptr inbounds ptr, ptr %35, i64 0
  %37 = load i64, ptr %36, align 4
  store i64 1000, ptr %36, align 4
  %38 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %39 = load i64, ptr %38, align 4
  %40 = icmp eq i64 %39, 1000
  call void @Assert(i1 %40)
  %41 = load ptr, ptr %26, align 8
  %42 = getelementptr inbounds ptr, ptr %41, i64 0
  %43 = load i64, ptr %42, align 4
  %44 = icmp eq i64 %43, 1000
  call void @Assert(i1 %44)
  %45 = alloca i64, align 8
  store i64 0, ptr %45, align 4
  %46 = alloca i64, align 8
  store i64 0, ptr %46, align 4
  %47 = alloca [2 x [2 x i64]], align 8
  %48 = getelementptr [2 x [2 x i64]], ptr %47, i64 0, i64 0
  store [2 x i64] [i64 1, i64 2], ptr %48, align 4
  %49 = getelementptr [2 x [2 x i64]], ptr %47, i64 0, i64 1
  store [2 x i64] [i64 3, i64 4], ptr %49, align 4
  %50 = alloca i64, align 8
  store i64 0, ptr %50, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %51 = alloca i64, align 8
  store i64 0, ptr %51, align 4
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %52 = load i64, ptr %50, align 4
  %53 = icmp slt i64 %52, 2
  br i1 %53, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %54 = load i64, ptr %50, align 4
  %55 = add i64 %54, 1
  store i64 %55, ptr %50, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %56 = load i64, ptr %45, align 4
  %57 = icmp eq i64 %56, 10
  call void @Assert(i1 %57)
  %58 = load i64, ptr %46, align 4
  %59 = icmp eq i64 %58, 10
  call void @Assert(i1 %59)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

for.body1:                                        ; preds = %for.cond2
  %60 = load i64, ptr %50, align 4
  %61 = getelementptr [2 x [2 x i64]], ptr %47, i64 0, i64 %60
  %62 = load i64, ptr %51, align 4
  %63 = getelementptr inbounds ptr, ptr %61, i64 %62
  %64 = load i64, ptr %45, align 4
  %65 = load i64, ptr %63, align 4
  %66 = add i64 %64, %65
  %67 = load i64, ptr %45, align 4
  store i64 %66, ptr %45, align 4
  %68 = load i64, ptr %50, align 4
  %69 = mul i64 %68, 2
  %70 = getelementptr inbounds ptr, ptr @Global2dArray, i64 %69
  %71 = load i64, ptr %51, align 4
  %72 = getelementptr inbounds ptr, ptr %70, i64 %71
  %73 = load i64, ptr %46, align 4
  %74 = load i64, ptr %72, align 4
  %75 = add i64 %73, %74
  %76 = load i64, ptr %46, align 4
  store i64 %75, ptr %46, align 4
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.body
  %77 = load i64, ptr %51, align 4
  %78 = icmp slt i64 %77, 2
  br i1 %78, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %79 = load i64, ptr %51, align 4
  %80 = add i64 %79, 1
  store i64 %80, ptr %51, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

exit:                                             ; preds = %return, %for.end
  %81 = load i64, ptr %0, align 4
  ret i64 %81
}
