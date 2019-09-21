/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan shader module object.
	 */
	class ShaderModule
	{

	public:

		//!	@brief	Create shader module object.
		VkResult Create(const char * Path);

		//!	@brief	Create shader module object.
		VkResult Create(const std::vector<char> & BinaryCode);

	private:

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * Path);
	};
}