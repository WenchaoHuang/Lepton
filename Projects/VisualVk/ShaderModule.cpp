/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#include "ShaderModule.h"
#include <fstream>

using namespace Vk;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
ShaderModule::ShaderModule() : m_hShaderModule(VK_NULL_HANDLE)
{

}


VkResult ShaderModule::Create(const std::vector<char> & BinaryCode)
{
	VkShaderModuleCreateInfo	CreateInfo = {};
	CreateInfo.sType			= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext			= nullptr;
	CreateInfo.flags			= 0;
	CreateInfo.codeSize			= BinaryCode.size();
	CreateInfo.pCode			= (uint32_t*)BinaryCode.data();

	VkShaderModule hShaderModule = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateShaderModule(&CreateInfo, &hShaderModule);

	if (eResult == VK_SUCCESS)
	{
		this->Release();

		m_hShaderModule = hShaderModule;
	}

	return eResult;
}


std::vector<char> ShaderModule::ReadBinary(const char * pFileName)
{
	std::ifstream Stream(pFileName, std::ios::ate | std::ios::binary);

	std::vector<char> BinaryCode;

	if (Stream.is_open() && Stream.good())
	{
		BinaryCode.resize((size_t)Stream.tellg());

		Stream.seekg(0);

		Stream.read(BinaryCode.data(), BinaryCode.size());

		Stream.close();
	}

	return BinaryCode;
}


VkResult ShaderModule::Create(const char * pFileName)
{
	return this->Create(ShaderModule::ReadBinary(pFileName));
}


void ShaderModule::Release() noexcept
{
	if (m_hShaderModule != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyShaderModule(m_hShaderModule);

		m_hShaderModule = VK_NULL_HANDLE;
	}
}


ShaderModule::~ShaderModule()
{
	this->Release();
}


/*************************************************************************
***********************    PipelineShaderStages    ***********************
*************************************************************************/
VkPipelineShaderStageCreateInfo * PipelineShaderStages::GetStages()
{
	m_ShaderStageCreateInfos.clear();



	return nullptr;
}