; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { i64 }
%Derived = type { i64, i64 }
%ExtendedDerived = type { i64, i64, i64 }

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @"Base::GetX"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Base, ptr %this, i32 0, i32 0
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

define i64 @"Base::GetSum"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @"Base::GetX"(ptr %this)
  store i64 %1, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}

define i64 @"Derived::GetY"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %Derived, ptr %this, i32 0, i32 1
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

define i64 @"Derived::GetSum"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @"Derived::GetY"(ptr %this)
  %2 = call i64 @"Base::GetSum"(ptr %this)
  %3 = add i64 %1, %2
  store i64 %3, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define i64 @"ExtendedDerived::GetZ"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = getelementptr inbounds %ExtendedDerived, ptr %this, i32 0, i32 2
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

define i64 @"ExtendedDerived::GetSum"(ptr %this) {
entry:
  %0 = alloca i64, align 8
  %1 = call i64 @"ExtendedDerived::GetZ"(ptr %this)
  %2 = call i64 @"Derived::GetSum"(ptr %this)
  %3 = add i64 %1, %2
  store i64 %3, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define internal void @PassBase__Base(%Base %b) {
entry:
  %0 = alloca %Base, align 8
  store %Base %b, ptr %0, align 4
  %1 = call i64 @"Base::GetX"(ptr %0)
  %2 = icmp eq i64 %1, 1
  call void @Assert(i1 %2)
  %3 = call i64 @"Base::GetSum"(ptr %0)
  %4 = icmp eq i64 %3, 1
  call void @Assert(i1 %4)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @PassBaseRef__Baseref(ptr %b) {
entry:
  %0 = alloca ptr, align 8
  store ptr %b, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = call i64 @"Base::GetX"(ptr %1)
  %3 = icmp eq i64 %2, 1
  call void @Assert(i1 %3)
  %4 = call i64 @"Base::GetSum"(ptr %1)
  %5 = icmp eq i64 %4, 1
  call void @Assert(i1 %5)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @PassDerived__Derived(%Derived %d) {
entry:
  %0 = alloca %Derived, align 8
  store %Derived %d, ptr %0, align 4
  %1 = call i64 @"Base::GetX"(ptr %0)
  %2 = icmp eq i64 %1, 1
  call void @Assert(i1 %2)
  %3 = call i64 @"Derived::GetY"(ptr %0)
  %4 = icmp eq i64 %3, 2
  call void @Assert(i1 %4)
  %5 = call i64 @"Derived::GetSum"(ptr %0)
  %6 = icmp eq i64 %5, 3
  call void @Assert(i1 %6)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @PassDerivedRef__Derivedref(ptr %d) {
entry:
  %0 = alloca ptr, align 8
  store ptr %d, ptr %0, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = call i64 @"Base::GetX"(ptr %1)
  %3 = icmp eq i64 %2, 1
  call void @Assert(i1 %3)
  %4 = call i64 @"Derived::GetY"(ptr %1)
  %5 = icmp eq i64 %4, 2
  call void @Assert(i1 %5)
  %6 = call i64 @"Derived::GetSum"(ptr %1)
  %7 = icmp eq i64 %6, 3
  call void @Assert(i1 %7)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestAssignment() {
entry:
  %0 = alloca %Derived, align 8
  %1 = getelementptr inbounds %Derived, ptr %0, i32 0, i32 0
  store i64 1, ptr %1, align 4
  %2 = getelementptr inbounds %Derived, ptr %0, i32 0, i32 1
  store i64 2, ptr %2, align 4
  %3 = load %Derived, ptr %0, align 4
  %4 = getelementptr inbounds %Base, ptr %0, i32 0, i32 0
  %5 = alloca %Base, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %5, ptr %4, i64 8, i1 false)
  %6 = call i64 @"Base::GetX"(ptr %5)
  %7 = icmp eq i64 %6, 1
  call void @Assert(i1 %7)
  %8 = call i64 @"Base::GetSum"(ptr %5)
  %9 = icmp eq i64 %8, 1
  call void @Assert(i1 %9)
  %10 = load %Base, ptr %5, align 4
  call void @PassBase__Base(%Base %10)
  %11 = load %Base, ptr %5, align 4
  call void @PassBaseRef__Baseref(ptr %5)
  %12 = alloca %ExtendedDerived, align 8
  %13 = getelementptr inbounds %ExtendedDerived, ptr %12, i32 0, i32 1
  store i64 2, ptr %13, align 4
  %14 = getelementptr inbounds %ExtendedDerived, ptr %12, i32 0, i32 0
  store i64 1, ptr %14, align 4
  %15 = getelementptr inbounds %ExtendedDerived, ptr %12, i32 0, i32 2
  store i64 3, ptr %15, align 4
  %16 = call i64 @"ExtendedDerived::GetSum"(ptr %12)
  %17 = icmp eq i64 %16, 6
  call void @Assert(i1 %17)
  %18 = call i64 @"ExtendedDerived::GetZ"(ptr %12)
  %19 = icmp eq i64 %18, 3
  call void @Assert(i1 %19)
  %20 = load %ExtendedDerived, ptr %12, align 4
  %21 = getelementptr inbounds %Base, ptr %12, i32 0, i32 0
  %22 = alloca %Base, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %22, ptr %21, i64 8, i1 false)
  %23 = call i64 @"Base::GetX"(ptr %22)
  %24 = icmp eq i64 %23, 1
  call void @Assert(i1 %24)
  %25 = call i64 @"Base::GetSum"(ptr %22)
  %26 = icmp eq i64 %25, 1
  call void @Assert(i1 %26)
  %27 = load %Base, ptr %22, align 4
  call void @PassBase__Base(%Base %27)
  %28 = load %Base, ptr %22, align 4
  call void @PassBaseRef__Baseref(ptr %22)
  %29 = load %ExtendedDerived, ptr %12, align 4
  %30 = getelementptr inbounds %Derived, ptr %12, i32 0, i32 0
  %31 = alloca %Derived, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %31, ptr %30, i64 16, i1 false)
  %32 = call i64 @"Base::GetX"(ptr %31)
  %33 = icmp eq i64 %32, 1
  call void @Assert(i1 %33)
  %34 = call i64 @"Derived::GetY"(ptr %31)
  %35 = icmp eq i64 %34, 2
  call void @Assert(i1 %35)
  %36 = call i64 @"Derived::GetSum"(ptr %31)
  %37 = icmp eq i64 %36, 3
  call void @Assert(i1 %37)
  %38 = load %Derived, ptr %31, align 4
  call void @PassDerived__Derived(%Derived %38)
  %39 = load %Derived, ptr %31, align 4
  call void @PassDerivedRef__Derivedref(ptr %31)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #0

define internal void @TestReferenceAssignment() {
entry:
  %0 = alloca %Derived, align 8
  %1 = getelementptr inbounds %Derived, ptr %0, i32 0, i32 0
  store i64 1, ptr %1, align 4
  %2 = getelementptr inbounds %Derived, ptr %0, i32 0, i32 1
  store i64 2, ptr %2, align 4
  %3 = load %Derived, ptr %0, align 4
  %4 = alloca ptr, align 8
  store ptr %0, ptr %4, align 8
  %5 = load ptr, ptr %4, align 8
  %6 = call i64 @"Base::GetX"(ptr %5)
  %7 = icmp eq i64 %6, 1
  call void @Assert(i1 %7)
  %8 = call i64 @"Base::GetSum"(ptr %5)
  %9 = icmp eq i64 %8, 1
  call void @Assert(i1 %9)
  %10 = alloca %ExtendedDerived, align 8
  %11 = getelementptr inbounds %ExtendedDerived, ptr %10, i32 0, i32 1
  store i64 2, ptr %11, align 4
  %12 = getelementptr inbounds %ExtendedDerived, ptr %10, i32 0, i32 0
  store i64 1, ptr %12, align 4
  %13 = getelementptr inbounds %ExtendedDerived, ptr %10, i32 0, i32 2
  store i64 3, ptr %13, align 4
  %14 = load %ExtendedDerived, ptr %10, align 4
  %15 = alloca ptr, align 8
  store ptr %10, ptr %15, align 8
  %16 = load ptr, ptr %15, align 8
  %17 = call i64 @"Base::GetX"(ptr %16)
  %18 = icmp eq i64 %17, 1
  call void @Assert(i1 %18)
  %19 = call i64 @"Base::GetSum"(ptr %16)
  %20 = icmp eq i64 %19, 1
  call void @Assert(i1 %20)
  %21 = load %ExtendedDerived, ptr %10, align 4
  %22 = alloca ptr, align 8
  store ptr %10, ptr %22, align 8
  %23 = load ptr, ptr %22, align 8
  %24 = call i64 @"Base::GetX"(ptr %23)
  %25 = icmp eq i64 %24, 1
  call void @Assert(i1 %25)
  %26 = call i64 @"Derived::GetY"(ptr %23)
  %27 = icmp eq i64 %26, 2
  call void @Assert(i1 %27)
  %28 = call i64 @"Derived::GetSum"(ptr %23)
  %29 = icmp eq i64 %28, 3
  call void @Assert(i1 %29)
  %30 = load ptr, ptr %23, align 8
  %31 = alloca %Base, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr %31, ptr %23, i64 8, i1 false)
  %32 = call i64 @"Base::GetX"(ptr %31)
  %33 = icmp eq i64 %32, 1
  call void @Assert(i1 %33)
  %34 = call i64 @"Base::GetSum"(ptr %31)
  %35 = icmp eq i64 %34, 1
  call void @Assert(i1 %35)
  %36 = load %Base, ptr %31, align 4
  call void @PassBase__Base(%Base %36)
  %37 = load %Base, ptr %31, align 4
  call void @PassBaseRef__Baseref(ptr %31)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestAssignment()
  call void @TestReferenceAssignment()
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
