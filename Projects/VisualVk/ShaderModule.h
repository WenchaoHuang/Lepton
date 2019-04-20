/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan shader module object.
	 */
	class ShaderModule : private Resource
	{

	public:

		//!	@brief	Create shader module object.
		ShaderModule(VkShaderModule hShaderModule);

		//!	@brief	Destroy shader module object.
		~ShaderModule() noexcept;

	public:

		//!	@brief	Convert to handle.
		operator VkShaderModule() { return m_hShaderModule; }

		//!	@brief	Read binary file.
		static std::vector<char> ReadBinary(const char * pFileName);

		//!	@brief	Create shader module.
		static std::shared_ptr<ShaderModule> Create(const char * pFileName);

		//!	@brief	Create shader module.
		static std::shared_ptr<ShaderModule> Create(const std::vector<char> & BinaryCode);

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

	private:

		const VkShaderModule	m_hShaderModule;
	};
}