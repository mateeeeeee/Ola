#pragma once
#include <vector>
#include <string>

namespace ola::ir
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
		Struct
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

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRContext*) { return ::operator new(sz); }

	private:
		IRTypeKind kind;
		uint32 align;
		uint32 size;

	protected:
		explicit IRType(IRTypeKind kind) : kind(kind), align(), size() {}
		IRType(IRTypeKind kind, uint32 align, uint32 size) : kind(kind), align(align), size(size) {}

		void SetAlign(uint32 _align) { align = _align; }
		void SetSize(uint32 _size) { size = _size; }
	};

	class VoidType : public IRType
	{
		friend class IRContext;
	public:
		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Void; }
		static VoidType* Get(IRContext* ctx);

	private:
		VoidType() : IRType(IRTypeKind::Void, 1, 1) {}
	};

	class PointerType : public IRType
	{
		friend class IRContext;
	public:
		IRType* GetPointeeType() const { return pointee_type; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Pointer; }
		static PointerType* Get(IRContext* ctx, IRType* pointee_type = nullptr);

	private:
		IRType* pointee_type;

	private:
		explicit PointerType(IRType* pointee_type) : IRType(IRTypeKind::Pointer, 8, 8), pointee_type(pointee_type) {}
	};

	class IntegerType : public IRType
	{
		friend class IRContext;
	public:

		uint32 GetWidth() const { return width; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Integer; }
		static IntegerType* Get(IRContext* ctx, uint32 width);

	private:
		uint32 width; 

	private:
		explicit IntegerType(uint32 width) : IRType(IRTypeKind::Integer, width, width), width(width) {}
	};

	class FloatType : public IRType
	{
		friend class IRContext;
	public:

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Float; }
		static FloatType* Get(IRContext* ctx);

	private:
		FloatType() : IRType(IRTypeKind::Float, 8, 8) {}
	};

	class ArrayType : IRType
	{
		friend class IRContext;
	public:
		IRType* GetBaseType() const { return base_type; }
		uint32 GetArraySize() const { return array_size; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Array; }
		static ArrayType* Get(IRContext* ctx, IRType* base_type, uint32 array_size);

	private:
		IRType* base_type;
		uint32 array_size;

	private:
		ArrayType(IRType* base_type, uint32 array_size) : IRType(IRTypeKind::Array, base_type->GetAlign(), base_type->GetSize() * array_size), base_type(base_type), array_size(array_size) {}
	};

	class FunctionType : IRType
	{
		friend class IRContext;
	public:

		IRType* GetReturnType() const { return return_type; }
		std::vector<IRType*> const& GetParamTypes() const { return param_types; }
		uint64 GetParamCount() const { return param_types.size(); }
		IRType* GetParamType(uint32 i) const { return param_types[i]; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Function; }
		static FunctionType* Get(IRContext* ctx, IRType* return_type, std::vector<IRType*> const& param_types);

	private:
		IRType* return_type;
		std::vector<IRType*> param_types;

	private:
		FunctionType(IRType* return_type, std::vector<IRType*> const& param_types) 
			: IRType(IRTypeKind::Function, 8, 8), return_type(return_type), param_types(param_types) {}
	};

	class StructType : IRType
	{
		friend class IRContext;
	public:

		std::string_view GetName() const { return name; }
		std::vector<IRType*> const& GetMemberTypes() const { return member_types; }
		uint64 GetMemberCount() const { return member_types.size(); }
		IRType* GetMemberType(uint32 i) const { return member_types[i]; }

		static bool ClassOf(IRType const* T) { return T->GetKind() == IRTypeKind::Struct; }
		static StructType* Get(IRContext* ctx, std::string_view name, std::vector<IRType*> const& member_types);

	private:
		std::string name;
		std::vector<IRType*> member_types;
	private:
		StructType(std::string_view name, std::vector<IRType*> const& member_types);
	};

	template <typename T> requires std::derived_from<T, IRType>
	inline bool isa(IRType const* type) { return T::ClassOf(type); }

	template <typename T, typename... Ts> requires (std::derived_from<T, IRType> && ... && std::derived_from<Ts, IRType>)
	inline bool isoneof(IRType const* type)
	{
		return (T::ClassOf(type) || ... || Ts::ClassOf(type));
	}

	template<typename T> requires std::derived_from<T, IRType>
	inline T* cast(IRType* t)
	{
		return static_cast<T*>(t);
	}
	template<typename T> requires std::derived_from<T, IRType>
	inline T const* cast(IRType const* t)
	{
		return static_cast<T const*>(t);
	}

	template<typename T> requires std::derived_from<T, IRType>
	inline T* dyn_cast(IRType* t)
	{
		return isa<T>(t) ? static_cast<T*>(t) : nullptr;
	}
	template<typename T> requires std::derived_from<T, IRType>
	inline T const* dyn_cast(IRType const* t)
	{
		return isa<T>(t) ? static_cast<T const*>(t) : nullptr;
	}
}