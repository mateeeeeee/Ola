; ModuleID = 'test.wv'
source_filename = "test.wv"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store ptr inttoptr (i64 24 to ptr), ptr %0, align 8
  %1 = load i64, ptr %0, align 8
  ret i64 %1
}
