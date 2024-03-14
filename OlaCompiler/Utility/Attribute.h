#pragma once
namespace ola
{
	template <typename Attr>
	class Attribute
	{
	public:

		constexpr Attribute() : attribute{ static_cast<Attr>(0) } {}
		constexpr Attribute(Attr attr) : attribute{ attr } {}

		OLA_NODISCARD bool HasAttr(Attr attr) const 
		{
			return static_cast<uint32>(attribute) & static_cast<uint32>(attr);
		}
		Attribute& AddAttr(Attr attr) 
		{
			attribute = static_cast<Attr>(static_cast<uint32>(attribute) | static_cast<uint32>(attr));
			return *this;
		}
		Attribute& RemoveAttr(Attr attr)
		{
			attribute = static_cast<Attr>(static_cast<uint32>(attribute) & (~static_cast<uint32>(attr)));
			return *this;
		}
		OLA_NODISCARD bool Empty() const  
		{
			return !static_cast<uint32>(attribute);
		}

	private:
		Attr attribute;
	};
}