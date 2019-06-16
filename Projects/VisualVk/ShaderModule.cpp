/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#include "ShaderModule.h"
#include <fstream>

using namespace Vk;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
ShaderModule::ShaderModule(VkShaderModule hShaderModule) : m_hShaderModule(hShaderModule)
{

}


std::shared_ptr<ShaderModule> ShaderModule::Create(const std::vector<char> & BinaryCode)
{
	VkShaderModuleCreateInfo	CreateInfo = {};
	CreateInfo.sType			= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext			= nullptr;
	CreateInfo.flags			= 0;
	CreateInfo.codeSize			= BinaryCode.size();
	CreateInfo.pCode			= reinterpret_cast<const uint32_t*>(BinaryCode.data());

	VkShaderModule hShaderModule = VK_NULL_HANDLE;

	sm_pLogicalDevice->CreateShaderModule(&CreateInfo, &hShaderModule);

	return std::make_shared<ShaderModule>(hShaderModule);
}


std::shared_ptr<ShaderModule> ShaderModule::Create(const char * pFileName)
{
	return ShaderModule::Create(ShaderModule::ReadBinary(pFileName));
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


ShaderModule::~ShaderModule()
{
	m_pDevice->DestroyShaderModule(m_hShaderModule);
}