; ModuleID = 'test.ola'
source_filename = "test.ola"

@Array = internal global [3 x i64] zeroinitializer

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = load ptr, ptr getelementptr inbounds ([3 x i64], ptr @Array, i64 0, i64 2), align 16
  store ptr %1, ptr %0, align 8
  %2 = load i64, ptr %0, align 8
  ret i64 %2
}
