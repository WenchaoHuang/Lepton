/*************************************************************************
**********************    VisualVk_CommandBuffer    **********************
*************************************************************************/
#include "CommandBuffer.h"

using namespace Vk;

/*************************************************************************
***************************    CommandQueue    ***************************
*************************************************************************/
CommandQueue::CommandQueue(VkDevice hDevice, VkQueue hQueue, uint32_t QueueFamilyIndex, VkQueueFlags eFlags)
	: m_hDevice(hDevice), m_hQueue(hQueue), m_FamilyIdx(QueueFamilyIndex), m_QueueFlags(eFlags)
{

}


CommandPool * CommandQueue::CreateCommandPool(VkCommandPoolCreateFlags eCreateFlags)
{
	VkCommandPoolCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= eCreateFlags;
	CreateInfo.queueFamilyIndex		= m_FamilyIdx;

	VkCommandPool hCommandPool = VK_NULL_HANDLE;

	if (vkCreateCommandPool(m_hDevice, &CreateInfo, nullptr, &hCommandPool) == VK_SUCCESS)
	{
		CommandPool * pCommandPool = new CommandPool(m_hDevice, m_hQueue, hCommandPool);

		m_pCommandPools.insert(pCommandPool);

		return pCommandPool;
	}

	return nullptr;
}


VkResult CommandQueue::DestroyCommandPool(CommandPool * pCommandPool)
{
	if (m_pCommandPools.erase(pCommandPool) != 0)
	{
		delete pCommandPool;

		return VK_SUCCESS;
	}

	return VK_ERROR_INVALID_EXTERNAL_HANDLE;
}


CommandQueue::~CommandQueue() noexcept
{
	for (auto pCommandPool : m_pCommandPools)
	{
		delete pCommandPool;
	}
}


/*************************************************************************
***************************    CommandPool    ****************************
*************************************************************************/
CommandPool::CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool)
	: m_hDevice(hDevice), m_hQueue(hQueue), m_hCommandPool(hCommnadPool)
{

}


CommandBuffer * CommandPool::AllocateCommandBuffer(VkCommandBufferLevel eLevel)
{
	VkCommandBufferAllocateInfo			AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.commandPool			= m_hCommandPool;
	AllocateInfo.level					= eLevel;
	AllocateInfo.commandBufferCount		= 1;

	VkCommandBuffer hCommandBuffer = VK_NULL_HANDLE;

	if (vkAllocateCommandBuffers(m_hDevice, &AllocateInfo, &hCommandBuffer) == VK_SUCCESS)
	{
		CommandBuffer * pCommandBuffer = new CommandBuffer(m_hQueue, hCommandBuffer);

		m_pCommandBuffers.insert(pCommandBuffer);

		return pCommandBuffer;
	}

	return nullptr;
}


VkResult CommandPool::FreeCommandBuffer(CommandBuffer * pCommandBuffer)
{
	if (m_pCommandBuffers.erase(pCommandBuffer) != 0)
	{
		VkCommandBuffer hCommandBuffer = pCommandBuffer->m_hCommandBuffer;

		vkFreeCommandBuffers(m_hDevice, m_hCommandPool, 1, &hCommandBuffer);

		delete pCommandBuffer;

		return VK_SUCCESS;
	}

	return VK_ERROR_INVALID_EXTERNAL_HANDLE;
}


CommandPool::~CommandPool() noexcept
{
	vkDestroyCommandPool(m_hDevice, m_hCommandPool, nullptr);

	for (auto pCommandBuffer : m_pCommandBuffers)
	{
		delete pCommandBuffer;
	}
}


/*************************************************************************
**************************    CommandBuffer    ***************************
*************************************************************************/
CommandBuffer::CommandBuffer(VkQueue hQueue, VkCommandBuffer hCommandBuffer)
	: m_hQueue(hQueue), m_hCommandBuffer(hCommandBuffer)
{
	m_SubmitInfo.sType					= VK_STRUCTURE_TYPE_SUBMIT_INFO;
	m_SubmitInfo.pNext					= nullptr;
	m_SubmitInfo.waitSemaphoreCount		= 0;
	m_SubmitInfo.pWaitSemaphores		= nullptr;
	m_SubmitInfo.pWaitDstStageMask		= nullptr;
	m_SubmitInfo.commandBufferCount		= 1;
	m_SubmitInfo.pCommandBuffers		= &m_hCommandBuffer;
	m_SubmitInfo.signalSemaphoreCount	= 0;
	m_SubmitInfo.pSignalSemaphores		= nullptr;
}


void CommandBuffer::SetWaitSignalSemaphores(uint32_t SignalSemaphoreCount,
											const VkSemaphore * pSignalSemaphores,
											const VkPipelineStageFlags * pWaitDstStageMask)
{
	m_SubmitInfo.waitSemaphoreCount		= SignalSemaphoreCount;
	m_SubmitInfo.pWaitSemaphores		= pSignalSemaphores;
	m_SubmitInfo.pWaitDstStageMask		= pWaitDstStageMask;
}


void CommandBuffer::SetSignalSemaphores(uint32_t SignalSemaphoreCount, const VkSemaphore * pSignalSemaphores)
{
	m_SubmitInfo.signalSemaphoreCount	= SignalSemaphoreCount;
	m_SubmitInfo.pSignalSemaphores		= pSignalSemaphores;
}