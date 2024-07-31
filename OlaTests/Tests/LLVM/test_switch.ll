; ModuleID = 'test_switch.ola'
source_filename = "test_switch.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 2, ptr %1, align 4
  br label %switch.header

switch.header:                                    ; preds = %entry
  %2 = load i64, ptr %1, align 4
  switch i64 %2, label %switch.default [
    i64 1, label %switch.case1
    i64 2, label %switch.case2
    i64 3, label %switch.case3
  ]

switch.default:                                   ; preds = %switch.header
  call void @Assert(i1 false)
  br label %switch.end

switch.end:                                       ; preds = %switch.default, %switch.case3, %switch.case2, %switch.case1
  %3 = alloca i64, align 8
  store i64 1, ptr %3, align 4
  br label %switch.header4

switch.case1:                                     ; preds = %switch.header
  call void @Assert(i1 false)
  br label %switch.end

break:                                            ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

switch.case2:                                     ; preds = %switch.header
  call void @Assert(i1 true)
  br label %switch.end

break1:                                           ; No predecessors!
  %nop23 = alloca i1, align 1
  br label %exit

switch.case3:                                     ; preds = %switch.header
  call void @Assert(i1 false)
  br label %switch.end

break2:                                           ; No predecessors!
  %nop24 = alloca i1, align 1
  br label %exit

break3:                                           ; No predecessors!
  %nop25 = alloca i1, align 1
  br label %exit

switch.header4:                                   ; preds = %switch.end
  %4 = load i64, ptr %3, align 4
  switch i64 %4, label %switch.default5 [
    i64 1, label %switch.case17
    i64 2, label %switch.case28
    i64 3, label %switch.case310
  ]

switch.default5:                                  ; preds = %switch.header4
  call void @Assert(i1 false)
  br label %switch.end6

switch.end6:                                      ; preds = %switch.default5, %switch.case310, %switch.case28
  %5 = alloca i64, align 8
  store i64 5, ptr %5, align 4
  br label %switch.header13

switch.case17:                                    ; preds = %switch.header4
  call void @Assert(i1 true)
  br label %switch.case28

switch.case28:                                    ; preds = %switch.case17, %switch.header4
  call void @Assert(i1 true)
  br label %switch.end6

break9:                                           ; No predecessors!
  %nop26 = alloca i1, align 1
  br label %exit

switch.case310:                                   ; preds = %switch.header4
  call void @Assert(i1 false)
  br label %switch.end6

break11:                                          ; No predecessors!
  %nop27 = alloca i1, align 1
  br label %exit

break12:                                          ; No predecessors!
  %nop28 = alloca i1, align 1
  br label %exit

switch.header13:                                  ; preds = %switch.end6
  %6 = load i64, ptr %5, align 4
  switch i64 %6, label %switch.default14 [
    i64 1, label %switch.case116
    i64 2, label %switch.case218
    i64 3, label %switch.case320
  ]

switch.default14:                                 ; preds = %switch.header13
  call void @Assert(i1 true)
  br label %switch.end15

switch.end15:                                     ; preds = %switch.default14, %switch.case320, %switch.case218, %switch.case116
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop29 = alloca i1, align 1
  br label %exit

switch.case116:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break17:                                          ; No predecessors!
  %nop30 = alloca i1, align 1
  br label %exit

switch.case218:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break19:                                          ; No predecessors!
  %nop31 = alloca i1, align 1
  br label %exit

switch.case320:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break21:                                          ; No predecessors!
  %nop32 = alloca i1, align 1
  br label %exit

break22:                                          ; No predecessors!
  %nop33 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %break22, %break21, %break19, %break17, %return, %break12, %break11, %break9, %break3, %break2, %break1, %break, %switch.end15
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
