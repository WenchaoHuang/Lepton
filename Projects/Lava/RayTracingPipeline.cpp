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


RayTracingPipeline::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hPipeline, nullptr);
	}
}