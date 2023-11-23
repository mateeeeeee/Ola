; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%S = type { i64, i64 }

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

define internal void @StructByValue(%S %s) {
entry:
  %0 = alloca %S, align 8
  store %S %s, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %2 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %3 = load i64, ptr %2, align 4
  %4 = mul i64 %3, 2
  %5 = load i64, ptr %1, align 4
  store i64 %4, ptr %1, align 4
  %6 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %7 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %8 = load i64, ptr %7, align 4
  %9 = mul i64 %8, 2
  %10 = load i64, ptr %6, align 4
  store i64 %9, ptr %6, align 4
  %11 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 20
  call void @Assert(i1 %13)
  %14 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %15 = load i64, ptr %14, align 4
  %16 = icmp eq i64 %15, 20
  call void @Assert(i1 %16)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  store i64 0, ptr %2, align 4
  %3 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  store i64 0, ptr %3, align 4
  call void @"S::Init"(ptr %1, i64 10, i64 10)
  %4 = load %S, ptr %1, align 4
  call void @StructByValue(%S %4)
  %5 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 10
  call void @Assert(i1 %7)
  %8 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %9 = load i64, ptr %8, align 4
  %10 = icmp eq i64 %9, 10
  call void @Assert(i1 %10)
  %11 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %11, ptr %1, i64 16, i1 false)
  %12 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %13 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %14 = load i64, ptr %13, align 4
  %15 = mul i64 %14, 2
  %16 = load i64, ptr %12, align 4
  store i64 %15, ptr %12, align 4
  %17 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %18 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %19 = load i64, ptr %18, align 4
  %20 = mul i64 %19, 2
  %21 = load i64, ptr %17, align 4
  store i64 %20, ptr %17, align 4
  %22 = getelementptr inbounds %S, ptr %11, i32 0, i32 0
  %23 = load i64, ptr %22, align 4
  %24 = icmp eq i64 %23, 10
  call void @Assert(i1 %24)
  %25 = getelementptr inbounds %S, ptr %11, i32 0, i32 1
  %26 = load i64, ptr %25, align 4
  %27 = icmp eq i64 %26, 10
  call void @Assert(i1 %27)
  %28 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %29 = load i64, ptr %28, align 4
  %30 = icmp eq i64 %29, 20
  call void @Assert(i1 %30)
  %31 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %32 = load i64, ptr %31, align 4
  %33 = icmp eq i64 %32, 20
  call void @Assert(i1 %33)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %34 = load i64, ptr %0, align 4
  ret i64 %34
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
