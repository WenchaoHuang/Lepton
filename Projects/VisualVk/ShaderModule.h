#pragma once

#include "Resource.h"

namespace Vk
{


	template<VkShaderStageFlagBits eStage> class ShaderModule : private Resource
	{

	public:

		ShaderModule();

		~ShaderModule();

	private:

		ShaderModule(VkShaderModule hShaderModule);

	public:

		static std::shared_ptr<ShaderModule> Create();


	private:

		const VkShaderModule				m_hShaderModule;

		VkPipelineShaderStageCreateInfo		m_ShaderStageCreateInfo;
	};
}