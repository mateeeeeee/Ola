; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %B = alloca i64, align 8
  store i64 5, ptr %B, align 4
  %a = alloca i64, align 8
  %B1 = load i64, ptr %B, align 4
  %addtmp = add i64 %B1, 5
  store i64 %addtmp, ptr %a, align 4
  %a2 = load i64, ptr %a, align 4
  ret i64 %a2
}
