; ModuleID = 'test.ola'
source_filename = "test.ola"

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

define void @"S::SetX"(ptr %this, i64 %x) {
entry:
  %0 = alloca i64, align 8
  store i64 %x, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define void @"S::SetY"(ptr %this, i64 %y) {
entry:
  %0 = alloca i64, align 8
  store i64 %y, ptr %0, align 4
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %2 = load i64, ptr %1, align 4
  %3 = load i64, ptr %0, align 4
  %4 = load ptr, ptr %0, align 8
  store ptr %4, ptr %1, align 8
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @"S::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 0
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define i64 @"S::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %S, ptr %this, i32 0, i32 1
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}

define internal void @StructByValue(%S %s) {
entry:
  %0 = alloca %S, align 8
  store %S %s, ptr %0, align 4
  call void @"S::SetX"(ptr %0, i64 100)
  call void @"S::SetY"(ptr %0, i64 100)
  %1 = call i64 @"S::GetX"(ptr %0)
  %2 = icmp eq i64 %1, 100
  call void @Assert(i1 %2)
  %3 = call i64 @"S::GetY"(ptr %0)
  %4 = icmp eq i64 %3, 100
  call void @Assert(i1 %4)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @StructByRef(ptr %s) {
entry:
  %0 = alloca ptr, align 8
  store ptr %s, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  call void @"S::SetX"(ptr %1, i64 1000)
  call void @"S::SetY"(ptr %1, i64 1000)
  %2 = call i64 @"S::GetX"(ptr %1)
  %3 = icmp eq i64 %2, 1000
  call void @Assert(i1 %3)
  %4 = call i64 @"S::GetY"(ptr %1)
  %5 = icmp eq i64 %4, 1000
  call void @Assert(i1 %5)
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
  %5 = call i64 @"S::GetX"(ptr %1)
  %6 = icmp eq i64 %5, 10
  call void @Assert(i1 %6)
  %7 = call i64 @"S::GetY"(ptr %1)
  %8 = icmp eq i64 %7, 10
  call void @Assert(i1 %8)
  %9 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %9, ptr %1, i64 16, i1 false)
  call void @"S::SetX"(ptr %1, i64 25)
  call void @"S::SetY"(ptr %1, i64 25)
  %10 = call i64 @"S::GetX"(ptr %9)
  %11 = icmp eq i64 %10, 10
  call void @Assert(i1 %11)
  %12 = call i64 @"S::GetY"(ptr %9)
  %13 = icmp eq i64 %12, 10
  call void @Assert(i1 %13)
  %14 = call i64 @"S::GetX"(ptr %1)
  %15 = icmp eq i64 %14, 25
  call void @Assert(i1 %15)
  %16 = call i64 @"S::GetY"(ptr %1)
  %17 = icmp eq i64 %16, 25
  call void @Assert(i1 %17)
  %18 = load %S, ptr %1, align 4
  call void @StructByRef(ptr %1)
  %19 = call i64 @"S::GetX"(ptr %1)
  %20 = icmp eq i64 %19, 1000
  call void @Assert(i1 %20)
  %21 = call i64 @"S::GetY"(ptr %1)
  %22 = icmp eq i64 %21, 1000
  call void @Assert(i1 %22)
  %23 = load %S, ptr %1, align 4
  %24 = alloca ptr, align 8
  store ptr %1, ptr %24, align 8
  %25 = load ptr, ptr %24, align 8
  %26 = call i64 @"S::GetX"(ptr %25)
  %27 = icmp eq i64 %26, 1000
  call void @Assert(i1 %27)
  %28 = call i64 @"S::GetY"(ptr %25)
  %29 = icmp eq i64 %28, 1000
  call void @Assert(i1 %29)
  call void @"S::SetX"(ptr %25, i64 0)
  %30 = call i64 @"S::GetX"(ptr %1)
  %31 = icmp eq i64 %30, 0
  call void @Assert(i1 %31)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %32 = load i64, ptr %0, align 4
  ret i64 %32
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
