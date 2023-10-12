; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %B = alloca i64, align 8
  store i64 5, ptr %B, align 4
  %a = alloca i64, align 8
  %B1 = load i64, ptr %B, align 4
  %addtmp = add i64 %B1, 5
  %addtmp2 = add i64 %addtmp, 10
  store i64 %addtmp2, ptr %a, align 4
  %a3 = load i64, ptr %a, align 4
  %a4 = load i64, ptr %a, align 4
  %addtmp5 = add i64 %a4, 10
  store i64 %addtmp5, ptr %a, align 4
  %a6 = load i64, ptr %a, align 4
  %addtmp7 = add i64 %a6, 12
  ret i64 %addtmp7
}
