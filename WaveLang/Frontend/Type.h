#pragma once
#include <concepts>
#include <string>
#include <vector>
#include <span>

namespace wave
{
	enum class TypeKind : uint8
	{
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

		constexpr bool IsConst() const { return is_const; }
		constexpr uint32 GetSize() const { return size; }
		constexpr uint32 GetAlign() const { return align; }
		constexpr void SetConst(bool _const) { is_const = _const; }
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
		TypeKind kind;
		uint32 size;
		uint32 align;
		bool is_const;

	protected:
		constexpr Type(TypeKind kind, uint32 size = 0, uint32 align = 0)
			: kind(kind), size(size), align(align), is_const(false) {}
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
		explicit ArrayType(Type const& type) : Type{ TypeKind::Array, 0, type.GetAlign() } {}
		virtual bool IsCompatible(Type const& other) const override
		{
			if (other.IsNot(TypeKind::Array)) return false;
			ArrayType const& other_array_type = other.As<ArrayType>();

			bool is_underlying_type_array = type.Is(TypeKind::Array);
			bool is_other_underlying_type_array = other_array_type.type.Is(TypeKind::Array);
			if (!is_underlying_type_array && !is_other_underlying_type_array)
			{
				return type.GetKind() == other_array_type.type.GetKind();
			}
			else if (is_underlying_type_array && is_other_underlying_type_array)
			{
				return type.IsCompatible(other_array_type.type);
			}
			else return false;
		}

	private:
		Type type;
	};

	struct FunctionParameter
	{
		std::string name = "";
		Type type;
	};
	class FunctionType : public Type
	{
	public:
		explicit FunctionType(Type const& return_type, std::vector<FunctionParameter> const& params = {}) : Type{ TypeKind::Function, 8, 8 },
		return_type(return_type), params(params){}

		virtual bool IsCompatible(Type const& other) const override
		{
			return false;
		}

		Type const& GetReturnType() const { return return_type; }
		std::span<const FunctionParameter> GetParameters() const { return params; }

	private:
		Type return_type;
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
	inline T& TypeCast(Type& t)
	{
		return static_cast<T&>(t);
	}
	template<typename T> requires std::derived_from<T, Type>
	inline T const& TypeCast(Type const& t)
	{
		return static_cast<T const&>(t);
	}

	template<typename T> requires std::derived_from<T, Type>
	inline T* DynamicTypeCast(Type& t)
	{
		return dynamic_cast<T*>(&t);
	}
	template<typename T> requires std::derived_from<T, Type>
	inline T const* DynamicTypeCast(Type const& t)
	{
		return dynamic_cast<T const*>(&t);
	}

	template<typename T>
	T const& Type::As() const
	{
		return TypeCast<T>(*this);
	}
	template<typename T>
	T& Type::As()
	{
		return TypeCast<T>(*this);
	}
	template<typename T>
	T const* Type::TryAs() const
	{
		return DynamicTypeCast<T>(*this);
	}
	template<typename T>
	T* Type::TryAs()
	{
		return DynamicTypeCast<T>(*this);
	}
}