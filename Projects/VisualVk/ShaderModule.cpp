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


VkPipelineShaderStageCreateInfo ShaderModule::GetStageInfo(VkShaderStageFlagBits eStage) const
{
	VkPipelineShaderStageCreateInfo				ShaderStageCreateInfo = {};
	ShaderStageCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStageCreateInfo.pNext					= nullptr;
	ShaderStageCreateInfo.flags					= 0;
	ShaderStageCreateInfo.stage					= eStage;
	ShaderStageCreateInfo.module				= m_hShaderModule;
	ShaderStageCreateInfo.pName					= "main";
	ShaderStageCreateInfo.pSpecializationInfo	= nullptr;

	return ShaderStageCreateInfo;
}


std::shared_ptr<ShaderModule> ShaderModule::Create(const std::vector<char> & BinaryCode)
{
	VkShaderModuleCreateInfo	CreateInfo = {};
	CreateInfo.sType			= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	CreateInfo.pNext			= nullptr;
	CreateInfo.flags			= 0;
	CreateInfo.codeSize			= BinaryCode.size();
	CreateInfo.pCode			= (uint32_t*)BinaryCode.data();

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


/*************************************************************************
*************************    ShaderStagesInfo    *************************
*************************************************************************/
const VkPipelineShaderStageCreateInfo * ShaderStagesInfo::GetStages()
{
	m_CreateInfos.clear();

	if ((spVertexShader != nullptr) && spVertexShader->IsValid())
		m_CreateInfos.push_back(spVertexShader->GetStageInfo(VK_SHADER_STAGE_VERTEX_BIT));

	if ((spGeometryShader != nullptr) && spGeometryShader->IsValid())
		m_CreateInfos.push_back(spGeometryShader->GetStageInfo(VK_SHADER_STAGE_GEOMETRY_BIT));

	if ((spFragmentShader != nullptr) && spFragmentShader->IsValid())
		m_CreateInfos.push_back(spFragmentShader->GetStageInfo(VK_SHADER_STAGE_FRAGMENT_BIT));

	if ((spTessControlShader != nullptr) && spTessControlShader->IsValid())
		m_CreateInfos.push_back(spTessControlShader->GetStageInfo(VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT));

	if ((spTessEvalutionShader != nullptr) && spTessEvalutionShader->IsValid())
		m_CreateInfos.push_back(spTessEvalutionShader->GetStageInfo(VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT));

	return m_CreateInfos.data();
}


uint32_t ShaderStagesInfo::GetStageCount() const
{
	uint32_t StageCount = 0;

	if ((spVertexShader != nullptr) && spVertexShader->IsValid())					StageCount++;
	if ((spGeometryShader != nullptr) && spGeometryShader->IsValid())				StageCount++;
	if ((spFragmentShader != nullptr) && spFragmentShader->IsValid())				StageCount++;
	if ((spTessControlShader != nullptr) && spTessControlShader->IsValid())			StageCount++;
	if ((spTessEvalutionShader != nullptr) && spTessEvalutionShader->IsValid())		StageCount++;

	return StageCount;
}