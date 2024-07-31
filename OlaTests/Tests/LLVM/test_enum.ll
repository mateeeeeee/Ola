; ModuleID = 'test_enum.ola'
source_filename = "test_enum.ola"

@globalColor = internal global i64 0

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @TestEnumValues() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 2, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 2
  call void @Assert(i1 %3)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define i64 @TestEnumValuesAfterModification() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 7, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 7
  call void @Assert(i1 %3)
  %4 = alloca i64, align 8
  store i64 2, ptr %4, align 4
  %5 = load i64, ptr %4, align 4
  %6 = icmp eq i64 %5, 2
  call void @Assert(i1 %6)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}

define i64 @TestEnumSwitch() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 1, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %switch.header

switch.header:                                    ; preds = %entry
  %3 = load i64, ptr %1, align 4
  switch i64 %3, label %switch.default [
    i64 0, label %switch.case0
    i64 1, label %switch.case1
    i64 2, label %switch.case2
  ]

switch.default:                                   ; preds = %switch.header
  %nop = alloca i1, align 1
  br label %exit

switch.end:                                       ; preds = %switch.case2, %switch.case1, %switch.case0
  %4 = load i64, ptr %2, align 4
  %5 = icmp eq i64 %4, 2
  call void @Assert(i1 %5)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop3 = alloca i1, align 1
  br label %exit

switch.case0:                                     ; preds = %switch.header
  %6 = load i64, ptr %2, align 4
  store i64 1, ptr %2, align 4
  br label %switch.end

break:                                            ; No predecessors!
  %nop4 = alloca i1, align 1
  br label %exit

switch.case1:                                     ; preds = %switch.header
  %7 = load i64, ptr %2, align 4
  store i64 2, ptr %2, align 4
  br label %switch.end

break1:                                           ; No predecessors!
  %nop5 = alloca i1, align 1
  br label %exit

switch.case2:                                     ; preds = %switch.header
  %8 = load i64, ptr %2, align 4
  store i64 3, ptr %2, align 4
  br label %switch.end

break2:                                           ; No predecessors!
  %nop6 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %break2, %break1, %break, %return, %switch.default, %switch.end
  %9 = load i64, ptr %0, align 4
  ret i64 %9
}

define i64 @TestLocalEnumDeclaration() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  %3 = icmp eq i64 %2, 0
  call void @Assert(i1 %3)
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %4 = load i64, ptr %0, align 4
  ret i64 %4
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = load i64, ptr @globalColor, align 4
  %2 = icmp eq i64 %1, 0
  call void @Assert(i1 %2)
  %3 = call i64 @TestLocalEnumDeclaration()
  %4 = call i64 @TestEnumValues()
  %5 = call i64 @TestEnumValuesAfterModification()
  %6 = call i64 @TestEnumSwitch()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
