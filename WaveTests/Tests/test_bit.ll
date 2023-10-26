; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  br label %exit

return:                                           ; No predecessors!
  br label %exit

exit:                                             ; preds = %return, %entry
  ret i64 0
}
