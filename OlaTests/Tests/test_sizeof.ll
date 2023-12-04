; ModuleID = 'test_sizeof.ola'
source_filename = "test_sizeof.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestSizeofTypes() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestSizeofExpressions() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestSizeofArrays() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestSizeofTypes()
  tail call void @TestSizeofExpressions()
  tail call void @TestSizeofArrays()
  ret i64 0
}
