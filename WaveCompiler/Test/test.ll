; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64, i64 }

@s = global %S zeroinitializer

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"S::Init"(ptr %this, i64 %x, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 %y, ptr %1, align 4
  %2 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %3 = load i64, ptr %2, align 4
  %4 = load i64, ptr %0, align 4
  %5 = load ptr, ptr %0, align 8
  store ptr %5, ptr %2, align 8
  %6 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %7 = load i64, ptr %6, align 4
  %8 = load i64, ptr %1, align 4
  %9 = load ptr, ptr %1, align 8
  store ptr %9, ptr %6, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @ReturnValueS(ptr %0) {
entry:
  store ptr @s, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  ret void
}

define internal ptr @ReturnRefS() {
entry:
  %0 = alloca ptr, align 8
  %1 = load %S, ptr @s, align 4
  store ptr @s, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load ptr, ptr %0, align 8
  ret ptr %2
}

define internal void @TestRefReturnStruct() {
entry:
  call void @"S::Init"(ptr @s, i64 9, i64 9)
  %0 = call ptr @ReturnRefS()
  %1 = load ptr, ptr %0, align 8
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr inbounds %S, ptr %3, i32 0, i32 0
  %5 = load i64, ptr %4, align 4
  %6 = alloca ptr, align 8
  %7 = load ptr, ptr %4, align 8
  store ptr %7, ptr %6, align 8
  %8 = add i64 %5, 1
  store i64 %8, ptr %4, align 4
  %9 = getelementptr inbounds %S, ptr %3, i32 0, i32 1
  %10 = load i64, ptr %9, align 4
  %11 = alloca ptr, align 8
  %12 = load ptr, ptr %9, align 8
  store ptr %12, ptr %11, align 8
  %13 = add i64 %10, 1
  store i64 %13, ptr %9, align 4
  %14 = load i64, ptr @s, align 4
  %15 = icmp eq i64 %14, 10
  call void @Assert(i1 %15)
  %16 = load i64, ptr getelementptr inbounds (%S, ptr @s, i32 0, i32 1), align 4
  %17 = icmp eq i64 %16, 10
  call void @Assert(i1 %17)
  %18 = call ptr @ReturnRefS()
  %19 = load ptr, ptr %18, align 8
  %20 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %20, ptr %18, i64 16, i1 false)
  %21 = getelementptr inbounds %S, ptr %20, i32 0, i32 0
  %22 = load i64, ptr %21, align 4
  %23 = alloca ptr, align 8
  %24 = load ptr, ptr %21, align 8
  store ptr %24, ptr %23, align 8
  %25 = add i64 %22, 1
  store i64 %25, ptr %21, align 4
  %26 = getelementptr inbounds %S, ptr %20, i32 0, i32 0
  %27 = load i64, ptr %26, align 4
  %28 = alloca ptr, align 8
  %29 = load ptr, ptr %26, align 8
  store ptr %29, ptr %28, align 8
  %30 = add i64 %27, 1
  store i64 %30, ptr %26, align 4
  %31 = load i64, ptr @s, align 4
  %32 = icmp eq i64 %31, 10
  call void @Assert(i1 %32)
  %33 = load i64, ptr getelementptr inbounds (%S, ptr @s, i32 0, i32 1), align 4
  %34 = icmp eq i64 %33, 10
  call void @Assert(i1 %34)
  %35 = alloca ptr, align 8
  call void @ReturnValueS(ptr %35)
  %36 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %36, ptr %35, i64 16, i1 false)
  %37 = getelementptr inbounds %S, ptr %36, i32 0, i32 0
  %38 = load i64, ptr %37, align 4
  %39 = alloca ptr, align 8
  %40 = load ptr, ptr %37, align 8
  store ptr %40, ptr %39, align 8
  %41 = add i64 %38, 1
  store i64 %41, ptr %37, align 4
  %42 = getelementptr inbounds %S, ptr %36, i32 0, i32 0
  %43 = load i64, ptr %42, align 4
  %44 = alloca ptr, align 8
  %45 = load ptr, ptr %42, align 8
  store ptr %45, ptr %44, align 8
  %46 = add i64 %43, 1
  store i64 %46, ptr %42, align 4
  %47 = load i64, ptr @s, align 4
  %48 = icmp eq i64 %47, 10
  call void @Assert(i1 %48)
  %49 = load i64, ptr getelementptr inbounds (%S, ptr @s, i32 0, i32 1), align 4
  %50 = icmp eq i64 %49, 10
  call void @Assert(i1 %50)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestRefReturnStruct()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
