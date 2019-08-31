/*************************************************************************
**************************    VisualVk_Flags    **************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan_core.h>

namespace Vk
{
	/*********************************************************************
	****************************    Flags    *****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan enumeration bitmask.
	 */
	template<typename BitType> class Flags
	{

	public:

		//!	@brief	Default constructor.
		constexpr Flags() : m_Mask(0) {}

		//!	@brief	Constructed by another flags.
		constexpr Flags(VkFlags flags) : m_Mask(flags) {}

		//!	@brief	Constructed by a given bitmask.
		constexpr Flags(BitType bit) : m_Mask(static_cast<VkFlags>(bit)) {}

		//!	@brief	Bitwise operation: BitType | Flags.
		constexpr friend Flags operator|(BitType bit, Flags flags) { return static_cast<VkFlags>(bit) | flags.m_Mask; }

		//!	@brief	Bitwise operation: BitType & Flags.
		constexpr friend Flags operator&(BitType bit, Flags flags) { return static_cast<VkFlags>(bit) & flags.m_Mask; }

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

		//!	@brief	Convert to VkFlags.
		constexpr operator VkFlags() const { return m_Mask; }

	private:

		VkFlags		m_Mask;
	};

	/*********************************************************************
	**********************    Bitwise operators    ***********************
	*********************************************************************/

	//!	@brief	Bitwise operation: BitType & BitType.
	template<typename BitType> constexpr Flags<BitType> operator&(BitType a, BitType b)
	{
		return Flags<BitType>(static_cast<VkFlags>(a) & static_cast<VkFlags>(b));
	}

	//!	@brief	Bitwise operation: BitType | BitType.
	template<typename BitType> constexpr Flags<BitType> operator|(BitType a, BitType b)
	{
		return Flags<BitType>(static_cast<VkFlags>(a) | static_cast<VkFlags>(b));
	}

	//!	@brief	Bitwise operation: ~BitType.
	template<typename BitType> constexpr Flags<BitType> operator~(BitType a)
	{
		return Flags<BitType>(~static_cast<VkFlags>(a));
	}
}