; ModuleID = 'test_increment.ola'
source_filename = "test_increment.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestPreIncrementDecrement() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestPostIncrementDecrement() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestPreIncrementDecrement()
  tail call void @TestPostIncrementDecrement()
  ret i64 0
}
