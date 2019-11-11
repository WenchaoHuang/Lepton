/*************************************************************************
*********************    Lava_RayTracingPipeline    **********************
*************************************************************************/

#include "RayTracingPipeline.h"

using namespace Lava;

/*************************************************************************
************************    RayTracingPipeline    ************************
*************************************************************************/
RayTracingPipeline::UniqueHandle::UniqueHandle(VkDevice hDevice, VkPipeline hPipeline)
	: m_hDevice(hDevice), m_hPipeline(hPipeline)
{

}


Result RayTracingPipeline::Create()
{
	VkRayTracingPipelineCreateInfoNV		CreateInfo = {};
	CreateInfo.sType						;
	CreateInfo.pNext						;
	CreateInfo.flags						;
	CreateInfo.stageCount					;
	CreateInfo.pStages						;
	CreateInfo.groupCount					;
	CreateInfo.pGroups						;
	CreateInfo.maxRecursionDepth			;
	CreateInfo.layout						;
	CreateInfo.basePipelineHandle			;
	CreateInfo.basePipelineIndex			;

//	VkPipeline hPipeline = VK_NULL_HANDLE;
}


RayTracingPipeline::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hPipeline, nullptr);
	}
}