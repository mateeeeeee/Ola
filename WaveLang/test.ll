; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %f = alloca i1, align 1
  store i1 false, ptr %f, align 1
  ret i64 0
}
