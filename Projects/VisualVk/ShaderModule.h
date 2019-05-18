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

		//!	@brief	Return create information of shader stage.
		VkPipelineShaderStageCreateInfo GetStageCreateInfo(VkShaderStageFlagBits eStage) const;

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

	private:

		const VkShaderModule		m_hShaderModule;
	};

	/*********************************************************************
	*********************    PipelineShaderStages    *********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan pipeline shader stages object.
	 */
	class PipelineShaderStages
	{

	public:

		//!	@brief	Return count of valid states.
		uint32_t GetStageCount() const;

		//!	@brief	Return pointer to array of create informations.
		const VkPipelineShaderStageCreateInfo * GetStages();

	public:

		std::shared_ptr<ShaderModule>			spVertexShader;
		std::shared_ptr<ShaderModule>			spGeometryShader;
		std::shared_ptr<ShaderModule>			spFragmentShader;
		std::shared_ptr<ShaderModule>			spTessControlShader;
		std::shared_ptr<ShaderModule>			spTessEvalutionShader;

	private:

		std::vector<VkPipelineShaderStageCreateInfo>	m_CreateInfos;
	};
}