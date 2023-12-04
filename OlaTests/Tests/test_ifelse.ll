; ModuleID = 'test_ifelse.ola'
source_filename = "test_ifelse.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIfElseBasic() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIfElseMultipleConditions() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestNestedIfElse() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestComplexNestedIfElse() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIfElseLogicalOperators() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestIfElseBasic()
  tail call void @TestIfElseMultipleConditions()
  tail call void @TestNestedIfElse()
  tail call void @TestComplexNestedIfElse()
  tail call void @TestIfElseLogicalOperators()
  ret i64 0
}
