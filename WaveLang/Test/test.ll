; ModuleID = 'WaveModule'
source_filename = "WaveModule"

define i64 @main() {
entry:
  %b = alloca i64, align 8
  store i64 10, ptr %b, align 4
  %a = alloca i64, align 8
  %b1 = load i64, ptr %b, align 4
  %subtmp = sub i64 %b1, 10
  store i64 %subtmp, ptr %a, align 4
  %a2 = load i64, ptr %a, align 4
  %ifcond = icmp ne i64 %a2, 0
  br i1 %ifcond, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %a3 = load i64, ptr %a, align 4
  %b4 = load i64, ptr %b, align 4
  %addtmp = add i64 %a3, %b4
  ret i64 %addtmp
  br label %if.end

if.else:                                          ; preds = %entry
  %a5 = load i64, ptr %a, align 4
  %b6 = load i64, ptr %b, align 4
  %subtmp7 = sub i64 %a5, %b6
  ret i64 %subtmp7
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i64 0
}
