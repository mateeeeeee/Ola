; ModuleID = 'test_ref.ola'
source_filename = "test_ref.ola"

%S = type { i64, i64 }

@g = internal global i64 9
@s = global %S zeroinitializer

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @IntByRef(ptr %a) {
entry:
  %0 = load i64, ptr %a, align 4
  %1 = add i64 %0, 1
  store i64 %1, ptr %a, align 4
  ret void
}

define internal void @IntByValue(i64 %a) {
entry:
  ret void
}

define internal void @TestRefSimple() {
entry:
  %0 = alloca i64, align 8
  store i64 9, ptr %0, align 8
  call void @IntByRef(ptr nonnull %0)
  %1 = load i64, ptr %0, align 8
  %2 = icmp eq i64 %1, 10
  call void @Assert(i1 %2)
  %3 = load i64, ptr %0, align 8
  %4 = add i64 %3, 1
  store i64 %4, ptr %0, align 8
  %5 = icmp eq i64 %4, 11
  call void @Assert(i1 %5)
  %6 = load i64, ptr %0, align 8
  %7 = icmp eq i64 %6, 11
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 8
  %9 = icmp eq i64 %8, 11
  call void @Assert(i1 %9)
  %10 = load i64, ptr %0, align 8
  %11 = add i64 %10, 1
  store i64 %11, ptr %0, align 8
  %12 = icmp eq i64 %11, 12
  call void @Assert(i1 %12)
  call void @IntByRef(ptr nonnull %0)
  %13 = load i64, ptr %0, align 8
  %14 = icmp eq i64 %13, 13
  call void @Assert(i1 %14)
  %15 = load i64, ptr %0, align 8
  call void @IntByValue(i64 %15)
  %16 = load i64, ptr %0, align 8
  %17 = icmp eq i64 %16, 13
  call void @Assert(i1 %17)
  ret void
}

define internal ptr @ReturnRef() {
entry:
  ret ptr @g
}

define internal i64 @ReturnValue() {
entry:
  %0 = alloca i64, align 8
  store ptr @g, ptr %0, align 8
  %1 = load i64, ptr %0, align 8
  ret i64 %1
}

define internal void @TestRefReturnSimple() {
entry:
  %0 = tail call ptr @ReturnRef()
  %1 = load i64, ptr %0, align 4
  %2 = add i64 %1, 1
  store i64 %2, ptr %0, align 4
  %3 = load i64, ptr @g, align 8
  %4 = icmp eq i64 %3, 10
  tail call void @Assert(i1 %4)
  %5 = tail call ptr @ReturnRef()
  %6 = load i64, ptr @g, align 8
  %7 = icmp eq i64 %6, 10
  tail call void @Assert(i1 %7)
  %8 = tail call i64 @ReturnValue()
  %9 = load i64, ptr @g, align 8
  %10 = icmp eq i64 %9, 10
  tail call void @Assert(i1 %10)
  ret void
}

define void @"S::Init"(ptr %this, i64 %x, i64 %y) {
entry:
  %.cast = inttoptr i64 %x to ptr
  store ptr %.cast, ptr %this, align 8
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  %.cast1 = inttoptr i64 %y to ptr
  store ptr %.cast1, ptr %0, align 8
  ret void
}

define internal void @StructByRef(ptr %s) {
entry:
  %0 = load i64, ptr %s, align 4
  %1 = add i64 %0, 1
  store i64 %1, ptr %s, align 4
  %2 = getelementptr inbounds %S, ptr %s, i64 0, i32 1
  %3 = load i64, ptr %2, align 4
  %4 = add i64 %3, 1
  store i64 %4, ptr %2, align 4
  ret void
}

define internal void @StructByValue(%S %s) {
entry:
  ret void
}

define internal void @TestRefStruct() {
entry:
  %0 = alloca %S, align 8
  store i64 0, ptr %0, align 8
  %1 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  store i64 0, ptr %1, align 8
  call void @"S::Init"(ptr nonnull %0, i64 9, i64 9)
  %.unpack = load i64, ptr %0, align 8
  %2 = insertvalue %S poison, i64 %.unpack, 0
  %.elt1 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  %.unpack2 = load i64, ptr %.elt1, align 8
  %3 = insertvalue %S %2, i64 %.unpack2, 1
  call void @StructByValue(%S %3)
  %4 = load i64, ptr %0, align 8
  %5 = icmp eq i64 %4, 9
  call void @Assert(i1 %5)
  %6 = load i64, ptr %1, align 8
  %7 = icmp eq i64 %6, 9
  call void @Assert(i1 %7)
  call void @StructByRef(ptr nonnull %0)
  %8 = load i64, ptr %0, align 8
  %9 = icmp eq i64 %8, 10
  call void @Assert(i1 %9)
  %10 = load i64, ptr %1, align 8
  %11 = icmp eq i64 %10, 10
  call void @Assert(i1 %11)
  %12 = load i64, ptr %0, align 8
  %13 = add i64 %12, 1
  store i64 %13, ptr %0, align 8
  %14 = load i64, ptr %1, align 8
  %15 = add i64 %14, 1
  store i64 %15, ptr %1, align 8
  %16 = icmp eq i64 %13, 11
  call void @Assert(i1 %16)
  %17 = load i64, ptr %1, align 8
  %18 = icmp eq i64 %17, 11
  call void @Assert(i1 %18)
  %19 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %19, ptr noundef nonnull align 8 dereferenceable(16) %0, i64 16, i1 false)
  %20 = load i64, ptr %19, align 8
  %21 = add i64 %20, 1
  store i64 %21, ptr %19, align 8
  %22 = getelementptr inbounds %S, ptr %19, i64 0, i32 1
  %23 = load i64, ptr %22, align 8
  %24 = add i64 %23, 1
  store i64 %24, ptr %22, align 8
  %25 = icmp eq i64 %21, 12
  call void @Assert(i1 %25)
  %26 = load i64, ptr %0, align 8
  %27 = icmp eq i64 %26, 11
  call void @Assert(i1 %27)
  %28 = load i64, ptr %0, align 8
  %29 = add i64 %28, 1
  store i64 %29, ptr %0, align 8
  %30 = load i64, ptr %1, align 8
  %31 = add i64 %30, 1
  store i64 %31, ptr %1, align 8
  %32 = icmp eq i64 %29, 12
  call void @Assert(i1 %32)
  %33 = load i64, ptr %1, align 8
  %34 = icmp eq i64 %33, 12
  call void @Assert(i1 %34)
  call void @StructByRef(ptr nonnull %0)
  %35 = load i64, ptr %0, align 8
  %36 = icmp eq i64 %35, 13
  call void @Assert(i1 %36)
  %37 = load i64, ptr %1, align 8
  %38 = icmp eq i64 %37, 13
  call void @Assert(i1 %38)
  %.unpack3 = load i64, ptr %0, align 8
  %39 = insertvalue %S poison, i64 %.unpack3, 0
  %.elt4 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  %.unpack5 = load i64, ptr %.elt4, align 8
  %40 = insertvalue %S %39, i64 %.unpack5, 1
  call void @StructByValue(%S %40)
  %41 = load i64, ptr %0, align 8
  %42 = icmp eq i64 %41, 13
  call void @Assert(i1 %42)
  %43 = load i64, ptr %1, align 8
  %44 = icmp eq i64 %43, 13
  call void @Assert(i1 %44)
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

define internal void @ReturnValueS(ptr %0) {
entry:
  store ptr @s, ptr %0, align 8
  ret void
}

define internal ptr @ReturnRefS() {
entry:
  ret ptr @s
}

define internal void @TestRefReturnStruct() {
entry:
  tail call void @"S::Init"(ptr nonnull @s, i64 9, i64 9)
  %0 = tail call ptr @ReturnRefS()
  %1 = load i64, ptr %0, align 4
  %2 = add i64 %1, 1
  store i64 %2, ptr %0, align 4
  %3 = getelementptr inbounds %S, ptr %0, i64 0, i32 1
  %4 = load i64, ptr %3, align 4
  %5 = add i64 %4, 1
  store i64 %5, ptr %3, align 4
  %6 = load i64, ptr @s, align 8
  %7 = icmp eq i64 %6, 10
  tail call void @Assert(i1 %7)
  %8 = load i64, ptr getelementptr inbounds (%S, ptr @s, i64 0, i32 1), align 8
  %9 = icmp eq i64 %8, 10
  tail call void @Assert(i1 %9)
  %10 = tail call ptr @ReturnRefS()
  %11 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %11, ptr noundef nonnull align 1 dereferenceable(16) %10, i64 16, i1 false)
  %12 = load i64, ptr %11, align 8
  %13 = add i64 %12, 2
  store i64 %13, ptr %11, align 8
  %14 = load i64, ptr @s, align 8
  %15 = icmp eq i64 %14, 10
  tail call void @Assert(i1 %15)
  %16 = load i64, ptr getelementptr inbounds (%S, ptr @s, i64 0, i32 1), align 8
  %17 = icmp eq i64 %16, 10
  tail call void @Assert(i1 %17)
  %18 = alloca ptr, align 8
  call void @ReturnValueS(ptr nonnull %18)
  %19 = alloca %S, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %19, ptr noundef nonnull align 8 dereferenceable(16) %18, i64 16, i1 false)
  %20 = load i64, ptr %19, align 8
  %21 = add i64 %20, 2
  store i64 %21, ptr %19, align 8
  %22 = load i64, ptr @s, align 8
  %23 = icmp eq i64 %22, 10
  call void @Assert(i1 %23)
  %24 = load i64, ptr getelementptr inbounds (%S, ptr @s, i64 0, i32 1), align 8
  %25 = icmp eq i64 %24, 10
  call void @Assert(i1 %25)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestRefSimple()
  tail call void @TestRefReturnSimple()
  tail call void @TestRefStruct()
  tail call void @TestRefReturnStruct()
  ret i64 0
}

attributes #0 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
