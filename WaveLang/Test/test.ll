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
    i64 1, label %switch.case1
  ]

switch.default:                                   ; preds = %switch.case1, %switch.header
  %4 = load i64, ptr %2, align 4
  store i64 5, ptr %2, align 4
  br label %switch.end

switch.end:                                       ; preds = %switch.default
  %5 = load ptr, ptr %2, align 8
  store ptr %5, ptr %0, align 8
  br label %exit

switch.case0:                                     ; preds = %switch.header
  %6 = load i64, ptr %2, align 4
  store i64 10, ptr %2, align 4
  br label %switch.case1

switch.case1:                                     ; preds = %switch.case0, %switch.header
  %7 = load i64, ptr %2, align 4
  store i64 15, ptr %2, align 4
  br label %switch.default

exit:                                             ; preds = %switch.end
  %8 = load i64, ptr %0, align 4
  ret i64 %8
}
