#pragma once
#include <vector>
#include <string>
#include "Compiler/RTTI.h"

namespace ola
{
	class IRContext;

	enum class IRTypeKind 
	{
		Void,
		Pointer,
		Integer,
		Float,
		Array,
		Function,
		Struct,
		Label
	};

	class IRType
	{
	public:
		IRTypeKind GetKind() const { return kind; }

		uint32 GetAlign() const
		{
			return align;
		}
		uint32 GetSize() const
		{
			return size;
		}
		IRContext& GetContext() const { return ctx; }

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRContext*) { return ::operator new(sz); }

		bool IsVoidType() const { return kind == IRTypeKind::Void; }
		bool IsStructType() const { return kind == IRTypeKind::Struct; }
		bool IsPointerType() const { return kind == IRTypeKind::Pointer; }
		bool IsIntegerType() const { return kind == IRTypeKind::Integer; }
		bool IsFloatType() const { return kind == IRTypeKind::Float; }
		bool IsArrayType() const { return kind == IRTypeKind::Array; }
		bool IsFunctionType() const { return kind == IRTypeKind::Function; }
		bool IsLabelType() const { return kind == IRTypeKind::Label; }

		static bool ClassOf(IRType const* T) { return false; }

	private:
		IRTypeKind kind;
		uint32 align;
		uint32 size;
		IRContext& ctx;

	protected:
		IRType(IRContext& ctx, IRTypeKind kind)   : ctx(ctx), kind(kind), align(), size() {}
		IRType(IRContext& ctx, IRTypeKind kind, uint32 align, uint32 size) : ctx(ctx), kind(kind), align(align), size(size) {}

		void SetAlign(uint32 _align) { align = _align; }
		void SetSize(uint32 _size) { size = _size; }
	};

	class VoidType : public IRType
	{
		friend class IRContext;
	public:
		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Void; }
		static VoidType* Get(IRContext& ctx);

	private:
		explicit VoidType(IRContext& ctx) : IRType(ctx, IRTypeKind::Void, 1, 1) {}
	};

	class PointerType : public IRType
	{
		friend class IRContext;
	public:
		IRType* GetPointeeType() const { return pointee_type; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Pointer; }
		static PointerType* Get(IRType* pointee_type = nullptr);
		static PointerType* Get(IRContext& ctx, IRType* pointee_type = nullptr);

	private:
		IRType* pointee_type;

	private:
		PointerType(IRContext& ctx, IRType* pointee_type) : IRType(ctx, IRTypeKind::Pointer, 8, 8), pointee_type(pointee_type) {}
	};

	class IntegerType : public IRType
	{
		friend class IRContext;
	public:

		uint32 GetWidth() const { return width; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Integer; }
		static IntegerType* Get(IRContext& ctx, uint32 width);

	private:
		uint32 width; 

	private:
		explicit IntegerType(IRContext& ctx, uint32 width) : IRType(ctx, IRTypeKind::Integer, width, width), width(width) {}
	};

	class FloatType : public IRType
	{
		friend class IRContext;
	public:

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Float; }
		static FloatType* Get(IRContext& ctx);

	private:
		explicit FloatType(IRContext& ctx) : IRType(ctx, IRTypeKind::Float, 8, 8) {}
	};

	class ArrayType : public IRType
	{
		friend class IRContext;
	public:
		IRType* GetBaseType() const { return base_type; }
		uint32 GetArraySize() const { return array_size; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Array; }
		static ArrayType* Get(IRType* base_type, uint32 array_size);
		static ArrayType* Get(IRContext& ctx, IRType* base_type, uint32 array_size);

	private:
		IRType* base_type;
		uint32 array_size;

	private:
		ArrayType(IRContext& ctx, IRType* base_type, uint32 array_size) : IRType(ctx, IRTypeKind::Array, base_type->GetAlign(), base_type->GetSize() * array_size), base_type(base_type), array_size(array_size) {}
	};

	class FunctionType : public IRType
	{
		friend class IRContext;
	public:

		IRType* GetReturnType() const { return return_type; }
		std::vector<IRType*> const& GetParamTypes() const { return param_types; }
		uint64 GetParamCount() const { return param_types.size(); }
		IRType* GetParamType(uint32 i) const { return param_types[i]; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Function; }
		static FunctionType* Get(IRType* return_type, std::vector<IRType*> const& param_types);
		static FunctionType* Get(IRContext& ctx, IRType* return_type, std::vector<IRType*> const& param_types);

	private:
		IRType* return_type;
		std::vector<IRType*> param_types;

	private:
		FunctionType(IRContext& ctx, IRType* return_type, std::vector<IRType*> const& param_types)
			: IRType(ctx, IRTypeKind::Function, 8, 8), return_type(return_type), param_types(param_types) {}
	};

	class StructType : public IRType
	{
		friend class IRContext;
	public:

		std::string_view GetName() const { return name; }
		std::vector<IRType*> const& GetMemberTypes() const { return member_types; }
		uint64 GetMemberCount() const { return member_types.size(); }
		IRType* GetMemberType(uint32 i) const { return member_types[i]; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Struct; }
		static StructType* Get(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types);

	private:
		std::string name;
		std::vector<IRType*> member_types;
	private:
		StructType(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types);
	};

	class LabelType : public IRType
	{
		friend class IRContext;
	public:
		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Label; }
		static LabelType* Get(IRContext& ctx);

	private:
		explicit LabelType(IRContext& ctx) : IRType(ctx, IRTypeKind::Label, 0, 0) {}
	};
}