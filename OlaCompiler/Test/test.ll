; ModuleID = 'test.ola'
source_filename = "test.ola"

define internal i64 @add__I__I(i64 %a, i64 %b) {
entry:
  %0 = add i64 %a, %b
  ret i64 %0
}

define i64 @main() {
entry:
  %0 = call i64 @add__I__I(i64 5, i64 7)
  %1 = add i64 %0, 10
  ret i64 %1
}
