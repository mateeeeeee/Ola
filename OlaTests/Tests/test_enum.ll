; ModuleID = 'test_enum.ola'
source_filename = "test_enum.ola"

@globalColor = internal global i64 0

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @TestEnumValues() {
entry:
  tail call void @Assert(i1 true)
  ret i64 0
}

define i64 @TestEnumValuesAfterModification() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret i64 0
}

define i64 @TestEnumSwitch() {
entry:
  tail call void @Assert(i1 true)
  ret i64 0
}

define i64 @TestLocalEnumDeclaration() {
entry:
  tail call void @Assert(i1 true)
  ret i64 0
}

define i64 @main() {
entry:
  %0 = load i64, ptr @globalColor, align 8
  %1 = icmp eq i64 %0, 0
  tail call void @Assert(i1 %1)
  %2 = tail call i64 @TestLocalEnumDeclaration()
  %3 = tail call i64 @TestEnumValues()
  %4 = tail call i64 @TestEnumValuesAfterModification()
  %5 = tail call i64 @TestEnumSwitch()
  ret i64 0
}
