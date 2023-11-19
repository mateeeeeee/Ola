; ModuleID = 'WaveModule'
source_filename = "WaveModule"

%Foo = type { i64 }
%Foo.0 = type { i64 }
%Foo.1 = type { i64 }

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  %1 = alloca %Foo, align 8
  %2 = getelementptr inbounds %Foo, ptr %1, i32 0, i32 0
  store i64 5, ptr %2, align 4
  %3 = getelementptr inbounds %Foo.0, ptr %1, i32 0, i32 0
  %4 = load i64, ptr %3, align 4
  store i64 10, ptr %3, align 4
  %5 = getelementptr inbounds %Foo.1, ptr %1, i32 0, i32 0
  %6 = load ptr, ptr %5, align 8
  store ptr %6, ptr %0, align 8
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %7 = load i64, ptr %0, align 4
  ret i64 %7
}
