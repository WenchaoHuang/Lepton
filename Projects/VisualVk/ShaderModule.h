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

		//!	@brief	Creates shader module object.
		ShaderModule(VkShaderModule hShaderModule = VK_NULL_HANDLE);

		//!	@brief	Destroys shader module object.
		~ShaderModule() noexcept;

	public:

		//!	@brief	Read file as binary data.
		static std::vector<char> ReadBinary(const char * pFileName);

		//!	@brief	Creates a new shader module object
		static std::shared_ptr<ShaderModule> Create(const char * pFileName);

		//!	@brief	Creates a new shader module object
		static std::shared_ptr<ShaderModule> Create(const std::vector<char> & BinaryCode);

		//!	@brief	Returns creating information of shader stage.
		VkPipelineShaderStageCreateInfo GetStageInfo(VkShaderStageFlagBits eStage) const;

		//!	@brief	If shader handle is valid.
		VkBool32 IsValid() const { return m_hShaderModule != VK_NULL_HANDLE; }

	private:

		const VkShaderModule		m_hShaderModule;
	};

	/*********************************************************************
	***********************    ShaderStagesInfo    ***********************
	*********************************************************************/

	/**
	 *	@brief	Vulkan pipeline shader stages object.
	 */
	class ShaderStagesInfo
	{

	public:

		//!	@brief	Returns count of valid states.
		uint32_t GetStageCount() const;

		//!	@brief	Returns pointer to array of create informations.
		const VkPipelineShaderStageCreateInfo * GetStages();

	public:

		std::shared_ptr<ShaderModule>		spVertexShader;
		std::shared_ptr<ShaderModule>		spGeometryShader;
		std::shared_ptr<ShaderModule>		spFragmentShader;
		std::shared_ptr<ShaderModule>		spTessControlShader;
		std::shared_ptr<ShaderModule>		spTessEvalutionShader;

	private:

		std::vector<VkPipelineShaderStageCreateInfo>	m_CreateInfos;
	};
}