/*************************************************************************
***************************    Lepton_Flags    ***************************
*************************************************************************/
#pragma once

#include <concepts>
#include <vulkan/vulkan.h>

namespace Lepton
{
	//!	@brief		Define what bit-enumerated type is.
	template<typename Type> concept BitEnum = std::is_enum<Type>::value && std::same_as<std::underlying_type_t<Type>, VkFlags>;

	/*********************************************************************
	****************************    Flags    *****************************
	*********************************************************************/

	/**
	 *	@brief		Template for Vulkan enumeration bitmask.
	 */
	template<BitEnum Type> class Flags
	{

	public:

		//!	@brief	Default constructor.
		constexpr Flags() : m_Mask(0) {}

		//!	@brief	Constructed by another flags.
		constexpr Flags(VkFlags flags) : m_Mask(flags) {}

		//!	@brief	Constructed by a given bitmask.
		constexpr Flags(Type bit) : m_Mask(static_cast<VkFlags>(bit)) {}

		//!	@brief	Bitwise operation: Type | Flags.
		constexpr friend Flags operator|(Type bit, Flags flags) { return Flags(static_cast<VkFlags>(bit) | flags.m_Mask); }

		//!	@brief	Bitwise operation: Type & Flags.
		constexpr friend Flags operator&(Type bit, Flags flags) { return Flags(static_cast<VkFlags>(bit) & flags.m_Mask); }

		//!	@brief	Bitwise operation: Flags | Flags.
		constexpr Flags operator|(Flags flags) const { return Flags(m_Mask | flags.m_Mask); }

		//!	@brief	Bitwise operation: Flags & Flags.
		constexpr Flags operator&(Flags flags) const { return Flags(m_Mask & flags.m_Mask); }

		//!	@brief	Bitwise operation: Flags |= Flags.
		constexpr void operator|=(Flags flags) { m_Mask |= flags.m_Mask; }

		//!	@brief	Bitwise operation: Flags &= Flags.
		constexpr void operator&=(Flags flags) { m_Mask &= flags.m_Mask; }

		//!	@brief	Bitwise operation: ~Flags.
		constexpr Flags operator~() const { return Flags(~m_Mask); }

		//!	@brief	Cast to VkFlags.
		constexpr operator VkFlags() const { return m_Mask; }

	private:

		VkFlags		m_Mask;
	};

	/*********************************************************************
	**********************    Bitwise operators    ***********************
	*********************************************************************/

	template<BitEnum Type> constexpr Flags<Type> operator|(Type a, Type b)
	{
		return Flags<Type>(static_cast<VkFlags>(a) | static_cast<VkFlags>(b));
	}

	template<BitEnum Type> constexpr Flags<Type> operator&(Type a, Type b)
	{
		return Flags<Type>(static_cast<VkFlags>(a) & static_cast<VkFlags>(b));
	}

	template<BitEnum Type> constexpr Flags<Type> operator~(Type a)
	{
		return Flags<Type>(~static_cast<VkFlags>(a));
	}
}