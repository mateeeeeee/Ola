#pragma once
namespace ola
{
	template <typename Attr>
	class Attribute
	{
	public:

		constexpr Attribute() : attribute{ static_cast<Attr>(0) } {}
		constexpr Attribute(Attr attr) : attribute{ attr } {}

		OLA_NODISCARD Bool HasAttr(Attr attr) const 
		{
			return static_cast<Uint32>(attribute) & static_cast<Uint32>(attr);
		}
		Attribute& AddAttr(Attr attr) 
		{
			attribute = static_cast<Attr>(static_cast<Uint32>(attribute) | static_cast<Uint32>(attr));
			return *this;
		}
		Attribute& RemoveAttr(Attr attr)
		{
			attribute = static_cast<Attr>(static_cast<Uint32>(attribute) & (~static_cast<Uint32>(attr)));
			return *this;
		}
		OLA_NODISCARD Bool Empty() const  
		{
			return !static_cast<Uint32>(attribute);
		}

	private:
		Attr attribute;
	};
}