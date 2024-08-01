; ModuleID = 'test.ola'
source_filename = "test.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestLessThanOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestLessThanOrEqualOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestGreaterThanOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestGreaterThanOrEqualOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestEqualOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define internal void @TestNotEqualOperators() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret void
}

define i64 @main() {
entry:
  call void @TestLessThanOperators()
  call void @TestLessThanOrEqualOperators()
  call void @TestGreaterThanOperators()
  call void @TestGreaterThanOrEqualOperators()
  call void @TestEqualOperators()
  call void @TestNotEqualOperators()
  ret i64 0
}
