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

define internal void @modifyArrayCopy__I3([3 x i64] %arr) {
entry:
  %0 = alloca [3 x i64], align 8
  store [3 x i64] %arr, ptr %0, align 4
  %1 = getelementptr [3 x i64], ptr %0, i64 0, i64 0
  %2 = load i64, ptr %1, align 4
  store i64 100, ptr %1, align 4
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
  %28 = load [3 x i64], ptr %19, align 4
  call void @modifyArrayCopy__I3([3 x i64] %28)
  %29 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %30 = load i64, ptr %29, align 4
  %31 = icmp eq i64 %30, -5
  call void @Assert(i1 %31)
  %32 = load ptr, ptr %26, align 8
  %33 = getelementptr inbounds ptr, ptr %32, i64 0
  %34 = load i64, ptr %33, align 4
  %35 = icmp eq i64 %34, -5
  call void @Assert(i1 %35)
  call void @modifyArray__I0(ptr %19)
  %36 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %37 = load i64, ptr %36, align 4
  %38 = icmp eq i64 %37, 100
  call void @Assert(i1 %38)
  %39 = load ptr, ptr %26, align 8
  %40 = getelementptr inbounds ptr, ptr %39, i64 0
  %41 = load i64, ptr %40, align 4
  %42 = icmp eq i64 %41, 100
  call void @Assert(i1 %42)
  %43 = load ptr, ptr %26, align 8
  %44 = getelementptr inbounds ptr, ptr %43, i64 0
  %45 = load i64, ptr %44, align 4
  store i64 1000, ptr %44, align 4
  %46 = getelementptr [3 x i64], ptr %19, i64 0, i64 0
  %47 = load i64, ptr %46, align 4
  %48 = icmp eq i64 %47, 1000
  call void @Assert(i1 %48)
  %49 = load ptr, ptr %26, align 8
  %50 = getelementptr inbounds ptr, ptr %49, i64 0
  %51 = load i64, ptr %50, align 4
  %52 = icmp eq i64 %51, 1000
  call void @Assert(i1 %52)
  %53 = alloca i64, align 8
  store i64 0, ptr %53, align 4
  %54 = alloca i64, align 8
  store i64 0, ptr %54, align 4
  %55 = alloca [2 x [2 x i64]], align 8
  %56 = getelementptr [2 x [2 x i64]], ptr %55, i64 0, i64 0
  store [2 x i64] [i64 1, i64 2], ptr %56, align 4
  %57 = getelementptr [2 x [2 x i64]], ptr %55, i64 0, i64 1
  store [2 x i64] [i64 3, i64 4], ptr %57, align 4
  %58 = alloca i64, align 8
  store i64 0, ptr %58, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %59 = alloca i64, align 8
  store i64 0, ptr %59, align 4
  br label %for.cond2

for.cond:                                         ; preds = %for.iter, %entry
  %60 = load i64, ptr %58, align 4
  %61 = icmp slt i64 %60, 2
  br i1 %61, label %for.body, label %for.end

for.iter:                                         ; preds = %for.end4
  %62 = load i64, ptr %58, align 4
  %63 = add i64 %62, 1
  store i64 %63, ptr %58, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %64 = load i64, ptr %53, align 4
  %65 = icmp eq i64 %64, 10
  call void @Assert(i1 %65)
  %66 = load i64, ptr %54, align 4
  %67 = icmp eq i64 %66, 10
  call void @Assert(i1 %67)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

for.body1:                                        ; preds = %for.cond2
  %68 = load i64, ptr %58, align 4
  %69 = getelementptr [2 x [2 x i64]], ptr %55, i64 0, i64 %68
  %70 = load i64, ptr %59, align 4
  %71 = getelementptr inbounds ptr, ptr %69, i64 %70
  %72 = load i64, ptr %53, align 4
  %73 = load i64, ptr %71, align 4
  %74 = add i64 %72, %73
  %75 = load i64, ptr %53, align 4
  store i64 %74, ptr %53, align 4
  %76 = load i64, ptr %58, align 4
  %77 = mul i64 %76, 2
  %78 = getelementptr inbounds ptr, ptr @Global2dArray, i64 %77
  %79 = load i64, ptr %59, align 4
  %80 = getelementptr inbounds ptr, ptr %78, i64 %79
  %81 = load i64, ptr %54, align 4
  %82 = load i64, ptr %80, align 4
  %83 = add i64 %81, %82
  %84 = load i64, ptr %54, align 4
  store i64 %83, ptr %54, align 4
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.body
  %85 = load i64, ptr %59, align 4
  %86 = icmp slt i64 %85, 2
  br i1 %86, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %87 = load i64, ptr %59, align 4
  %88 = add i64 %87, 1
  store i64 %88, ptr %59, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  br label %for.iter

exit:                                             ; preds = %return, %for.end
  %89 = load i64, ptr %0, align 4
  ret i64 %89
}
