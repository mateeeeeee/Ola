; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca i64, align 8
  store i64 0, ptr %1, align 8
  br i1 true, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i64 5, ptr %1, align 8
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %2 = load ptr, ptr %1, align 8
  store ptr %2, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %if.end
  %3 = load i64, ptr %0, align 8
  ret i64 %3
}
