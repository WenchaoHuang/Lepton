/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan shader module object.
	 */
	class ShaderModule
	{
		VK_UNIQUE_RESOURCE(ShaderModule)

	public:

		//!	@brief	Create shader module object.
		ShaderModule();

		//!	@brief	Create and initialize immediately.
		explicit ShaderModule(VkDevice hDevice, const char * pFilePath);

		//!	@brief	Create and initialize immediately.
		explicit ShaderModule(VkDevice hDevice, ArrayProxy<const uint32_t> code_spv);

		//!	@brief	Destroy shader module object.
		~ShaderModule();

	public:

		//!	@brief	Read SPIR-V shader.
		static std::vector<uint32_t> ReadSPIRV(const char * pFilePath);

		//!	@brief	Create a new shader module.
		Result Create(VkDevice hDevice, ArrayProxy<const uint32_t> code_spv);

		//!	@brief	Create a new shader module.
		Result Create(VkDevice hDevice, const char * pFilePath);

		//!	@brief	Destroy the shader module.
		void Destroy();
	};
}