#pragma once

namespace ola
{

	enum class IRTypeKind 
	{
		Unknown,
		Void,
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

	protected:
		explicit IRType(IRTypeKind kind) : kind(kind) {}

	private:
		IRTypeKind kind;
	};
}