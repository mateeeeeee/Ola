#pragma once
#include <concepts>
#include <string>
#include <vector>
#include <memory>
#include <span>
#include "Utility/RTTI.h"
#include "Utility/EnumOperators.h"


namespace ola
{
	class FrontendContext;

	enum QualifierFlag : Uint8
	{
		Qualifier_None = 0x0,
		Qualifier_Const = 0x1
	};
	ENABLE_ENUM_BIT_OPERATORS(QualifierFlag);

	using Qualifiers = Uint8;

	class Type;
	class QualType
	{
		friend class Type;
	public:
		explicit QualType(Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers) {}
		QualType(Type const* _type, Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers)
		{
			type = _type;
		}

		Bool IsConst() const { return qualifiers & Qualifier_Const; }
		void AddConst() { qualifiers |= Qualifier_Const; }
		void RemoveConst() { qualifiers &= ~Qualifier_Const; }

		Bool IsNull() const { return type == nullptr; }

		const Type& operator* () const { return *type; }
		operator Type const* ()  const { return type; }
		Type const* operator->() const { return type; }
		Type const* GetTypePtr() const { return type; }

		void SetType(Type const* _type)
		{
			type = _type;
		}

		Bool operator==(QualType const& o) const;
		Bool operator!=(QualType const& o) const
		{
			return !(*this == o);
		}

	private:
		Type const* type = nullptr;
		Qualifiers qualifiers = Qualifier_None;
	};

	enum class TypeKind : Uint8
	{
		Invalid,
		Void,
		Ref,
		Bool,
		Char,
		Int,
		Float,
		Class,
		Array,
		Function,
	};

	class Type
	{
	public:
        virtual ~Type() = default;
		constexpr Type() {}
		constexpr Uint32 GetSize() const { return size; }
		constexpr Uint32 GetAlign() const { return align; }
		TypeKind GetKind() const { return kind; }

		void* operator new(std::size_t) = delete;
		void* operator new(std::size_t sz, FrontendContext*) { return ::operator new(sz); }

		virtual Bool IsAssignableFrom(Type const*) const { return true; }

	private:
		TypeKind kind = TypeKind::Invalid;
		Uint32 size = 0;
		Uint32 align = 0;

	protected:
		constexpr Type(TypeKind kind, Uint32 size = 0, Uint32 align = 0) : kind(kind), size(size), align(align) {}
		constexpr void SetAlign(Uint32 _align) { align = _align; }
		constexpr void SetSize(Uint32 _size)   { size = _size; }
	};

	class RefType : public Type
	{
		friend class FrontendContext;
	public:
		QualType const& GetReferredType() const { return type; }

		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Ref; }
		static RefType* Get(FrontendContext* ctx, QualType const& type);
	private:
		QualType type;

	private:
		explicit RefType(QualType const& type) :Type(TypeKind::Ref, 8, 8), type(type) {}
	};

	class VoidType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Void; }
		static VoidType* Get(FrontendContext* ctx);
	private:
		constexpr VoidType() : Type{ TypeKind::Void } {}
	};

	class BoolType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Bool; }
		static BoolType* Get(FrontendContext* ctx);
	private:
		constexpr BoolType() : Type{ TypeKind::Bool, 1, 1 } {}
	};

	class CharType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Char; }
		static CharType* Get(FrontendContext* ctx);
	private:
		constexpr CharType() : Type{ TypeKind::Char, 1, 1 } {}
	};

	class IntType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Int; }
		static IntType* Get(FrontendContext* ctx);
	private:
		constexpr IntType() : Type{ TypeKind::Int, 8, 8 } {}
	};

	class FloatType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Float; }
		static FloatType* Get(FrontendContext* ctx);
	private:
		constexpr FloatType() : Type{ TypeKind::Float, 8, 8 } {}
	};

	class ArrayType : public Type
	{
		friend class FrontendContext;
	public:

		virtual Bool IsAssignableFrom(Type const*) const override;

		QualType const& GetElementType() const { return element_type; }
		Uint32 GetArraySize() const { return array_size; }

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Array; }
		static ArrayType* Get(FrontendContext* ctx, QualType const& type, Uint32 array_size = 0);
	private:
		QualType element_type;
		Uint32 array_size;

	private:
		ArrayType(QualType const& type, Uint32 array_size) : Type{ TypeKind::Array, array_size * type->GetSize(), type->GetAlign() },
			element_type(type), array_size(array_size) {}
	};

	class FuncType : public Type
	{
		friend class FrontendContext;
	public:
		
		virtual Bool IsAssignableFrom(Type const*) const override;

		QualType const& GetReturnType() const { return return_type; }
		std::span<QualType const> GetParams() const { return param_types; }
		Uint64 GetParamCount() const { return param_types.size(); }
		QualType const& GetParamType(Uint64 i) const { return param_types[i]; }

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Function; }
		static FuncType* Get(FrontendContext* ctx, QualType const& return_type, std::vector<QualType> const& param_types = {});
	private:
		QualType return_type;
		std::vector<QualType> param_types;

	private:
		explicit FuncType(QualType const& return_type, std::vector<QualType> const& param_types = {})
			: Type{ TypeKind::Function, 8, 8 }, return_type(return_type), param_types(param_types) {}
	};

	class ClassDecl;
	class ClassType : public Type
	{
		friend class FrontendContext;
	public:
		virtual Bool IsAssignableFrom(Type const*) const override;

		ClassDecl const* GetClassDecl() const { return class_decl; }

		static Bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Class; }
		static ClassType* Get(FrontendContext* ctx, ClassDecl const* class_decl);
	private:
		ClassDecl const* class_decl;

	private:
		ClassType(ClassDecl const* class_decl);
	};


	template<typename T> requires std::derived_from<T, Type>
	inline Bool isa(QualType const& qtype)
	{
		return isa<T>(qtype.GetTypePtr());
	}

	template <typename... Ts> requires (std::derived_from<Ts, Type> && ...)
	inline Bool isoneof(QualType const& qtype) { return (Bool(isa<Ts>(qtype)) || ...); }

	template<typename T> requires std::derived_from<T, Type>
	inline auto cast(QualType& qtype)
	{
		return cast<T>(qtype.GetTypePtr());
	}
	template<typename T> requires std::derived_from<T, Type>
	inline auto cast(QualType const& qtype)
	{
		return cast<T>(qtype.GetTypePtr());
	}
	template<typename T> requires std::derived_from<T, Type>
	inline auto dyn_cast(QualType& qtype)
	{
		return dyn_cast<T>(qtype.GetTypePtr());
	}
	template<typename T> requires std::derived_from<T, Type>
	inline auto dyn_cast(QualType const& qtype)
	{
		return dyn_cast<T>(qtype.GetTypePtr());
	}

}
