; ModuleID = 'test_class.ola'
source_filename = "test_class.ola"

%S = type { i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define void @"S::Init"(ptr %this, i64 %x, i64 %y) {
entry:
  %.cast = inttoptr i64 %x to ptr
  store ptr %.cast, ptr %this, align 8
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  %.cast1 = inttoptr i64 %y to ptr
  store ptr %.cast1, ptr %0, align 8
  ret void
}

define void @"S::SetX"(ptr %this, i64 %x) {
entry:
  %.cast = inttoptr i64 %x to ptr
  store ptr %.cast, ptr %this, align 8
  ret void
}

define void @"S::SetY"(ptr %this, i64 %y) {
entry:
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  %.cast = inttoptr i64 %y to ptr
  store ptr %.cast, ptr %0, align 8
  ret void
}

define i64 @"S::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = load ptr, ptr %this, align 8
  store ptr %1, ptr %0, align 8
  %2 = load i64, ptr %0, align 8
  ret i64 %2
}

define i64 @"S::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  %3 = load i64, ptr %0, align 8
  ret i64 %3
}

define internal void @StructByValue(%S %s) {
entry:
  %0 = alloca %S, align 8
  %s.elt = extractvalue %S %s, 0
  store i64 %s.elt, ptr %0, align 8
  %.repack1 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  %s.elt2 = extractvalue %S %s, 1
  store i64 %s.elt2, ptr %.repack1, align 8
  call void @"S::SetX"(ptr nonnull %0, i64 100)
  call void @"S::SetY"(ptr nonnull %0, i64 100)
  %1 = call i64 @"S::GetX"(ptr nonnull %0)
  %2 = icmp eq i64 %1, 100
  call void @Assert(i1 %2)
  %3 = call i64 @"S::GetY"(ptr nonnull %0)
  %4 = icmp eq i64 %3, 100
  call void @Assert(i1 %4)
  ret void
}

define internal void @StructByRef(ptr %s) {
entry:
  tail call void @"S::SetX"(ptr %s, i64 1000)
  tail call void @"S::SetY"(ptr %s, i64 1000)
  %0 = tail call i64 @"S::GetX"(ptr %s)
  %1 = icmp eq i64 %0, 1000
  tail call void @Assert(i1 %1)
  %2 = tail call i64 @"S::GetY"(ptr %s)
  %3 = icmp eq i64 %2, 1000
  tail call void @Assert(i1 %3)
  ret void
}

define i64 @main() {
entry:
  %0 = alloca %S, align 8
  store i64 0, ptr %0, align 8
  %1 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  store i64 0, ptr %1, align 8
  call void @"S::Init"(ptr nonnull %0, i64 10, i64 10)
  %.unpack = load i64, ptr %0, align 8
  %2 = insertvalue %S poison, i64 %.unpack, 0
  %.elt1 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  %.unpack2 = load i64, ptr %.elt1, align 8
  %3 = insertvalue %S %2, i64 %.unpack2, 1
  call void @StructByValue(%S %3)
  %4 = call i64 @"S::GetX"(ptr nonnull %0)
  %5 = icmp eq i64 %4, 10
  call void @Assert(i1 %5)
  %6 = call i64 @"S::GetY"(ptr nonnull %0)
  %7 = icmp eq i64 %6, 10
  call void @Assert(i1 %7)
  %8 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %8, ptr noundef nonnull align 8 dereferenceable(16) %0, i64 16, i1 false)
  call void @"S::SetX"(ptr nonnull %0, i64 25)
  call void @"S::SetY"(ptr nonnull %0, i64 25)
  %9 = call i64 @"S::GetX"(ptr nonnull %8)
  %10 = icmp eq i64 %9, 10
  call void @Assert(i1 %10)
  %11 = call i64 @"S::GetY"(ptr nonnull %8)
  %12 = icmp eq i64 %11, 10
  call void @Assert(i1 %12)
  %13 = call i64 @"S::GetX"(ptr nonnull %0)
  %14 = icmp eq i64 %13, 25
  call void @Assert(i1 %14)
  %15 = call i64 @"S::GetY"(ptr nonnull %0)
  %16 = icmp eq i64 %15, 25
  call void @Assert(i1 %16)
  call void @StructByRef(ptr nonnull %0)
  %17 = call i64 @"S::GetX"(ptr nonnull %0)
  %18 = icmp eq i64 %17, 1000
  call void @Assert(i1 %18)
  %19 = call i64 @"S::GetY"(ptr nonnull %0)
  %20 = icmp eq i64 %19, 1000
  call void @Assert(i1 %20)
  %21 = call i64 @"S::GetX"(ptr nonnull %0)
  %22 = icmp eq i64 %21, 1000
  call void @Assert(i1 %22)
  %23 = call i64 @"S::GetY"(ptr nonnull %0)
  %24 = icmp eq i64 %23, 1000
  call void @Assert(i1 %24)
  call void @"S::SetX"(ptr nonnull %0, i64 0)
  %25 = call i64 @"S::GetX"(ptr nonnull %0)
  %26 = icmp eq i64 %25, 0
  call void @Assert(i1 %26)
  ret i64 0
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
