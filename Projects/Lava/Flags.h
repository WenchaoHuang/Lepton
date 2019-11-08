/*************************************************************************
****************************    Lava_Flags    ****************************
*************************************************************************/
#pragma once

#include <type_traits>
#include <vulkan/vulkan.h>

namespace Lava
{
	/*********************************************************************
	****************************    Flags    *****************************
	*********************************************************************/

	/**
	 *	@brief	Template for Vulkan enumeration bitmask.
	 */
	template<typename EnumType> class Flags
	{

	public:

		//!	@brief	Default constructor.
		constexpr Flags() : m_Mask(0) {}

		//!	@brief	Constructed by another flags.
		constexpr Flags(VkFlags flags) : m_Mask(flags) {}

		//!	@brief	Constructed by a given bitmask.
		constexpr Flags(EnumType bit) : m_Mask(static_cast<VkFlags>(bit)) {}

		//!	@brief	Bitwise operation: EnumType | Flags.
		constexpr friend Flags operator|(EnumType bit, Flags flags) { return static_cast<VkFlags>(bit) | flags.m_Mask; }

		//!	@brief	Bitwise operation: EnumType & Flags.
		constexpr friend Flags operator&(EnumType bit, Flags flags) { return static_cast<VkFlags>(bit) & flags.m_Mask; }

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

	//!	@brief	Bitwise operation: EnumType & EnumType.
	template<typename EnumType> constexpr Flags<EnumType> operator&(EnumType a, EnumType b)
	{
		static_assert(std::is_enum<EnumType>::value, "Invalid type!");

		return Flags<EnumType>(static_cast<VkFlags>(a) & static_cast<VkFlags>(b));
	}

	//!	@brief	Bitwise operation: EnumType | EnumType.
	template<typename EnumType> constexpr Flags<EnumType> operator|(EnumType a, EnumType b)
	{
		static_assert(std::is_enum<EnumType>::value, "Invalid type!");

		return Flags<EnumType>(static_cast<VkFlags>(a) | static_cast<VkFlags>(b));
	}

	//!	@brief	Bitwise operation: ~EnumType.
	template<typename EnumType> constexpr Flags<EnumType> operator~(EnumType a)
	{
		static_assert(std::is_enum<EnumType>::value, "Invalid type!");

		return Flags<EnumType>(~static_cast<VkFlags>(a));
	}
}