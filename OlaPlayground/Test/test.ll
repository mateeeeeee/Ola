; ModuleID = 'test.ola'
source_filename = "test.ola"

%Base = type { ptr, i64 }
%Derived = type { ptr, i64, i64 }

@VTable_Derived = internal constant [2 x ptr] [ptr @"Derived::GetX", ptr @"Derived::GetSumX"]

declare void @Assert(i1) local_unnamed_addr

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read)
define i64 @"Base::GetX"(ptr nocapture readonly %this) local_unnamed_addr #0 {
entry:
  %0 = getelementptr inbounds %Base, ptr %this, i64 0, i32 1
  %1 = load ptr, ptr %0, align 8
  %2 = ptrtoint ptr %1 to i64
  ret i64 %2
}

define i64 @"Base::GetSumX"(ptr %this) local_unnamed_addr {
entry:
  %0 = load ptr, ptr %this, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = tail call i64 %1(ptr nonnull %this)
  ret i64 %2
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read)
define i64 @"Derived::GetX"(ptr nocapture readonly %this) #0 {
entry:
  %0 = getelementptr inbounds %Derived, ptr %this, i64 0, i32 2
  %1 = load ptr, ptr %0, align 8
  %2 = ptrtoint ptr %1 to i64
  ret i64 %2
}

define i64 @"Derived::GetSumX"(ptr %this) {
entry:
  %0 = load ptr, ptr %this, align 8
  %1 = load ptr, ptr %0, align 8
  %2 = tail call i64 %1(ptr nonnull %this)
  %3 = getelementptr inbounds %Base, ptr %this, i64 0, i32 1
  %4 = load ptr, ptr %3, align 8
  %5 = ptrtoint ptr %4 to i64
  %6 = add i64 %2, %5
  ret i64 %6
}

define i64 @main() local_unnamed_addr {
entry:
  tail call void @Assert(i1 true)
  %0 = alloca %Derived, align 8
  store ptr @VTable_Derived, ptr %0, align 8
  %1 = getelementptr inbounds %Derived, ptr %0, i64 0, i32 1
  store i64 1, ptr %1, align 8
  %2 = getelementptr inbounds %Derived, ptr %0, i64 0, i32 2
  store i64 10, ptr %2, align 8
  tail call void @Assert(i1 true)
  %3 = load ptr, ptr %0, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = call i64 %4(ptr nonnull %0)
  %6 = icmp eq i64 %5, 10
  call void @Assert(i1 %6)
  %7 = load ptr, ptr %0, align 8
  %8 = getelementptr inbounds ptr, ptr %7, i64 1
  %9 = load ptr, ptr %8, align 8
  %10 = call i64 %9(ptr nonnull %0)
  %11 = icmp eq i64 %10, 11
  call void @Assert(i1 %11)
  ret i64 0
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) }
