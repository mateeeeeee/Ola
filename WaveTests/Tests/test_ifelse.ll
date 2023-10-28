; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret i64 0
}
