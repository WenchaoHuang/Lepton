/*************************************************************************
***********************    VisualVk_ShaderStage    ***********************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	*************************    ShaderModule    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan shader module object.
	 */
	template<VkShaderStageFlagBits eShaderStage> class ShaderModule : private Resource
	{

	public:

		//!	@brief	Create shader module object.
		ShaderModule();

		//!	@brief	Destroy shader module object.
		~ShaderModule();

	public:

		//!	@brief	Convert to create information.
		operator VkPipelineShaderStageCreateInfo() { return m_ShaderStageCreateInfo; }

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_ShaderStageCreateInfo.module != VK_NULL_HANDLE; }

		//!	@brief	Create a new shader module object
		VkResult Create(const std::vector<char> & BinaryCode);

		//!	@brief	Create a new shader module object
		VkResult Create(const char * pFileName);

		//!	@brief	Destroy shader module object.
		void Release() noexcept;

	private:

		VkPipelineShaderStageCreateInfo		m_ShaderStageCreateInfo;
	};

	/*********************************************************************
	*********************    PipelineShaderStages    *********************
	*********************************************************************/

	class PipelineShaderStages
	{

	public:

		//!	@brief	Return count of valid stage.
		uint32_t GetStageCount() const;

		//!	@brief	Return pointer to array of shader stage create infos.
		VkPipelineShaderStageCreateInfo * GetStages();

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * pFileName);

	public:

		ShaderModule<VK_SHADER_STAGE_VERTEX_BIT>						VertexShader;
		ShaderModule<VK_SHADER_STAGE_GEOMETRY_BIT>						GeometryShader;
		ShaderModule<VK_SHADER_STAGE_FRAGMENT_BIT>						FragmentShader;
		ShaderModule<VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>			TessControlShader;
		ShaderModule<VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>		TessEvalutionShader;

	private:

		std::vector<VkPipelineShaderStageCreateInfo>					m_ShaderStageCreateInfos;
	};
}