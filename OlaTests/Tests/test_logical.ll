; ModuleID = 'test_logical.ola'
source_filename = "test_logical.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestUnaryLogicalOperators() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestBinaryLogicalOperators() {
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

define internal void @TestBinaryLogicalOperatorsImplicitCasts() {
entry:
  tail call void @Assert(i1 poison)
  tail call void @Assert(i1 poison)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 poison)
  ret void
}

define internal void @TestLogicalOperatorsImplicitCasts() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 poison)
  tail call void @Assert(i1 poison)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestUnaryLogicalOperators()
  tail call void @TestBinaryLogicalOperators()
  tail call void @TestBinaryLogicalOperatorsImplicitCasts()
  tail call void @TestLogicalOperatorsImplicitCasts()
  ret i64 0
}
