; ModuleID = 'test.ola'
source_filename = "test.ola"

%S = type { i64, i64 }

declare void @Assert(i1) local_unnamed_addr

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @"S$Init__I__I"(ptr nocapture writeonly %this, i64 %x, i64 %y) local_unnamed_addr #0 {
entry:
  store i64 %x, ptr %this, align 4
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  store i64 %y, ptr %0, align 4
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @"S$SetX__I"(ptr nocapture writeonly %this, i64 %x) local_unnamed_addr #0 {
entry:
  store i64 %x, ptr %this, align 4
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write)
define void @"S$SetY__I"(ptr nocapture writeonly %this, i64 %y) local_unnamed_addr #0 {
entry:
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  store i64 %y, ptr %0, align 4
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read)
define i64 @"S$GetX"(ptr nocapture readonly %this) local_unnamed_addr #1 {
entry:
  %0 = load ptr, ptr %this, align 8
  %1 = ptrtoint ptr %0 to i64
  ret i64 %1
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read)
define i64 @"S$GetY"(ptr nocapture readonly %this) local_unnamed_addr #1 {
entry:
  %0 = getelementptr inbounds %S, ptr %this, i64 0, i32 1
  %1 = load ptr, ptr %0, align 8
  %2 = ptrtoint ptr %1 to i64
  ret i64 %2
}

define i64 @main() local_unnamed_addr {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret i64 0
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: write) }
attributes #1 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) }
