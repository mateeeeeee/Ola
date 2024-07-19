; ModuleID = 'test.ola'
source_filename = "test.ola"

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  store ptr inttoptr (i64 42 to ptr), ptr %0, align 8
  %1 = load i64, ptr %0, align 8
  ret i64 %1
}
