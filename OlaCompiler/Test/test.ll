; ModuleID = 'test.ola'
source_filename = "test.ola"

define internal i64 @add__I__I__I__I__I(i64 %a, i64 %b, i64 %c, i64 %d, i64 %e) {
entry:
  %0 = add i64 %a, %b
  %1 = add i64 %0, %c
  %2 = add i64 %1, %d
  %3 = add i64 %2, %e
  ret i64 %3
}

define i64 @main() {
entry:
  %0 = call i64 @add__I__I__I__I__I(i64 1, i64 2, i64 3, i64 4, i64 5)
  ret i64 %0
}
