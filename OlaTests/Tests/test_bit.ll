; ModuleID = 'test_bit.ola'
source_filename = "test_bit.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIntBitwiseAnd() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIntBitwiseOr() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIntBitwiseXor() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestIntBitwiseNot() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestBoolBitOperators() {
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
  tail call void @TestIntBitwiseAnd()
  tail call void @TestIntBitwiseOr()
  tail call void @TestIntBitwiseXor()
  tail call void @TestIntBitwiseNot()
  tail call void @TestBoolBitOperators()
  ret i64 0
}
