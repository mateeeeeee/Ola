; ModuleID = 'test_multiplicative.ola'
source_filename = "test_multiplicative.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestMultiplication() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestDivision() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestModulo() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestMultiplication()
  tail call void @TestDivision()
  tail call void @TestModulo()
  ret i64 0
}
