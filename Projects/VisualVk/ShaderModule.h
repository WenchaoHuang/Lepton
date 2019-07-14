/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include "Handle.h"
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan shader module object.
	 */
	class ShaderModule : public ShaderModuleH
	{

	public:

		//!	@brief	Create shader module object.
		VkResult Create(const char * Path);

		//!	@brief	Create shader module object.
		VkResult Create(const std::vector<char> & BinaryCode);

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * Path);
	};
}