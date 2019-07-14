/*************************************************************************
**********************    VisualVk_LogicalDevice    **********************
*************************************************************************/
#include "LogicalDevice.h"
#include "CommandBuffer.h"

using namespace Vk;

/*************************************************************************
**************************    LogicalDevice    ***************************
*************************************************************************/
LogicalDevice::LogicalDevice(VkDevice hDevice,
							 CommandQueue * pComputeQueue,
							 CommandQueue * pGraphicsQueue,
							 CommandQueue * pTransferQueue,
							 PhysicalDevice * pPhysicalDevice,
							 std::vector<CommandQueue*> pCommandQueues)
	:	m_hDevice(hDevice), m_pPhysicalDevice(pPhysicalDevice), m_pCommandQueues(pCommandQueues),
		m_pComputeQueue(pComputeQueue), m_pGraphicsQueue(pGraphicsQueue), m_pTransferQueue(pTransferQueue)
{

}


VkResult LogicalDevice::GetSwapchainImages(VkSwapchainKHR hSwapchain, std::vector<VkImage> & hSwapchainImages)
{
	uint32_t SwapchainImageCount = 0;

	vkGetSwapchainImagesKHR(m_hDevice, hSwapchain, &SwapchainImageCount, nullptr);

	hSwapchainImages.resize(SwapchainImageCount);

	return vkGetSwapchainImagesKHR(m_hDevice, hSwapchain, &SwapchainImageCount, hSwapchainImages.data());
}


LogicalDevice::~LogicalDevice() noexcept
{
	this->WaitIdle();

	vkDestroyDevice(m_hDevice, nullptr);

	for (auto pCommandQueue : m_pCommandQueues)
	{
		delete pCommandQueue;
	}
}