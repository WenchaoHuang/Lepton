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
		ShaderModule(VkShaderModule hShaderModule = VK_NULL_HANDLE);

		//!	@brief	Destroy shader module object.
		~ShaderModule() noexcept;

	public:

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * pFileName);

		//!	@brief	Create a new shader module object
		static std::shared_ptr<ShaderModule> Create(const char * pFileName);

		//!	@brief	Create a new shader module object
		static std::shared_ptr<ShaderModule> Create(const std::vector<char> & BinaryCode);

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

		//!	@brief	Return VkShaderModule handle.
		VkShaderModule GetHandle() const { return m_hShaderModule; }

	private:

		const VkShaderModule		m_hShaderModule;
	};
}