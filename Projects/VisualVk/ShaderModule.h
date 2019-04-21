/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Resource.h"

namespace Vk
{
//	template<VkShaderStageFlagBits eStage> class ShaderModule;

//	using VertexShader = ShaderModule<VK_SHADER_STAGE_VERTEX_BIT>;
//	using ComputeShader = ShaderModule<VK_SHADER_STAGE_COMPUTE_BIT>;
//	using FragmentShader = std::shared_ptr<ShaderModule<VK_SHADER_STAGE_FRAGMENT_BIT>>;
//	using GeometryShader = std::shared_ptr<ShaderModule<VK_SHADER_STAGE_GEOMETRY_BIT>>;
//	using TessControlShader = std::shared_ptr<ShaderModule<VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>>;
//	using TessEvaluationShader = std::shared_ptr<ShaderModule<VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>>;

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
		static std::shared_ptr<ShaderModule> Create(const char * pFileName, VkShaderStageFlagBits eStage);

		//!	@brief	Create shader module.
		static std::shared_ptr<ShaderModule> Create(const std::vector<char> & BinaryCode, VkShaderStageFlagBits eStage);

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

	private:

		const VkShaderModule				m_hShaderModule;

		VkPipelineShaderStageCreateInfo		m_ShaderStageCreateInfo;
	};
}