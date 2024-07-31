; ModuleID = 'test_sizeof.ola'
source_filename = "test_sizeof.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestSizeofTypes() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestSizeofExpressions() {
entry:
  %0 = alloca i64, align 8
  store i64 42, ptr %0, align 4
  %1 = alloca double, align 8
  store double 3.140000e+00, ptr %1, align 8
  %2 = alloca i1, align 1
  store i1 true, ptr %2, align 1
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestSizeofArrays() {
entry:
  %0 = alloca [5 x i64], align 8
  %1 = alloca [10 x double], align 8
  %2 = alloca [3 x i1], align 1
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestSizeofTypes()
  call void @TestSizeofExpressions()
  call void @TestSizeofArrays()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
