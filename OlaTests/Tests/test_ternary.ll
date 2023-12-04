; ModuleID = 'test_ternary.ola'
source_filename = "test_ternary.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestTernaryOperatorIntegers() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestTernaryOperatorFloats() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestTernaryOperatorBools() {
entry:
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestTernaryOperatorIntegers()
  tail call void @TestTernaryOperatorFloats()
  tail call void @TestTernaryOperatorBools()
  ret i64 0
}
