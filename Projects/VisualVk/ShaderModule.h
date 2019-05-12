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
		ShaderModule();

		//!	@brief	Destroy shader module object.
		~ShaderModule();

	public:

		//!	@brief	Convert to handle.
		operator VkShaderModule() { return m_hShaderModule; }

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * pFileName);

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

		//!	@brief	Create a new shader module object
		VkResult Create(const std::vector<char> & BinaryCode);

		//!	@brief	Create a new shader module object
		VkResult Create(const char * pFileName);

		//!	@brief	Destroy shader module object.
		void Release() noexcept;

	private:

		VkShaderModule		m_hShaderModule;
	};

	/*********************************************************************
	*********************    PipelineShaderStages    *********************
	*********************************************************************/

	class PipelineShaderStages
	{

	public:

		uint32_t GetStageCount() const;

		VkPipelineShaderStageCreateInfo * GetStages();

	public:

		ShaderModule			VertexShader;
		ShaderModule			GeometryShader;
		ShaderModule			FragmentShader;
		ShaderModule			TessControlShader;
		ShaderModule			TessEvalutionShader;

	private:

		std::vector<VkPipelineShaderStageCreateInfo>		m_ShaderStageCreateInfos;
	};
}