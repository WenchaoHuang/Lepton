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
	 *	@brief	Template for Vulkan bitmask.
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

		//!	@brief	Operator: or.
		constexpr Flags operator|(const Flags & flags) const { return Flags(m_Mask | flags.m_Mask); }

		//!	@brief	Operator: and.
		constexpr Flags operator&(const Flags & flags) const { return Flags(m_Mask & flags.m_Mask); }

		//!	@brief	Operator: or equal.
		constexpr void operator|=(const Flags & flags) { m_Mask |= flags.m_Mask; }

		//!	@brief	Operator: and equal.
		constexpr void operator&=(const Flags & flags) { m_Mask |= flags.m_Mask; }

		//!	@brief	Convert to VkFlags.
		constexpr operator VkFlags() const { return m_Mask; }

	private:

		VkFlags		m_Mask;
	};

	/*********************************************************************
	**************************    Operators    ***************************
	*********************************************************************/

	template<typename BitType> constexpr Flags<BitType> operator|(BitType a, BitType b)
	{
		return Flags<BitType>(static_cast<VkFlags>(a) | static_cast<VkFlags>(b));
	}

	template<typename BitType> constexpr Flags<BitType> operator&(BitType a, BitType b)
	{
		return Flags<BitType>(static_cast<VkFlags>(a) & static_cast<VkFlags>(b));
	}
}