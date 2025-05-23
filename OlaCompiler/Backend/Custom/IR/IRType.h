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

		Uint32 GetAlign() const
		{
			return align;
		}
		Uint32 GetSize() const
		{
			return size;
		}
		IRContext& GetContext() const { return ctx; }

		void* operator new(Uint64) = delete;
		void* operator new(Uint64 sz, IRContext*) { return ::operator new(sz); }

		Bool IsVoid() const { return kind == IRTypeKind::Void; }
		Bool IsStruct() const { return kind == IRTypeKind::Struct; }
		Bool IsPointer() const { return kind == IRTypeKind::Pointer; }
		Bool IsInteger() const { return kind == IRTypeKind::Integer; }
		Bool IsBoolean() const { return kind == IRTypeKind::Integer && size == 1; }
		Bool IsFloat() const { return kind == IRTypeKind::Float; }
		Bool IsArray() const { return kind == IRTypeKind::Array; }
		Bool IsFunction() const { return kind == IRTypeKind::Function; }
		Bool IsLabel() const { return kind == IRTypeKind::Label; }

		static Bool ClassOf(IRType const* T) { return false; }

	private:
		IRTypeKind kind;
		Uint32 align;
		Uint32 size;
		IRContext& ctx;

	protected:
		IRType(IRContext& ctx, IRTypeKind kind)   : ctx(ctx), kind(kind), align(), size() {}
		IRType(IRContext& ctx, IRTypeKind kind, Uint32 align, Uint32 size) : ctx(ctx), kind(kind), align(align), size(size) {}

		void SetAlign(Uint32 _align) { align = _align; }
		void SetSize(Uint32 _size) { size = _size; }
	};

	class IRVoidType : public IRType
	{
		friend class IRContext;
	public:
		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Void; }
		static IRVoidType* Get(IRContext& ctx);

	private:
		explicit IRVoidType(IRContext& ctx) : IRType(ctx, IRTypeKind::Void, 1, 1) {}
	};

	class IRPtrType : public IRType
	{
		friend class IRContext;
	public:
		IRType* GetPointeeType() const { return pointee_type; }

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Pointer; }
		static IRPtrType* Get(IRType* pointee_type = nullptr);
		static IRPtrType* Get(IRContext& ctx, IRType* pointee_type = nullptr);

	private:
		IRType* pointee_type;

	private:
		IRPtrType(IRContext& ctx, IRType* pointee_type) : IRType(ctx, IRTypeKind::Pointer, 8, 8), pointee_type(pointee_type) {}
	};

	class IRIntType : public IRType
	{
		friend class IRContext;
	public:

		Uint32 GetWidth() const { return width; }

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Integer; }
		static IRIntType* Get(IRContext& ctx, Uint32 width);

	private:
		Uint32 width; 

	private:
		explicit IRIntType(IRContext& ctx, Uint32 width) : IRType(ctx, IRTypeKind::Integer, width, width), width(width) {}
	};

	class IRFloatType : public IRType
	{
		friend class IRContext;
	public:

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Float; }
		static IRFloatType* Get(IRContext& ctx);

	private:
		explicit IRFloatType(IRContext& ctx) : IRType(ctx, IRTypeKind::Float, 8, 8) {}
	};

	class IRArrayType : public IRType
	{
		friend class IRContext;
	public:
		IRType* GetElementType() const { return element_type; }
		Uint32 GetArraySize() const { return array_size; }

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Array; }
		static IRArrayType* Get(IRType* base_type, Uint32 array_size);
		static IRArrayType* Get(IRContext& ctx, IRType* base_type, Uint32 array_size);

	private:
		IRType* element_type;
		Uint32 array_size;

	private:
		IRArrayType(IRContext& ctx, IRType* element_type, Uint32 array_size) : IRType(ctx, IRTypeKind::Array, element_type->GetAlign(), element_type->GetSize() * array_size), element_type(element_type), array_size(array_size) {}
	};

	class IRFuncType : public IRType
	{
		friend class IRContext;
	public:

		IRType* GetReturnType() const { return return_type; }
		std::vector<IRType*> const& GetParamTypes() const { return param_types; }
		Uint32 GetParamCount() const { return (Uint32)param_types.size(); }
		IRType* GetParamType(Uint32 i) const { return param_types[i]; }

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Function; }
		static IRFuncType* Get(IRType* return_type, std::vector<IRType*> const& param_types);
		static IRFuncType* Get(IRContext& ctx, IRType* return_type, std::vector<IRType*> const& param_types);

	private:
		IRType* return_type;
		std::vector<IRType*> param_types;

	private:
		IRFuncType(IRContext& ctx, IRType* return_type, std::vector<IRType*> const& param_types)
			: IRType(ctx, IRTypeKind::Function, 8, 8), return_type(return_type), param_types(param_types) {}
	};

	class IRStructType : public IRType
	{
		friend class IRContext;
	public:

		std::string_view GetName() const { return name; }
		std::vector<IRType*> const& GetMemberTypes() const { return member_types; }
		Uint64 GetMemberCount() const { return member_types.size(); }
		IRType* GetMemberType(Uint32 i) const { return member_types[i]; }

		Uint32 GetFieldOffset(Uint32 i) const
		{
			OLA_ASSERT(false);
			return 0; 
		}

		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Struct; }
		static IRStructType* Get(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types);

	private:
		std::string name;
		std::vector<IRType*> member_types;
	private:
		IRStructType(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types);
	};

	class IRLabelType : public IRType
	{
		friend class IRContext;
	public:
		static Bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Label; }
		static IRLabelType* Get(IRContext& ctx);

	private:
		explicit IRLabelType(IRContext& ctx) : IRType(ctx, IRTypeKind::Label, 0, 0) {}
	};
}