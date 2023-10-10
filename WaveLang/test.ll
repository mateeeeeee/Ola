; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %B = alloca i64, align 8
  store i64 5, ptr %B, align 4
  %a = alloca i64, align 8
  %addtmp = add ptr %B, i64 3
  store ptr %addtmp, ptr %a, align 8
  ret void
}
