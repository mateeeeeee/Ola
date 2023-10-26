; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  br label %label.Label1

label.Label1:                                     ; preds = %goto, %entry
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br i1 true, label %if.then, label %if.end

label.Label2:                                     ; preds = %if.end, %if.then
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

goto:                                             ; No predecessors!
  br label %label.Label1

if.then:                                          ; preds = %label.Label1
  br label %label.Label2

if.else:                                          ; No predecessors!
  br label %exit

if.end:                                           ; preds = %label.Label1
  br label %label.Label2

goto1:                                            ; No predecessors!
  br label %exit

exit:                                             ; preds = %goto1, %if.else, %return, %label.Label2
  ret i64 0
}
