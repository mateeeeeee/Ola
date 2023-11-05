; ModuleID = 'WaveModule'
source_filename = "WaveModule"

declare void @Assert(i1)

declare i1 @IsAlnum(i8)

declare i1 @IsAlpha(i8)

declare i1 @IsLower(i8)

declare i1 @IsUpper(i8)

declare i1 @IsDigit(i8)

declare i1 @IsSpace(i8)

declare i8 @ToLower(i8)

declare i8 @ToUpper(i8)

declare double @StringToFloat(ptr)

declare i64 @StringToInteger(ptr)

declare void @StringCopy(ptr, ptr)

define i64 @main() {
entry:
  ret i64 0
}
