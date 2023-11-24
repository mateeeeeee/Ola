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

define internal void @StructByRef(ptr %s) {
entry:
  %0 = alloca ptr, align 8
  store ptr %s, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = getelementptr inbounds %S, ptr %1, i32 0, i32 0
  %3 = load i64, ptr %2, align 4
  %4 = alloca ptr, align 8
  %5 = load ptr, ptr %2, align 8
  store ptr %5, ptr %4, align 8
  %6 = add i64 %3, 1
  store i64 %6, ptr %2, align 4
  %7 = getelementptr inbounds %S, ptr %1, i32 0, i32 1
  %8 = load i64, ptr %7, align 4
  %9 = alloca ptr, align 8
  %10 = load ptr, ptr %7, align 8
  store ptr %10, ptr %9, align 8
  %11 = add i64 %8, 1
  store i64 %11, ptr %7, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @StructByValue(%S %s) {
entry:
  %0 = alloca %S, align 8
  store %S %s, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = alloca ptr, align 8
  %4 = load ptr, ptr %1, align 8
  store ptr %4, ptr %3, align 8
  %5 = add i64 %2, 1
  store i64 %5, ptr %1, align 4
  %6 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %7 = load i64, ptr %6, align 4
  %8 = alloca ptr, align 8
  %9 = load ptr, ptr %6, align 8
  store ptr %9, ptr %8, align 8
  %10 = add i64 %7, 1
  store i64 %10, ptr %6, align 4
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestRefStruct() {
entry:
  %0 = alloca %S, align 8
  %1 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  store i64 0, ptr %1, align 4
  %2 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  store i64 0, ptr %2, align 4
  call void @"S::Init"(ptr %0, i64 9, i64 9)
  %3 = load %S, ptr %0, align 4
  call void @StructByValue(%S %3)
  %4 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %5 = load i64, ptr %4, align 4
  %6 = icmp eq i64 %5, 9
  call void @Assert(i1 %6)
  %7 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %8 = load i64, ptr %7, align 4
  %9 = icmp eq i64 %8, 9
  call void @Assert(i1 %9)
  %10 = load %S, ptr %0, align 4
  call void @StructByRef(ptr %0)
  %11 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %12 = load i64, ptr %11, align 4
  %13 = icmp eq i64 %12, 10
  call void @Assert(i1 %13)
  %14 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %15 = load i64, ptr %14, align 4
  %16 = icmp eq i64 %15, 10
  call void @Assert(i1 %16)
  %17 = load %S, ptr %0, align 4
  %18 = alloca ptr, align 8
  store ptr %0, ptr %18, align 8
  %19 = load ptr, ptr %18, align 8
  %20 = getelementptr inbounds %S, ptr %19, i32 0, i32 0
  %21 = load i64, ptr %20, align 4
  %22 = add i64 %21, 1
  store i64 %22, ptr %20, align 4
  %23 = getelementptr inbounds %S, ptr %19, i32 0, i32 1
  %24 = load i64, ptr %23, align 4
  %25 = add i64 %24, 1
  store i64 %25, ptr %23, align 4
  %26 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %27 = load i64, ptr %26, align 4
  %28 = icmp eq i64 %27, 11
  call void @Assert(i1 %28)
  %29 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %30 = load i64, ptr %29, align 4
  %31 = icmp eq i64 %30, 11
  call void @Assert(i1 %31)
  %32 = load ptr, ptr %19, align 8
  %33 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %33, ptr %19, i64 16, i1 false)
  %34 = getelementptr inbounds %S, ptr %33, i32 0, i32 0
  %35 = load i64, ptr %34, align 4
  %36 = add i64 %35, 1
  store i64 %36, ptr %34, align 4
  %37 = getelementptr inbounds %S, ptr %33, i32 0, i32 1
  %38 = load i64, ptr %37, align 4
  %39 = add i64 %38, 1
  store i64 %39, ptr %37, align 4
  %40 = getelementptr inbounds %S, ptr %33, i32 0, i32 0
  %41 = load i64, ptr %40, align 4
  %42 = icmp eq i64 %41, 12
  call void @Assert(i1 %42)
  %43 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %44 = load i64, ptr %43, align 4
  %45 = icmp eq i64 %44, 11
  call void @Assert(i1 %45)
  %46 = load ptr, ptr %19, align 8
  %47 = alloca ptr, align 8
  store ptr %19, ptr %47, align 8
  %48 = load ptr, ptr %47, align 8
  %49 = getelementptr inbounds %S, ptr %48, i32 0, i32 0
  %50 = load i64, ptr %49, align 4
  %51 = add i64 %50, 1
  store i64 %51, ptr %49, align 4
  %52 = getelementptr inbounds %S, ptr %48, i32 0, i32 1
  %53 = load i64, ptr %52, align 4
  %54 = add i64 %53, 1
  store i64 %54, ptr %52, align 4
  %55 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %56 = load i64, ptr %55, align 4
  %57 = icmp eq i64 %56, 12
  call void @Assert(i1 %57)
  %58 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %59 = load i64, ptr %58, align 4
  %60 = icmp eq i64 %59, 12
  call void @Assert(i1 %60)
  %61 = load ptr, ptr %48, align 8
  call void @StructByRef(ptr %48)
  %62 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %63 = load i64, ptr %62, align 4
  %64 = icmp eq i64 %63, 13
  call void @Assert(i1 %64)
  %65 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %66 = load i64, ptr %65, align 4
  %67 = icmp eq i64 %66, 13
  call void @Assert(i1 %67)
  %68 = load ptr, ptr %48, align 8
  %69 = load %S, ptr %48, align 4
  call void @StructByValue(%S %69)
  %70 = getelementptr inbounds %S, ptr %0, i32 0, i32 0
  %71 = load i64, ptr %70, align 4
  %72 = icmp eq i64 %71, 13
  call void @Assert(i1 %72)
  %73 = getelementptr inbounds %S, ptr %0, i32 0, i32 1
  %74 = load i64, ptr %73, align 4
  %75 = icmp eq i64 %74, 13
  call void @Assert(i1 %75)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestRefStruct()
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
