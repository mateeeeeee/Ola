; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  br label %switch.header

switch.header:                                    ; preds = %entry
  switch i2 -2, label %switch.default [
    i2 1, label %switch.case1
    i2 -2, label %switch.case2
    i2 -1, label %switch.case3
  ]

switch.default:                                   ; preds = %switch.header
  br label %switch.end

switch.end:                                       ; preds = %switch.default, %switch.case3, %switch.case2, %switch.case1
  %0 = alloca i64, align 8
  store i64 1, ptr %0, align 8
  br label %switch.header4

switch.case1:                                     ; preds = %switch.header
  br label %switch.end

break:                                            ; No predecessors!
  br label %exit

switch.case2:                                     ; preds = %switch.header
  call void @Assert(i1 true)
  br label %switch.end

break1:                                           ; No predecessors!
  br label %exit

switch.case3:                                     ; preds = %switch.header
  br label %switch.end

break2:                                           ; No predecessors!
  br label %exit

break3:                                           ; No predecessors!
  br label %exit

switch.header4:                                   ; preds = %switch.end
  %1 = load i64, ptr %0, align 8
  switch i64 %1, label %switch.default5 [
    i64 1, label %switch.case17
    i64 2, label %switch.case28
    i64 3, label %switch.case310
  ]

switch.default5:                                  ; preds = %switch.header4
  call void @Assert(i1 false)
  br label %switch.end6

switch.end6:                                      ; preds = %switch.default5, %switch.case310, %switch.case28
  %2 = alloca i64, align 8
  store i64 5, ptr %2, align 8
  br label %switch.header13

switch.case17:                                    ; preds = %switch.header4
  call void @Assert(i1 true)
  br label %switch.case28

switch.case28:                                    ; preds = %switch.case17, %switch.header4
  call void @Assert(i1 true)
  br label %switch.end6

break9:                                           ; No predecessors!
  br label %exit

switch.case310:                                   ; preds = %switch.header4
  call void @Assert(i1 false)
  br label %switch.end6

break11:                                          ; No predecessors!
  br label %exit

break12:                                          ; No predecessors!
  br label %exit

switch.header13:                                  ; preds = %switch.end6
  %3 = load i64, ptr %2, align 8
  switch i64 %3, label %switch.default14 [
    i64 1, label %switch.case116
    i64 2, label %switch.case218
    i64 3, label %switch.case320
  ]

switch.default14:                                 ; preds = %switch.header13
  call void @Assert(i1 true)
  br label %switch.end15

switch.end15:                                     ; preds = %switch.default14, %switch.case320, %switch.case218, %switch.case116
  br label %exit

return:                                           ; No predecessors!
  br label %exit

switch.case116:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break17:                                          ; No predecessors!
  br label %exit

switch.case218:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break19:                                          ; No predecessors!
  br label %exit

switch.case320:                                   ; preds = %switch.header13
  call void @Assert(i1 false)
  br label %switch.end15

break21:                                          ; No predecessors!
  br label %exit

break22:                                          ; No predecessors!
  br label %exit

exit:                                             ; preds = %break22, %break21, %break19, %break17, %return, %break12, %break11, %break9, %break3, %break2, %break1, %break, %switch.end15
  ret i64 0
}
