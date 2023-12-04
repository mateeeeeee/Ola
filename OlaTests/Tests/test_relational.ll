; ModuleID = 'test_relational.ola'
source_filename = "test_relational.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestLessThanOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestLessThanOrEqualOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestGreaterThanOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestGreaterThanOrEqualOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestEqualOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestNotEqualOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestLessThanOperators()
  tail call void @TestLessThanOrEqualOperators()
  tail call void @TestGreaterThanOperators()
  tail call void @TestGreaterThanOrEqualOperators()
  tail call void @TestEqualOperators()
  tail call void @TestNotEqualOperators()
  ret i64 0
}
