; ModuleID = 'test_shift.ola'
source_filename = "test_shift.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestShiftOperatorsIntegers() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestCompoundShiftOperatorsIntegers() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestShiftOperatorsIntegers()
  tail call void @TestCompoundShiftOperatorsIntegers()
  ret i64 0
}
