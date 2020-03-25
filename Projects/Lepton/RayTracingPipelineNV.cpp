/*************************************************************************
*******************    Lepton_RayTracingPipelineNV    ********************
*************************************************************************/

#include "RayTracingPipelineNV.h"

using namespace Lepton;

/*************************************************************************
***********************    RayTracingPipelineNV    ***********************
*************************************************************************/
RayTracingPipelineNV::RayTracingPipelineNV() : m_hDevice(VK_NULL_HANDLE), m_hRayTracingPipelineNV(VK_NULL_HANDLE)
{

}


RayTracingPipelineNV::RayTracingPipelineNV(const RayTracingPipelineParam & Param)
{
	this->Create(Param);
}


Result RayTracingPipelineNV::Create(const RayTracingPipelineParam & Param)
{
	if (!Param.pipelineLayout.IsValid())		return Result::eErrorInvalidPipelineLayoutHandle;

	PFN_vkCreateRayTracingPipelinesNV			pfnCreateRayTracingPipelines = nullptr;

	pfnCreateRayTracingPipelines				= (PFN_vkCreateRayTracingPipelinesNV)vkGetDeviceProcAddr(Param.pipelineLayout.GetDeviceHandle(), "vkCreateRayTracingPipelinesNV");

	if (!pfnCreateRayTracingPipelines)			return Result::eErrorFailedToGetProcessAddress;

	std::vector<VkPipelineShaderStageCreateInfo>			ShaderStageCreateInfos(Param.shaderStages.size());
	std::vector<VkRayTracingShaderGroupCreateInfoNV>		ShaderGroupCreateInfos(Param.shaderGroups.size());

	for (size_t i = 0; i < ShaderStageCreateInfos.size(); i++)
	{
		ShaderStageCreateInfos[i] = Param.shaderStages[i].GetStageInfo();
	}

	for (size_t i = 0; i < ShaderGroupCreateInfos.size(); i++)
	{
		ShaderGroupCreateInfos[i].sType						= VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV;
		ShaderGroupCreateInfos[i].pNext						= nullptr;
		ShaderGroupCreateInfos[i].type						= static_cast<VkRayTracingShaderGroupTypeNV>(Param.shaderGroups[i].eType);
		ShaderGroupCreateInfos[i].generalShader				= Param.shaderGroups[i].generalShader;
		ShaderGroupCreateInfos[i].closestHitShader			= Param.shaderGroups[i].closestHitShader;
		ShaderGroupCreateInfos[i].anyHitShader				= Param.shaderGroups[i].anyHitShader;
		ShaderGroupCreateInfos[i].intersectionShader		= Param.shaderGroups[i].intersectionShader;
	}

	VkRayTracingPipelineCreateInfoNV		CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.stageCount					= static_cast<uint32_t>(ShaderStageCreateInfos.size());
	CreateInfo.pStages						= ShaderStageCreateInfos.data();
	CreateInfo.groupCount					= static_cast<uint32_t>(ShaderGroupCreateInfos.size());
	CreateInfo.pGroups						= ShaderGroupCreateInfos.data();
	CreateInfo.maxRecursionDepth			= Param.maxRecursionDepth;
	CreateInfo.layout						= Param.pipelineLayout;
	CreateInfo.basePipelineHandle			= VK_NULL_HANDLE;
	CreateInfo.basePipelineIndex			= 0;

	VkPipeline hPipeline = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(pfnCreateRayTracingPipelines(Param.pipelineLayout.GetDeviceHandle(), VK_NULL_HANDLE, 1, &CreateInfo, nullptr, &hPipeline));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hDevice = Param.pipelineLayout.GetDeviceHandle();

		m_hRayTracingPipelineNV = hPipeline;

		m_Parameter = Param;
	}

	return eResult;
}


void RayTracingPipelineNV::Destroy()
{
	if (m_hRayTracingPipelineNV != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hRayTracingPipelineNV, nullptr);

		m_Parameter = RayTracingPipelineParam();

		m_hRayTracingPipelineNV = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}


RayTracingPipelineNV::~RayTracingPipelineNV()
{
	this->Destroy();
}