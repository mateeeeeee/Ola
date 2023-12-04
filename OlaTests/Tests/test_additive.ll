; ModuleID = 'test_additive.ola'
source_filename = "test_additive.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIntAddition() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIntSubtraction() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestFloatAddition() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestFloatSubtraction() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestIntAddition()
  tail call void @TestIntSubtraction()
  tail call void @TestFloatAddition()
  tail call void @TestFloatSubtraction()
  ret i64 0
}
