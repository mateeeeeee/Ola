#include "AST.h"

namespace wave
{
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* DynamicAstCast(From* from)
	{
		return dynamic_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* DynamicAstCast(From const* from)
	{
		return dynamic_cast<To const*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* AstCast(From* from)
	{
		return static_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* AstCast(From const* from)
	{
		return static_cast<To const*>(from);
	}
}

