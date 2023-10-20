; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 4
  %2 = alloca i64, align 8
  store i64 0, ptr %2, align 4
  br label %switch.header

switch.header:                                    ; preds = %entry
  %3 = load i64, ptr %1, align 4
  switch i64 %3, label %switch.default [
    i64 0, label %switch.case0
  ]

switch.default:                                   ; preds = %switch.header
  %4 = load i64, ptr %2, align 4
  store i64 5, ptr %2, align 4
  %5 = load ptr, ptr %2, align 8
  store ptr %5, ptr %0, align 8
  br label %exit

switch.end:                                       ; preds = %switch.case0
  %nop = alloca i1, align 1
  br label %exit

switch.case0:                                     ; preds = %switch.header
  %6 = load i64, ptr %2, align 4
  store i64 10, ptr %2, align 4
  br label %switch.end

exit:                                             ; preds = %switch.end, %switch.default
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
