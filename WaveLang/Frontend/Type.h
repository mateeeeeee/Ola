#pragma once
#include <concepts>
#include <string>
#include <vector>
#include <memory>
#include <span>
#include "Utility/Enums.h"

namespace wave
{
	enum class TypeKind : uint8
	{
		Invalid,
		Void,
		Bool,
		Char,
		Int,
		Float,
		Function,
		Array,
		Class
	};

	class Type
	{
	public:
		constexpr Type() {}

		constexpr uint32 GetSize() const { return size; }
		constexpr uint32 GetAlign() const { return align; }
		constexpr void SetAlign(uint32 _align) { align = _align; }
		constexpr void SetSize(uint32 _size) { size = _size; }

		virtual bool IsCompatible(Type const& other) const { return true; }

		TypeKind GetKind() const { return kind; }
		bool Is(TypeKind t) const { return kind == t; }
		bool IsNot(TypeKind t) const { return kind != t; }
		template <typename... Ts>
		bool IsOneOf(TypeKind t1, Ts... ts) const
		{
			if constexpr (sizeof...(Ts) == 0) return Is(t1);
			else return Is(t1) || IsOneOf(ts...);
		}

		template<typename T>
		T const& As() const;
		template<typename T>
		T& As();

		template<typename T>
		T const* TryAs() const;
		template<typename T>
		T* TryAs();

	private:
		TypeKind kind = TypeKind::Invalid;
		uint32 size = 0;
		uint32 align = 0;

	protected:
		constexpr Type(TypeKind kind, uint32 size = 0, uint32 align = 0)
			: kind(kind), size(size), align(align) {}
	};


	enum QualifierFlag : uint8
	{
		Qualifier_None = 0x0,
		Qualifier_Const = 0x1
	};
	DEFINE_ENUM_BIT_OPERATORS(QualifierFlag);
	using Qualifiers = uint8;

	class QualifiedType
	{
		friend class Type;
	public:
		explicit QualifiedType(Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers) {}
		template<typename _Ty> requires std::derived_from<_Ty, Type>
		QualifiedType(_Ty const& _type, Qualifiers qualifiers = Qualifier_None) : qualifiers(qualifiers)
		{
			type = std::make_shared<_Ty>(_type);
		}

		bool IsConst() const { return qualifiers & Qualifier_Const; }
		void AddConst() { qualifiers |= Qualifier_Const; }
		void RemoveConst() { qualifiers &= ~Qualifier_Const; }

		bool HasRawType() const { return type != nullptr; }
		template<typename _Ty> requires std::derived_from<_Ty, Type>
		void SetRawType(_Ty const& _type)
		{
			type = std::make_shared<_Ty>(_type);
		}
		void ResetRawType() { type = nullptr; }
		Type const& RawType() const { return *type; }
		Type& RawType() { return *type; }

		Type const* operator->() const { return type.get(); }
		Type* operator->() { return type.get(); }
		Type const& operator*() const { return RawType(); }
		operator Type const& () const { return RawType(); }

	private:
		std::shared_ptr<Type> type = nullptr;
		Qualifiers qualifiers = Qualifier_None;
	};

	class VoidType : public Type
	{
	public:
		constexpr VoidType() : Type{ TypeKind::Void } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			return other.Is(TypeKind::Void);
		}
	};

	class BoolType : public Type
	{
	public:
		constexpr BoolType() : Type{ TypeKind::Bool, 1, 1 } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			return other.IsOneOf(TypeKind::Bool, TypeKind::Char, TypeKind::Int);
		}
	};

	class CharType : public Type
	{
	public:
		constexpr CharType() : Type{ TypeKind::Char, 1, 1 } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			return other.IsOneOf(TypeKind::Bool, TypeKind::Char, TypeKind::Int);
		}
	};

	class IntType : public Type
	{
	public:
		constexpr IntType() : Type{ TypeKind::Int, 8, 8 } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			return other.IsOneOf(TypeKind::Bool, TypeKind::Char, TypeKind::Int);
		}
	};

	class FloatType : public Type
	{
	public:
		constexpr FloatType() : Type{ TypeKind::Float, 8, 8 } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			return other.IsOneOf(TypeKind::Float);
		}
	};

	class ArrayType : public Type
	{
	public:
		explicit ArrayType(QualifiedType const& type) : Type{ TypeKind::Array, 0, type->GetAlign() }, base_type(type) {}
		ArrayType(QualifiedType const& type, uint32 array_size) : Type{ TypeKind::Array, array_size * type->GetSize(), type->GetAlign() },
			base_type(type), array_size(array_size) {}

		virtual bool IsCompatible(Type const& other) const override
		{
			if (other.IsNot(TypeKind::Array)) return false;
			ArrayType const& other_array_type = other.As<ArrayType>();

			bool is_underlying_type_array = base_type->Is(TypeKind::Array);
			bool is_other_underlying_type_array = other_array_type.base_type->Is(TypeKind::Array);
			if (!is_underlying_type_array && !is_other_underlying_type_array)
			{
				return base_type->GetKind() == other_array_type.base_type->GetKind();
			}
			else if (is_underlying_type_array && is_other_underlying_type_array)
			{
				return base_type->IsCompatible(*other_array_type.base_type);
			}
			else return false;
		}

	private:
		QualifiedType base_type;
		uint32 array_size = 0;
	};

	struct FunctionParameter
	{
		std::string name = "";
		QualifiedType type;
	};
	class FunctionType : public Type
	{
	public:
		explicit FunctionType(QualifiedType const& return_type, std::vector<FunctionParameter> const& params = {}) : Type{ TypeKind::Function, 8, 8 },
		return_type(return_type), params(params){}

		virtual bool IsCompatible(Type const& other) const override
		{
			return false;
		}

		QualifiedType const& GetReturnType() const { return return_type; }
		std::span<const FunctionParameter> GetParameters() const { return params; }

	private:
		QualifiedType return_type;
		std::vector<FunctionParameter> params;
	};

	namespace builtin_types
	{
		static constexpr VoidType  Void  = VoidType();
		static constexpr BoolType  Bool  = BoolType();
		static constexpr CharType  Char  = CharType();
		static constexpr IntType   Int   = IntType();
		static constexpr FloatType Float = FloatType();
	}

	template<TypeKind K>
	inline bool IsType(Type const& type)
	{
		return type.Is(K);
	}

	inline bool (*IsVoidType)(Type const& type) = IsType<TypeKind::Void>;
	inline bool (*IsArrayType)(Type const& type) = IsType<TypeKind::Array>;
	inline bool (*IsIntegerType)(Type const& type) = IsType<TypeKind::Int>;
	inline bool (*IsBoolType)(Type const& type) = IsType<TypeKind::Bool>;
	inline bool (*IsCharType)(Type const& type) = IsType<TypeKind::Char>;
	inline bool (*IsFloatType)(Type const& type) = IsType<TypeKind::Float>;
	inline bool (*IsFunctionType)(Type const& type) = IsType<TypeKind::Function>;
	inline bool (*IsClassType)(Type const& type) = IsType<TypeKind::Class>;

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
	inline T* dynamic_type_cast(Type& t)
	{
		return dynamic_cast<T*>(&t);
	}
	template<typename T> requires std::derived_from<T, Type>
	inline T const* dynamic_type_cast(Type const& t)
	{
		return dynamic_cast<T const*>(&t);
	}

	template<typename T>
	T const& Type::As() const
	{
		return type_cast<T>(*this);
	}
	template<typename T>
	T& Type::As()
	{
		return type_cast<T>(*this);
	}
	template<typename T>
	T const* Type::TryAs() const
	{
		return dynamic_type_cast<T>(*this);
	}
	template<typename T>
	T* Type::TryAs()
	{
		return dynamic_type_cast<T>(*this);
	}
}