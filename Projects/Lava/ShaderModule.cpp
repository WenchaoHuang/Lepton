/*************************************************************************
************************    Lava_ShaderModule    *************************
*************************************************************************/

#include <fstream>
#include "ShaderModule.h"

using namespace Lava;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
ShaderModule::UniqueHandle::UniqueHandle(VkDevice hDevice, VkShaderModule hShaderModule, ShaderStage eStage) : m_hDevice(hDevice)
{
	m_StageInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	m_StageInfo.pNext					= nullptr;
	m_StageInfo.flags					= 0;
	m_StageInfo.stage					= static_cast<VkShaderStageFlagBits>(eStage);
	m_StageInfo.module					= hShaderModule;
	m_StageInfo.pName					= "main";
	m_StageInfo.pSpecializationInfo		= nullptr;
}


Result ShaderModule::Create(VkDevice hDevice, ArrayProxy<uint32_t> pCode, ShaderStage eStage)
{
	if (pCode.empty() == true)			return Result::eErrorInvalidSPIRVCode;
	if (hDevice == VK_NULL_HANDLE)		return Result::eErrorInvalidDeviceHandle;

	VkShaderModuleCreateInfo			CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.codeSize					= sizeof(uint32_t) * pCode.size();
	CreateInfo.pCode					= pCode.data();

	VkShaderModule hShaderModule = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateShaderModule(hDevice, &CreateInfo, nullptr, &hShaderModule));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(hDevice, hShaderModule, eStage);
	}

	return eResult;
}


Result ShaderModule::Create(VkDevice hDevice, const char * pShaderPath, ShaderStage eShaderStage)
{
	std::vector<uint32_t> ShaderCode;

	std::ifstream Stream(pShaderPath, std::ios::ate | std::ios::binary);

	if (Stream.is_open() && Stream.good())
	{
		size_t sizeBytes = static_cast<size_t>(Stream.tellg());

		if (sizeBytes % sizeof(uint32_t) == 0)
		{
			ShaderCode.resize(sizeBytes / sizeof(uint32_t));

			Stream.seekg(0);

			Stream.read(reinterpret_cast<char*>(ShaderCode.data()), sizeBytes);
		}

		Stream.close();
	}

	return this->Create(hDevice, ShaderCode, eShaderStage);
}


ShaderModule::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_StageInfo.module != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(m_hDevice, m_StageInfo.module, nullptr);
	}
}