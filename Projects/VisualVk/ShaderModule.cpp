/*************************************************************************
**********************    VisualVk_ShaderModule    ***********************
*************************************************************************/
#include "ShaderModule.h"
#include <fstream>

using namespace Vk;

template ShaderModule<VK_SHADER_STAGE_VERTEX_BIT>;
template ShaderModule<VK_SHADER_STAGE_COMPUTE_BIT>;
template ShaderModule<VK_SHADER_STAGE_GEOMETRY_BIT>;
template ShaderModule<VK_SHADER_STAGE_FRAGMENT_BIT>;
template ShaderModule<VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT>;
template ShaderModule<VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT>;

/*************************************************************************
***************************    ShaderModule    ***************************
*************************************************************************/
template<VkShaderStageFlagBits eStage> ShaderModule<eStage>::ShaderModule(VkShaderModule hShaderModule) : m_hShaderModule(hShaderModule)
{
	m_ShaderStageCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	m_ShaderStageCreateInfo.pNext					= nullptr;
	m_ShaderStageCreateInfo.flags					= 0;
	m_ShaderStageCreateInfo.stage					= eStage;
	m_ShaderStageCreateInfo.module					= m_hShaderModule;
	m_ShaderStageCreateInfo.pName					= "main";
	m_ShaderStageCreateInfo.pSpecializationInfo		= nullptr;
}


template<VkShaderStageFlagBits eStage> std::vector<char> ShaderModule<eStage>::ReadBinary(const char * pFileName)
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


template<VkShaderStageFlagBits eStage> std::shared_ptr<ShaderModule<eStage>> ShaderModule<eStage>::Create(const char * pFileName)
{
	return ShaderModule::Create(ShaderModule::ReadBinary(pFileName));
}


template<VkShaderStageFlagBits eStage> std::shared_ptr<ShaderModule<eStage>> ShaderModule<eStage>::Create(const std::vector<char> & BinaryCode)
{
	if (BinaryCode.empty())			return nullptr;
	
	VkShaderModuleCreateInfo		CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.codeSize				= BinaryCode.size();
	CreateInfo.pCode				= (uint32_t*)BinaryCode.data();

	VkShaderModule hShaderModule = VK_NULL_HANDLE;

	sm_pDevice->CreateShaderModule(&CreateInfo, &hShaderModule);

	return std::make_shared<ShaderModule>(hShaderModule);
}


template<VkShaderStageFlagBits eStage> ShaderModule<eStage>::~ShaderModule() noexcept
{
	sm_pDevice->DestroyShaderModule(m_hShaderModule);
}