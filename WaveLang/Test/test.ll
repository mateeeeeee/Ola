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
  %addtmp = add i64 %a2, 1
  %ifcond = icmp ne i64 %addtmp, 0
  br i1 %ifcond, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %a3 = load i64, ptr %a, align 4
  %a4 = load i64, ptr %a, align 4
  %addtmp5 = add i64 %a4, 5
  store i64 %addtmp5, ptr %a, align 4
  %a6 = load i64, ptr %a, align 4
  %a7 = load i64, ptr %a, align 4
  %multmp = mul i64 %a6, %a7
  ret i64 %multmp
  br label %if.end

if.else:                                          ; preds = %entry
  %b8 = load i64, ptr %b, align 4
  %b9 = load i64, ptr %b, align 4
  %addtmp10 = add i64 %b9, 5
  store i64 %addtmp10, ptr %b, align 4
  %b11 = load i64, ptr %b, align 4
  %b12 = load i64, ptr %b, align 4
  %multmp13 = mul i64 %b11, %b12
  ret i64 %multmp13
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i64 0
}
