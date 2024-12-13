; ModuleID = 'test.ola'
source_filename = "test.ola"

define internal i64 @f__I__I(i64 %a, i64 %b) {
entry:
  %0 = icmp slt i64 %a, %b
  br i1 %0, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %.0 = phi i64 [ %a, %if.then ], [ %b, %if.else ]
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %if.end
  ret i64 %.0
}

define i64 @main() {
entry:
  %0 = call i64 @f__I__I(i64 3, i64 4)
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  ret i64 %0
}
