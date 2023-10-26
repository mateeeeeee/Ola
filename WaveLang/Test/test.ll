; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

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
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

switch.case1:                                     ; preds = %switch.header
  call void @Assert(i1 false)
  br label %switch.end

break:                                            ; No predecessors!
  %nop4 = alloca i1, align 1
  br label %exit

switch.case2:                                     ; preds = %switch.header
  call void @Assert(i1 true)
  br label %switch.end

break1:                                           ; No predecessors!
  %nop5 = alloca i1, align 1
  br label %exit

switch.case3:                                     ; preds = %switch.header
  call void @Assert(i1 false)
  br label %switch.end

break2:                                           ; No predecessors!
  %nop6 = alloca i1, align 1
  br label %exit

break3:                                           ; No predecessors!
  %nop7 = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %break3, %break2, %break1, %break, %return, %switch.end
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}
