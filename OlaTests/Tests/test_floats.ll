; ModuleID = 'WaveModule'
source_filename = "WaveModule"

@globalFloat = internal constant double 1.000000e+01

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret i64 0
}
