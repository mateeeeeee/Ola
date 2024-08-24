; ModuleID = 'test.ola'
source_filename = "test.ola"

@Array = internal global [3 x i64] zeroinitializer

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = load i64, ptr getelementptr inbounds ([3 x i64], ptr @Array, i64 0, i64 2), align 16
  store i64 10, i64 %0, align 4
  ret i64 %0
}
