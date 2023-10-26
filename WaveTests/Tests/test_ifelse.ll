; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

define i64 @main() {
entry:
  br i1 true, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @Assert(i1 true)
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br i1 true, label %if.then1, label %if.else2

if.then1:                                         ; preds = %if.end
  call void @Assert(i1 true)
  br label %if.end3

if.else2:                                         ; preds = %if.end
  br label %if.end3

if.end3:                                          ; preds = %if.else2, %if.then1
  br i1 false, label %if.then4, label %if.else5

if.then4:                                         ; preds = %if.end3
  br label %if.end6

if.else5:                                         ; preds = %if.end3
  call void @Assert(i1 true)
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.then4
  %0 = alloca i64, align 8
  store i64 15, ptr %0, align 8
  br i1 false, label %if.then7, label %if.else8

if.then7:                                         ; preds = %if.end6
  br label %if.end9

if.else8:                                         ; preds = %if.end6
  %1 = load i64, ptr %0, align 8
  %2 = icmp slt i64 %1, 20
  br i1 %2, label %if.then10, label %if.else11

if.end9:                                          ; preds = %if.then7
  br i1 true, label %if.then13, label %if.else14

if.then10:                                        ; preds = %if.else8
  call void @Assert(i1 true)
  br label %if.end12

if.else11:                                        ; preds = %if.else8
  call void @Assert(i1 false)
  br label %if.end12

if.end12:                                         ; preds = %if.else11, %if.then10
  br label %exit

if.then13:                                        ; preds = %if.end9
  br i1 poison, label %if.then16, label %if.else17

if.else14:                                        ; preds = %if.end9
  br label %if.end15

if.end15:                                         ; preds = %if.else14
  br label %exit

return:                                           ; No predecessors!
  br label %exit

if.then16:                                        ; preds = %if.then13
  br label %if.end18

if.else17:                                        ; preds = %if.then13
  br label %if.end18

if.end18:                                         ; preds = %if.else17, %if.then16
  br label %exit

exit:                                             ; preds = %if.end18, %return, %if.end12, %if.end15
  ret i64 0
}
