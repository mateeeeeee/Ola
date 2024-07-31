; ModuleID = 'test_bit.ola'
source_filename = "test_bit.ola"

declare void @Assert(i1)

declare void @AssertMsg(i1, ptr)

define internal void @TestIntBitwiseAnd() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 3, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = and i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 1
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %1, align 4
  %10 = and i64 %8, %9
  %11 = load i64, ptr %0, align 4
  store i64 %10, ptr %0, align 4
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 1
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestIntBitwiseOr() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 3, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = or i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 7
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %1, align 4
  %10 = or i64 %8, %9
  %11 = load i64, ptr %0, align 4
  store i64 %10, ptr %0, align 4
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 7
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestIntBitwiseXor() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = alloca i64, align 8
  store i64 3, ptr %1, align 4
  %2 = load i64, ptr %0, align 4
  %3 = load i64, ptr %1, align 4
  %4 = xor i64 %2, %3
  %5 = alloca i64, align 8
  store i64 %4, ptr %5, align 4
  %6 = load i64, ptr %5, align 4
  %7 = icmp eq i64 %6, 6
  call void @Assert(i1 %7)
  %8 = load i64, ptr %0, align 4
  %9 = load i64, ptr %1, align 4
  %10 = xor i64 %8, %9
  %11 = load i64, ptr %0, align 4
  store i64 %10, ptr %0, align 4
  %12 = load i64, ptr %0, align 4
  %13 = icmp eq i64 %12, 6
  call void @Assert(i1 %13)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestIntBitwiseNot() {
entry:
  %0 = alloca i64, align 8
  store i64 5, ptr %0, align 4
  %1 = load i64, ptr %0, align 4
  %2 = xor i64 %1, -1
  %3 = alloca i64, align 8
  store i64 %2, ptr %3, align 4
  %4 = load i64, ptr %3, align 4
  %5 = icmp eq i64 %4, -6
  call void @Assert(i1 %5)
  %6 = alloca i64, align 8
  store i64 -1, ptr %6, align 4
  %7 = load i64, ptr %6, align 4
  %8 = xor i64 %7, -1
  %9 = alloca i64, align 8
  store i64 %8, ptr %9, align 4
  %10 = load i64, ptr %9, align 4
  %11 = icmp eq i64 %10, 0
  call void @Assert(i1 %11)
  %12 = alloca i64, align 8
  store i64 0, ptr %12, align 4
  %13 = load i64, ptr %12, align 4
  %14 = xor i64 %13, -1
  %15 = alloca i64, align 8
  store i64 %14, ptr %15, align 4
  %16 = load i64, ptr %15, align 4
  %17 = icmp eq i64 %16, -1
  call void @Assert(i1 %17)
  %18 = alloca i64, align 8
  store i64 255, ptr %18, align 4
  %19 = load i64, ptr %18, align 4
  %20 = xor i64 %19, -1
  %21 = alloca i64, align 8
  store i64 %20, ptr %21, align 4
  %22 = load i64, ptr %21, align 4
  %23 = icmp eq i64 %22, -256
  call void @Assert(i1 %23)
  %24 = alloca i64, align 8
  store i64 65535, ptr %24, align 4
  %25 = load i64, ptr %24, align 4
  %26 = xor i64 %25, -1
  %27 = alloca i64, align 8
  store i64 %26, ptr %27, align 4
  %28 = load i64, ptr %27, align 4
  %29 = icmp eq i64 %28, -65536
  call void @Assert(i1 %29)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define internal void @TestBoolBitOperators() {
entry:
  %0 = alloca i1, align 1
  store i1 true, ptr %0, align 1
  %1 = alloca i1, align 1
  store i1 false, ptr %1, align 1
  %2 = load i1, ptr %0, align 1
  %3 = zext i1 %2 to i64
  %4 = load i1, ptr %1, align 1
  %5 = zext i1 %4 to i64
  %6 = and i64 %3, %5
  %7 = icmp ne i64 %6, 0
  %8 = alloca i1, align 1
  store i1 %7, ptr %8, align 1
  %9 = load i1, ptr %8, align 1
  %10 = icmp eq i1 %9, false
  call void @Assert(i1 %10)
  %11 = load i1, ptr %0, align 1
  %12 = zext i1 %11 to i64
  %13 = load i1, ptr %1, align 1
  %14 = zext i1 %13 to i64
  %15 = and i64 %12, %14
  %16 = icmp ne i64 %15, 0
  %17 = load i1, ptr %0, align 1
  store i1 %16, ptr %0, align 1
  %18 = load i1, ptr %0, align 1
  %19 = icmp eq i1 %18, false
  call void @Assert(i1 %19)
  %20 = load i1, ptr %0, align 1
  %21 = zext i1 %20 to i64
  %22 = load i1, ptr %1, align 1
  %23 = zext i1 %22 to i64
  %24 = or i64 %21, %23
  %25 = icmp ne i64 %24, 0
  %26 = alloca i1, align 1
  store i1 %25, ptr %26, align 1
  %27 = load i1, ptr %26, align 1
  %28 = icmp eq i1 %27, false
  call void @Assert(i1 %28)
  %29 = load i1, ptr %0, align 1
  %30 = zext i1 %29 to i64
  %31 = load i1, ptr %1, align 1
  %32 = zext i1 %31 to i64
  %33 = or i64 %30, %32
  %34 = icmp ne i64 %33, 0
  %35 = load i1, ptr %0, align 1
  store i1 %34, ptr %0, align 1
  %36 = load i1, ptr %0, align 1
  %37 = icmp eq i1 %36, false
  call void @Assert(i1 %37)
  %38 = load i1, ptr %0, align 1
  %39 = zext i1 %38 to i64
  %40 = load i1, ptr %1, align 1
  %41 = zext i1 %40 to i64
  %42 = xor i64 %39, %41
  %43 = icmp ne i64 %42, 0
  %44 = alloca i1, align 1
  store i1 %43, ptr %44, align 1
  %45 = load i1, ptr %44, align 1
  %46 = icmp eq i1 %45, false
  call void @Assert(i1 %46)
  %47 = load i1, ptr %0, align 1
  %48 = zext i1 %47 to i64
  %49 = load i1, ptr %1, align 1
  %50 = zext i1 %49 to i64
  %51 = xor i64 %48, %50
  %52 = icmp ne i64 %51, 0
  %53 = load i1, ptr %0, align 1
  store i1 %52, ptr %0, align 1
  %54 = load i1, ptr %0, align 1
  %55 = icmp eq i1 %54, false
  call void @Assert(i1 %55)
  %56 = load i1, ptr %0, align 1
  %57 = xor i1 %56, true
  %58 = alloca i1, align 1
  store i1 %57, ptr %58, align 1
  %59 = load i1, ptr %58, align 1
  %60 = icmp eq i1 %59, true
  call void @Assert(i1 %60)
  %61 = load i1, ptr %1, align 1
  %62 = xor i1 %61, true
  %63 = alloca i1, align 1
  store i1 %62, ptr %63, align 1
  %64 = load i1, ptr %63, align 1
  %65 = icmp eq i1 %64, true
  call void @Assert(i1 %65)
  br label %exit

exit:                                             ; preds = %entry
  ret void
}

define i64 @main() {
entry:
  %0 = alloca i64, align 8
  call void @TestIntBitwiseAnd()
  call void @TestIntBitwiseOr()
  call void @TestIntBitwiseXor()
  call void @TestIntBitwiseNot()
  call void @TestBoolBitOperators()
  store i64 0, ptr %0, align 4
  br label %exit

return:                                           ; No predecessors!
  %nop = alloca i1, align 1
  br label %exit

exit:                                             ; preds = %return, %entry
  %1 = load i64, ptr %0, align 4
  ret i64 %1
}
