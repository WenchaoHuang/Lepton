/*************************************************************************
***************************    Lepton_Enums    ***************************
*************************************************************************/
#pragma once

#include <vulkan/vulkan.hpp>

namespace Lepton
{
	/*********************************************************************
	**************************    IndexType    ***************************
	*********************************************************************/

	/**
	 *	@brief		Type of index buffer indices.
	 */
	enum class IndexType
	{
		eUint16		= VK_INDEX_TYPE_UINT16,
		eUint32		= VK_INDEX_TYPE_UINT32,
		eNoneNV		= VK_INDEX_TYPE_NONE_NV,
		eUint8EXT	= VK_INDEX_TYPE_UINT8_EXT,
	};
}