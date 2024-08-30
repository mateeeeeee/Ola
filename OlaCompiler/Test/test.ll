; ModuleID = 'test.ola'
source_filename = "test.ola"

@GlobalInt = internal global i64 7
@GlobalFloat = internal global double 1.400000e+01

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define i64 @main() {
entry:
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  %0 = load i64, ptr @GlobalInt, align 8
  %1 = icmp eq i64 %0, 7
  call void @Assert(i1 %1)
  %2 = load double, ptr @GlobalFloat, align 8
  %3 = fcmp oeq double %2, 1.400000e+01
  call void @Assert(i1 %3)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  call void @Assert(i1 true)
  ret i64 0
}
