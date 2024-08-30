; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalInt = internal global i64 7

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = load i64, ptr @GlobalInt, align 8
  ret i64 %0
}
