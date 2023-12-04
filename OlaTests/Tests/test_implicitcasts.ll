; ModuleID = 'test_implicitcasts.ola'
source_filename = "test_implicitcasts.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestImplicitCastAssignInit() {
entry:
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 poison)
  tail call void @Assert(i1 true)
  tail call void @Assert(i1 true)
  ret void
}

define internal void @TestImplicitCastParamBool(i1 %boolParam) {
entry:
  tail call void @Assert(i1 %boolParam)
  ret void
}

define internal void @TestImplicitCastParamInt(i64 %intParam) {
entry:
  %0 = icmp eq i64 %intParam, 1
  tail call void @Assert(i1 %0)
  ret void
}

define internal void @TestImplicitCastParamFloat(double %floatParam) {
entry:
  %0 = fcmp oeq double %floatParam, 1.000000e+00
  tail call void @Assert(i1 %0)
  ret void
}

define internal void @TestImplicitCastParam() {
entry:
  tail call void @TestImplicitCastParamBool(i1 true)
  tail call void @TestImplicitCastParamBool(i1 true)
  tail call void @TestImplicitCastParamBool(i1 true)
  tail call void @TestImplicitCastParamBool(i1 true)
  tail call void @TestImplicitCastParamInt(i64 1)
  tail call void @TestImplicitCastParamInt(i64 1)
  tail call void @TestImplicitCastParamInt(i64 1)
  tail call void @TestImplicitCastParamInt(i64 1)
  tail call void @TestImplicitCastParamFloat(double 1.000000e+00)
  tail call void @TestImplicitCastParamFloat(double 1.000000e+00)
  tail call void @TestImplicitCastParamFloat(double 1.000000e+00)
  tail call void @TestImplicitCastParamFloat(double 1.000000e+00)
  ret void
}

define i64 @main() {
entry:
  tail call void @TestImplicitCastAssignInit()
  tail call void @TestImplicitCastParam()
  ret i64 0
}
