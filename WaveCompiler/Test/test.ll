; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%Foo = type { i64 }

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Foo, align 8
  %2 = getelementptr inbounds %Foo, ptr %1, i32 0, i32 0
  store i64 5, ptr %2, align 4
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %3 = load i64, ptr %0, align 4
  ret i64 %3
}
