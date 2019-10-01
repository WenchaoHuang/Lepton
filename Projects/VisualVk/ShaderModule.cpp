/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/

#include <fstream>
#include "ShaderModule.h"

using namespace Vk;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
ShaderModule::ShaderModule(VkDevice hDevice, ArrayProxy<const uint32_t> code_spv)
	: m_hDevice(VK_NULL_HANDLE), m_hShaderModule(VK_NULL_HANDLE)
{
	if ((hDevice != VK_NULL_HANDLE) && !code_spv.empty())
	{
		VkShaderModuleCreateInfo		CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.codeSize				= sizeof(uint32_t) * code_spv.size();
		CreateInfo.pCode				= code_spv.data();

		VkShaderModule hShaderModule = VK_NULL_HANDLE;

		if (vkCreateShaderModule(hDevice, &CreateInfo, nullptr, &hShaderModule) == VK_SUCCESS)
		{
			m_hShaderModule = hShaderModule;

			m_hDevice = hDevice;
		}
	}
}


std::vector<uint32_t> ShaderModule::ReadSPIRV(const char * pFilePath)
{
	std::ifstream Stream(pFilePath, std::ios::ate | std::ios::binary);

	std::vector<uint32_t> BinaryCode;

	if (Stream.is_open() && Stream.good())
	{
		size_t sizeBytes = static_cast<size_t>(Stream.tellg());

		if (sizeBytes % sizeof(uint32_t) == 0)
		{
			BinaryCode.resize(sizeBytes / sizeof(uint32_t));

			Stream.seekg(0);

			Stream.read(reinterpret_cast<char*>(BinaryCode.data()), sizeBytes);
		}

		Stream.close();
	}

	return BinaryCode;
}


ShaderModule::~ShaderModule()
{
	if (m_hShaderModule != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(m_hDevice, m_hShaderModule, nullptr);

		m_hShaderModule = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}