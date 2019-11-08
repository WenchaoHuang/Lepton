/*************************************************************************
***********************    Lava_ComputePipeline    ***********************
*************************************************************************/

#include "ComputePipeline.h"

using namespace Lava;

/*************************************************************************
*************************    ComputePipeline    **************************
*************************************************************************/
ComputePipeline::UniqueHandle::UniqueHandle(VkDevice hDevice, VkPipeline hPipeline)
	: m_hDevice(hDevice), m_hPipeline(hPipeline)
{

}


ComputePipeline::UniqueHandle::~UniqueHandle() noexcept
{
	if (m_hPipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(m_hDevice, m_hPipeline, nullptr);
	}
}