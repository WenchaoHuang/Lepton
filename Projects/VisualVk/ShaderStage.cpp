/*************************************************************************
***********************    VisualVk_ShaderStage    ***********************
*************************************************************************/
#include "ShaderStage.h"
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
template<VkShaderStageFlagBits eShaderStage> ShaderModule<eShaderStage>::ShaderModule()
{
	m_ShaderStageCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	m_ShaderStageCreateInfo.pNext					= nullptr;
	m_ShaderStageCreateInfo.flags					= 0;
	m_ShaderStageCreateInfo.stage					= eShaderStage;
	m_ShaderStageCreateInfo.module					= VK_NULL_HANDLE;
	m_ShaderStageCreateInfo.pName					= "main";
	m_ShaderStageCreateInfo.pSpecializationInfo		= nullptr;
}


template<VkShaderStageFlagBits eShaderStage> VkResult ShaderModule<eShaderStage>::Create(const std::vector<char> & BinaryCode)
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

		m_ShaderStageCreateInfo.module = hShaderModule;
	}

	return eResult;
}


template<VkShaderStageFlagBits eShaderStage> VkResult ShaderModule<eShaderStage>::Create(const char * pFileName)
{
	return this->Create(PipelineShaderStages::ReadBinary(pFileName));
}


template<VkShaderStageFlagBits eShaderStage> void ShaderModule<eShaderStage>::Release() noexcept
{
	if (m_ShaderStageCreateInfo.module != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyShaderModule(m_ShaderStageCreateInfo.module);

		m_ShaderStageCreateInfo.module = VK_NULL_HANDLE;
	}
}


template<VkShaderStageFlagBits eShaderStage> ShaderModule<eShaderStage>::~ShaderModule()
{
	this->Release();
}


/*************************************************************************
***********************    PipelineShaderStages    ***********************
*************************************************************************/
std::vector<char> PipelineShaderStages::ReadBinary(const char * pFileName)
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


VkPipelineShaderStageCreateInfo * PipelineShaderStages::GetStages()
{
	m_ShaderStageCreateInfos.clear();

	if (VertexShader.IsValid())				m_ShaderStageCreateInfos.push_back(VertexShader);
	if (GeometryShader.IsValid())			m_ShaderStageCreateInfos.push_back(GeometryShader);
	if (FragmentShader.IsValid())			m_ShaderStageCreateInfos.push_back(FragmentShader);
	if (TessControlShader.IsValid())		m_ShaderStageCreateInfos.push_back(TessControlShader);
	if (TessEvalutionShader.IsValid())		m_ShaderStageCreateInfos.push_back(TessEvalutionShader);

	return m_ShaderStageCreateInfos.data();
}


uint32_t PipelineShaderStages::GetStageCount() const
{
	uint32_t StageCount = 0;

	if (VertexShader.IsValid())				StageCount++;
	if (GeometryShader.IsValid())			StageCount++;
	if (FragmentShader.IsValid())			StageCount++;
	if (TessControlShader.IsValid())		StageCount++;
	if (TessEvalutionShader.IsValid())		StageCount++;

	return StageCount;
}