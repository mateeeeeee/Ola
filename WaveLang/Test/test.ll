; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare void @PrintInteger(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare i64 @ReadInteger()

declare double @ReadFloat()

declare i8 @ReadChar()

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %dowhile.body

dowhile.body:                                     ; preds = %dowhile.cond, %entry
  %3 = load i64, ptr %2, align 4
  %4 = load i64, ptr %1, align 4
  %5 = add i64 %3, %4
  %6 = load i64, ptr %2, align 4
  store i64 %5, ptr %2, align 4
  %7 = load i64, ptr %1, align 4
  %8 = alloca ptr, align 8
  %9 = load ptr, ptr %1, align 8
  store ptr %9, ptr %8, align 8
  %10 = add i64 %7, 1
  store i64 %10, ptr %1, align 4
  br label %dowhile.cond

dowhile.cond:                                     ; preds = %dowhile.body
  %11 = load i64, ptr %1, align 4
  %12 = icmp slt i64 %11, 5
  br i1 %12, label %dowhile.body, label %dowhile.end

dowhile.end:                                      ; preds = %dowhile.cond
  %13 = load i64, ptr %2, align 4
  call void @PrintInteger(i64 %13)
  %14 = load i64, ptr %2, align 4
  %15 = icmp eq i64 %14, 10
  call void @Assert(i1 %15)
  %16 = alloca i64, align 8
  store i64 10, ptr %16, align 4
  %17 = alloca i64, align 8
  store i64 0, ptr %17, align 4
  br label %dowhile.body1

dowhile.body1:                                    ; preds = %dowhile.cond2, %dowhile.end
  %18 = load i64, ptr %17, align 4
  %19 = alloca ptr, align 8
  %20 = load ptr, ptr %17, align 8
  store ptr %20, ptr %19, align 8
  %21 = add i64 %18, 1
  store i64 %21, ptr %17, align 4
  br label %dowhile.cond2

dowhile.cond2:                                    ; preds = %dowhile.body1
  %22 = load i64, ptr %16, align 4
  %23 = icmp slt i64 %22, 10
  br i1 %23, label %dowhile.body1, label %dowhile.end3

dowhile.end3:                                     ; preds = %dowhile.cond2
  %24 = load i64, ptr %17, align 4
  call void @PrintInteger(i64 %24)
  %25 = load i64, ptr %17, align 4
  %26 = icmp eq i64 %25, 1
  call void @Assert(i1 %26)
  %27 = alloca i64, align 8
  store i64 5, ptr %27, align 4
  %28 = alloca i64, align 8
  store i64 3, ptr %28, align 4
  %29 = alloca i64, align 8
  store i64 0, ptr %29, align 4
  br label %dowhile.body4

dowhile.body4:                                    ; preds = %dowhile.cond5, %dowhile.end3
  %30 = load i64, ptr %27, align 4
  %31 = load i64, ptr %28, align 4
  %32 = icmp sgt i64 %30, %31
  br i1 %32, label %if.then, label %if.end

dowhile.cond5:                                    ; preds = %if.end
  %33 = load i64, ptr %27, align 4
  %34 = icmp sgt i64 %33, 0
  %35 = load i64, ptr %28, align 4
  %36 = icmp slt i64 %35, 10
  %37 = and i1 %34, %36
  %38 = icmp ne i1 %37, false
  br i1 %38, label %dowhile.body4, label %dowhile.end6

dowhile.end6:                                     ; preds = %dowhile.cond5
  %39 = load i64, ptr %29, align 4
  call void @PrintInteger(i64 %39)
  %40 = load i64, ptr %29, align 4
  %41 = icmp eq i64 %40, 5
  call void @Assert(i1 %41)
  %42 = alloca i64, align 8
  store i64 1, ptr %42, align 4
  %43 = alloca i64, align 8
  store i64 0, ptr %43, align 4
  br label %dowhile.body7

if.then:                                          ; preds = %dowhile.body4
  %44 = load i64, ptr %29, align 4
  %45 = load i64, ptr %27, align 4
  %46 = add i64 %44, %45
  %47 = load i64, ptr %29, align 4
  store i64 %46, ptr %29, align 4
  br label %if.end

if.else:                                          ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

if.end:                                           ; preds = %if.then, %dowhile.body4
  %48 = load i64, ptr %27, align 4
  %49 = alloca ptr, align 8
  %50 = load ptr, ptr %27, align 8
  store ptr %50, ptr %49, align 8
  %51 = sub i64 %48, 1
  store i64 %51, ptr %27, align 4
  %52 = load i64, ptr %28, align 4
  %53 = alloca ptr, align 8
  %54 = load ptr, ptr %28, align 8
  store ptr %54, ptr %53, align 8
  %55 = add i64 %52, 1
  store i64 %55, ptr %28, align 4
  br label %dowhile.cond5

dowhile.body7:                                    ; preds = %dowhile.cond8, %dowhile.end6
  %56 = load i64, ptr %43, align 4
  %57 = load i64, ptr %42, align 4
  %58 = add i64 %56, %57
  %59 = load i64, ptr %43, align 4
  store i64 %58, ptr %43, align 4
  %60 = load i64, ptr %43, align 4
  %61 = icmp sge i64 %60, 10
  br i1 %61, label %if.then10, label %if.end12

dowhile.cond8:                                    ; preds = %if.end12
  %62 = load i64, ptr %42, align 4
  %63 = icmp sle i64 %62, 5
  br i1 %63, label %dowhile.body7, label %dowhile.end9

dowhile.end9:                                     ; preds = %dowhile.cond8, %if.then10
  %64 = load i64, ptr %43, align 4
  call void @PrintInteger(i64 %64)
  %65 = load i64, ptr %43, align 4
  %66 = icmp eq i64 %65, 10
  call void @Assert(i1 %66)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop13 = alloca i1, align 1
  br label %exit

if.then10:                                        ; preds = %dowhile.body7
  br label %dowhile.end9

if.else11:                                        ; No predecessors!
  %nop14 = alloca i1, align 1
  br label %exit

if.end12:                                         ; preds = %dowhile.body7
  %67 = load i64, ptr %42, align 4
  %68 = alloca ptr, align 8
  %69 = load ptr, ptr %42, align 8
  store ptr %69, ptr %68, align 8
  %70 = add i64 %67, 1
  store i64 %70, ptr %42, align 4
  br label %dowhile.cond8

break:                                            ; No predecessors!
  %nop15 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %break, %if.else11, %return, %if.else, %dowhile.end9
  %71 = load i64, ptr %0, align 4
  ret i64 %71
}
