/*************************************************************************
********************    Lava_RayTracingPipelineNV    *********************
*************************************************************************/

#include "RayTracingPipelineNV.h"

using namespace Lava;

/*************************************************************************
***********************    RayTracingPipelineNV    ***********************
*************************************************************************/
RayTracingPipelineNV::UniqueHandle::UniqueHandle(VkDevice hDevice, VkPipeline hPipeline)
	: m_hDevice(hDevice), m_hPipeline(hPipeline)
{

}


Result RayTracingPipelineNV::Create(PipelineLayout pipelineLayout, uint32_t maxRecursionDepth)
{
	if (!pipelineLayout.IsValid())			return Result::eErrorInvalidPipelineLayoutHandle;

	VkRayTracingPipelineCreateInfoNV		CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.stageCount					;
	CreateInfo.pStages						;
	CreateInfo.groupCount					;
	CreateInfo.pGroups						;
	CreateInfo.maxRecursionDepth			= maxRecursionDepth;
	CreateInfo.layout						= pipelineLayout;
	CreateInfo.basePipelineHandle			= VK_NULL_HANDLE;
	CreateInfo.basePipelineIndex			= 0;

	VkPipeline hPipeline = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateRayTracingPipelinesNV(pipelineLayout.GetDeviceHandle(), VK_NULL_HANDLE, 1, &CreateInfo, nullptr, &hPipeline));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(pipelineLayout.GetDeviceHandle(), hPipeline);
	}

	return eResult;
}


RayTracingPipelineNV::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hPipeline, nullptr);
	}
}