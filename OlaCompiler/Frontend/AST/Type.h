#pragma once
#include <concepts>
#include <string>
#include <vector>
#include <memory>
#include <span>
#include "Utility/Enums.h"

namespace ola
{
	enum QualifierFlag : uint8
	{
		Qualifier_None = 0x0,
		Qualifier_Const = 0x1
	};
	DEFINE_ENUM_BIT_OPERATORS(QualifierFlag);
	using Qualifiers = uint8;

	class QualType
	{
		//todo: get rid of the shared_ptr -> type cache
		friend class Type;
	public:
		explicit QualType(Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers) {}
		template<typename _Ty> requires std::derived_from<_Ty, Type>
		QualType(_Ty const& _type, Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers)
		{
			type = std::make_shared<_Ty>(_type);
		}

		bool IsConst() const { return qualifiers & Qualifier_Const; }
		void AddConst() { qualifiers |= Qualifier_Const; }
		void RemoveConst() { qualifiers &= ~Qualifier_Const; }

		bool IsNull() const { return type == nullptr; }

		operator Type const& ()  const { return *type; }
		const Type& operator* () const { return *type; }
		const Type* operator->() const { return type.get(); }
		Type* operator->() { return type.get(); }

		Type* GetTypePtr() { return type.get(); }
		Type const* GetTypePtr() const { return type.get(); }

		template<typename _Ty> requires std::derived_from<_Ty, Type>
		void SetType(_Ty const& _type)
		{
			type = std::make_shared<_Ty>(_type);
		}

	private:
		std::shared_ptr<Type> type = nullptr;
		Qualifiers qualifiers = Qualifier_None;
	};

	enum class TypeKind : uint8
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
		constexpr Type() {}

		constexpr uint32 GetSize() const { return size; }
		constexpr uint32 GetAlign() const { return align; }
		constexpr void SetAlign(uint32 _align) { align = _align; }
		constexpr void SetSize(uint32 _size) { size = _size; }

		virtual bool IsSameAs(Type const& t) const
		{
			return kind == t.kind;
		}
		virtual bool IsAssignableFrom(Type const&) const { return true; }

		TypeKind GetKind() const { return kind; }
		bool Is(TypeKind t) const { return kind == t; }
		bool IsNot(TypeKind t) const { return kind != t; }
		template <typename... Ts>
		bool IsOneOf(TypeKind t1, Ts... ts) const
		{
			if constexpr (sizeof...(Ts) == 0) return Is(t1);
			else return Is(t1) || IsOneOf(ts...);
		}

	private:
		TypeKind kind = TypeKind::Invalid;
		uint32 size = 0;
		uint32 align = 0;

	protected:
		constexpr Type(TypeKind kind, uint32 size = 0, uint32 align = 0)
			: kind(kind), size(size), align(align) {}
	};

	class RefType : public Type
	{
	public:
		explicit RefType(QualType const& type) :Type(TypeKind::Ref, 8, 8), type(type) {}

		QualType const& GetReferredType() const { return type; }

		virtual bool IsAssignableFrom(Type const& other) const override;
		virtual bool IsSameAs(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Ref; }
	private:
		QualType type;
	};

	class VoidType : public Type
	{
	public:
		constexpr VoidType() : Type{ TypeKind::Void } {}
		virtual bool IsAssignableFrom(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Void; }
	};

	class BoolType : public Type
	{
	public:
		constexpr BoolType() : Type{ TypeKind::Bool, 1, 1 } {}
		virtual bool IsAssignableFrom(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Bool; }
	};

	class CharType : public Type
	{
	public:
		constexpr CharType() : Type{ TypeKind::Char, 1, 1 } {}
		virtual bool IsAssignableFrom(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Char; }
	};

	class IntType : public Type
	{
	public:
		constexpr IntType() : Type{ TypeKind::Int, 8, 8 } {}
		virtual bool IsAssignableFrom(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Int; }
	};

	class FloatType : public Type
	{
	public:
		constexpr FloatType() : Type{ TypeKind::Float, 8, 8 } {}
		virtual bool IsAssignableFrom(Type const& other) const override;

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Float; }
	};

	class ArrayType : public Type
	{
	public:
		explicit ArrayType(QualType const& type) : Type{ TypeKind::Array, 0, type->GetAlign() }, base_type(type) {}
		ArrayType(QualType const& type, uint32 array_size) : Type{ TypeKind::Array, array_size * type->GetSize(), type->GetAlign() },
			base_type(type), array_size(array_size) {}

		virtual bool IsAssignableFrom(Type const& other) const override;
		virtual bool IsSameAs(Type const& other) const override;

		QualType const& GetBaseType() const { return base_type; }
		uint32 GetArraySize() const { return array_size; }

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Array; }
	private:
		QualType base_type;
		uint32 array_size = 0;
	};

	class FuncType : public Type
	{
	public:
		explicit FuncType(QualType const& return_type, std::vector<QualType> const& param_types = {})
			: Type{ TypeKind::Function, 8, 8 }, return_type(return_type), param_types(param_types){}

		virtual bool IsAssignableFrom(Type const& other) const override;

		QualType const& GetReturnType() const { return return_type; }
		std::span<QualType const> GetParams() const { return param_types; }
		uint64 GetParamCount() const { return param_types.size(); }
		QualType const& GetParamType(uint64 i) const { return param_types[i]; }

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Function; }
	private:
		QualType return_type;
		std::vector<QualType> param_types;
	};

	class ClassDecl;
	class ClassType : public Type
	{
	public:
		ClassType(ClassDecl const* class_decl);

		virtual bool IsAssignableFrom(Type const& other) const override;
		virtual bool IsSameAs(Type const& other) const override;

		ClassDecl const* GetClassDecl() const { return class_decl; }

		static bool ClassOf(Type const* T) { return T->GetKind() == TypeKind::Class; }
	private:
		ClassDecl const* class_decl;
	};


	template <typename T> requires std::derived_from<T, Type>
	inline bool isa(Type const& type) { return T::ClassOf(&type); }

	template <typename T, typename... Ts> requires (std::derived_from<T, Type> && ... && std::derived_from<Ts, Type>)
	inline bool isoneof(Type const& type) 
	{ 
		return (T::ClassOf(&type) || ... || Ts::ClassOf(&type));
	}

	template<typename T> requires std::derived_from<T, Type>
	inline T& type_cast(Type& t)
	{
		return static_cast<T&>(t);
	}
	template<typename T> requires std::derived_from<T, Type>
	inline T const& type_cast(Type const& t)
	{
		return static_cast<T const&>(t);
	}

	template<typename T> requires std::derived_from<T, Type>
	inline T* dyn_type_cast(Type& t)
	{
		return isa<T>(t) ? static_cast<T*>(&t) : nullptr;
	}
	template<typename T> requires std::derived_from<T, Type>
	inline T const* dyn_type_cast(Type const& t)
	{
		return isa<T>(t) ? static_cast<T const*>(&t) : nullptr;
	}

	template<TypeKind K>
	inline bool IsType(Type const& type)
	{
		return type.Is(K);
	}
	template<TypeKind K, TypeKind... Ks>
	inline bool IsTypeOneOf(Type const& type)
	{
		return type.IsOneOf(K, Ks...);
	}

	inline bool (*IsVoidType)(Type const& type) = IsType<TypeKind::Void>;
	inline bool (*IsArrayType)(Type const& type) = IsType<TypeKind::Array>;
	inline bool (*IsIntegerType)(Type const& type) = IsType<TypeKind::Int>;
	inline bool (*IsBoolType)(Type const& type) = IsType<TypeKind::Bool>;
	inline bool (*IsCharType)(Type const& type) = IsType<TypeKind::Char>;
	inline bool (*IsFloatType)(Type const& type) = IsType<TypeKind::Float>;
	inline bool (*IsFunctionType)(Type const& type) = IsType<TypeKind::Function>;
	inline bool (*IsClassType)(Type const& type) = IsType<TypeKind::Class>;
	inline bool (*IsIntegralType)(Type const& type) = IsTypeOneOf<TypeKind::Int, TypeKind::Bool>;
	inline bool (*IsRefType)(Type const& type) = IsType<TypeKind::Ref>;

	namespace builtin_types
	{
		static constexpr VoidType  Void = VoidType();
		static constexpr BoolType  Bool = BoolType();
		static constexpr CharType  Char = CharType();
		static constexpr IntType   Int = IntType();
		static constexpr FloatType Float = FloatType();
		static constexpr IntType   Enum = Int;
	}

}