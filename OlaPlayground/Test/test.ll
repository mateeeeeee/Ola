; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca [5 x i64], align 8
  %2 = getelementptr [5 x i64], ptr %1, i64 0, i64 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr [5 x i64], ptr %1, i64 0, i64 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr [5 x i64], ptr %1, i64 0, i64 2
  store i64 3, ptr %4, align 4
  %5 = getelementptr [5 x i64], ptr %1, i64 0, i64 3
  store i64 4, ptr %5, align 4
  %6 = getelementptr [5 x i64], ptr %1, i64 0, i64 4
  store i64 5, ptr %6, align 4
  %7 = alloca i64, align 8
  store i64 0, ptr %7, align 4
  %8 = alloca i64, align 8
  store i64 0, ptr %8, align 4
  br label %for.cond

for.body:                                         ; preds = %for.cond
  %9 = load i64, ptr %8, align 4
  %10 = getelementptr [5 x i64], ptr %1, i64 0, i64 %9
  %11 = load i64, ptr %7, align 4
  %12 = load i64, ptr %10, align 4
  %13 = add i64 %11, %12
  %14 = load i64, ptr %7, align 4
  store i64 %13, ptr %7, align 4
  br label %for.iter

for.cond:                                         ; preds = %for.iter, %entry
  %15 = load i64, ptr %8, align 4
  %16 = icmp slt i64 %15, 5
  br i1 %16, label %for.body, label %for.end

for.iter:                                         ; preds = %for.body
  %17 = load i64, ptr %8, align 4
  %18 = alloca ptr, align 8
  store i64 %17, ptr %18, align 4
  %19 = add i64 %17, 1
  store i64 %19, ptr %8, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %20 = load i64, ptr %7, align 4
  %21 = icmp eq i64 %20, 15
  call void @Assert(i1 %21)
  %22 = alloca i64, align 8
  store i64 0, ptr %22, align 4
  br label %for.cond2

for.body1:                                        ; preds = %for.cond2
  %23 = load i64, ptr %22, align 4
  %24 = getelementptr [5 x i64], ptr %1, i64 0, i64 %23
  %25 = load i64, ptr %22, align 4
  %26 = getelementptr [5 x i64], ptr %1, i64 0, i64 %25
  %27 = load i64, ptr %26, align 4
  %28 = mul i64 %27, 2
  %29 = load i64, ptr %24, align 4
  store i64 %28, ptr %24, align 4
  br label %for.iter3

for.cond2:                                        ; preds = %for.iter3, %for.end
  %30 = load i64, ptr %22, align 4
  %31 = icmp slt i64 %30, 5
  br i1 %31, label %for.body1, label %for.end4

for.iter3:                                        ; preds = %for.body1
  %32 = load i64, ptr %22, align 4
  %33 = alloca ptr, align 8
  store i64 %32, ptr %33, align 4
  %34 = add i64 %32, 1
  store i64 %34, ptr %22, align 4
  br label %for.cond2

for.end4:                                         ; preds = %for.cond2
  %35 = getelementptr [5 x i64], ptr %1, i64 0, i64 0
  %36 = load i64, ptr %35, align 4
  %37 = icmp eq i64 %36, 2
  call void @Assert(i1 %37)
  %38 = getelementptr [5 x i64], ptr %1, i64 0, i64 1
  %39 = load i64, ptr %38, align 4
  %40 = icmp eq i64 %39, 4
  call void @Assert(i1 %40)
  %41 = getelementptr [5 x i64], ptr %1, i64 0, i64 2
  %42 = load i64, ptr %41, align 4
  %43 = icmp eq i64 %42, 6
  call void @Assert(i1 %43)
  %44 = getelementptr [5 x i64], ptr %1, i64 0, i64 3
  %45 = load i64, ptr %44, align 4
  %46 = icmp eq i64 %45, 8
  call void @Assert(i1 %46)
  %47 = getelementptr [5 x i64], ptr %1, i64 0, i64 4
  %48 = load i64, ptr %47, align 4
  %49 = icmp eq i64 %48, 10
  call void @Assert(i1 %49)
  %50 = getelementptr [5 x i64], ptr %1, i64 0, i64 0
  %51 = alloca i64, align 8
  %52 = load ptr, ptr %50, align 8
  store ptr %52, ptr %51, align 8
  %53 = alloca i64, align 8
  store i64 1, ptr %53, align 4
  br label %for.cond6

for.body5:                                        ; preds = %for.cond6
  %54 = load i64, ptr %53, align 4
  %55 = getelementptr [5 x i64], ptr %1, i64 0, i64 %54
  %56 = load i64, ptr %55, align 4
  %57 = load i64, ptr %51, align 4
  %58 = icmp sgt i64 %56, %57
  br i1 %58, label %if.then, label %if.end

for.cond6:                                        ; preds = %for.iter7, %for.end4
  %59 = load i64, ptr %53, align 4
  %60 = icmp slt i64 %59, 5
  br i1 %60, label %for.body5, label %for.end8

for.iter7:                                        ; preds = %if.end
  %61 = load i64, ptr %53, align 4
  %62 = alloca ptr, align 8
  store i64 %61, ptr %62, align 4
  %63 = add i64 %61, 1
  store i64 %63, ptr %53, align 4
  br label %for.cond6

for.end8:                                         ; preds = %for.cond6
  %64 = load i64, ptr %51, align 4
  store i64 %64, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.then:                                          ; preds = %for.body5
  %65 = load i64, ptr %53, align 4
  %66 = getelementptr [5 x i64], ptr %1, i64 0, i64 %65
  %67 = load i64, ptr %51, align 4
  %68 = load i64, ptr %66, align 4
  %69 = load ptr, ptr %66, align 8
  store ptr %69, ptr %51, align 8
  br label %if.end

if.else:                                          ; No predecessors!
  %nop9 = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %if.then, %for.body5
  br label %for.iter7

exit:                                             ; preds = %if.else, %return, %for.end8
  %70 = load i64, ptr %0, align 4
  ret i64 %70
}
