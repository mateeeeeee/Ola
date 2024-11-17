; ModuleID = 'test.ola'
source_filename = "test.ola"

@g = internal global i64 9

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store ptr @g, ptr %0, align 8
  %1 = load i64, ptr %0, align 8
  ret i64 %1
}
