; ModuleID = 'test.ola'
source_filename = "test.ola"

%S = type {}

@__StringLiteral0 = internal constant [4 x i8] c"Alo\00"

declare void @PrintInt(i64)

declare void @PrintFloat(double)

declare void @PrintChar(i8)

declare void @PrintString(ptr)

declare i64 @ReadInt()

declare double @ReadFloat()

declare i8 @ReadChar()

declare void @ReadString(ptr, i64)

define void @"S::Test"(ptr %this) {
entry:
  call void @PrintString(ptr @__StringLiteral0)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %S, align 8
  call void @"S::Test"(ptr %1)
  br label %exit

exit:                                             ; preds = %entry
  %2 = load i64, ptr %0, align 4
  ret i64 %2
}
