/*************************************************************************
************************    VisualVk_Commands    *************************
*************************************************************************/
#include "Commands.h"

using namespace Vk;

/*************************************************************************
***************************    CommandQueue    ***************************
*************************************************************************/
CommandQueue::CommandQueue(uint32_t familyIndex, Flags<QueueCapability> eCapabilityFlags, float priority)
	: m_hDevice(VK_NULL_HANDLE), m_hQueue(VK_NULL_HANDLE), m_FamilyIndex(familyIndex), m_CapabilityFlags(eCapabilityFlags), m_Priority(priority)
{

}


CommandPool * CommandQueue::CreateCommandPool(Flags<CommandPoolUsageBehavior> eBehaviors)
{
	VkCommandPoolCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= eBehaviors;
	CreateInfo.queueFamilyIndex		= m_FamilyIndex;

	VkCommandPool hCommandPool = VK_NULL_HANDLE;

	if (vkCreateCommandPool(m_hDevice, &CreateInfo, nullptr, &hCommandPool) == VK_SUCCESS)
	{
		CommandPool * pCommandPool = new CommandPool(m_hDevice, m_hQueue, hCommandPool);

		m_pCommandPools.insert(pCommandPool);

		return pCommandPool;
	}

	return nullptr;
}


Result CommandQueue::DestroyCommandPool(CommandPool * pCommandPool)
{
	if (m_pCommandPools.erase(pCommandPool) != 0)
	{
		delete pCommandPool;

		return Result::eSuccess;
	}

	return Result::eErrorInvalidExternalHandle;
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


CommandBuffer * CommandPool::AllocatePrimaryCommandBuffer()
{
	VkCommandBufferAllocateInfo			AllocateInfo = {};
	AllocateInfo.sType					= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	AllocateInfo.pNext					= nullptr;
	AllocateInfo.commandPool			= m_hCommandPool;
	AllocateInfo.level					= VK_COMMAND_BUFFER_LEVEL_PRIMARY;
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


Result CommandPool::FreeCommandBuffer(CommandBuffer * pCommandBuffer)
{
	if (m_pCommandBuffers.erase(pCommandBuffer) != 0)
	{
		vkQueueWaitIdle(m_hQueue);

		VkCommandBuffer hCommandBuffer = pCommandBuffer->m_hCommandBuffer;

		vkFreeCommandBuffers(m_hDevice, m_hCommandPool, 1, &hCommandBuffer);

		delete pCommandBuffer;

		return Result::eSuccess;
	}

	return Result::eErrorInvalidExternalHandle;
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
	m_SubmitInfo.sType						= VK_STRUCTURE_TYPE_SUBMIT_INFO;
	m_SubmitInfo.pNext						= nullptr;
	m_SubmitInfo.waitSemaphoreCount			= 0;
	m_SubmitInfo.pWaitSemaphores			= nullptr;
	m_SubmitInfo.pWaitDstStageMask			= nullptr;
	m_SubmitInfo.commandBufferCount			= 1;
	m_SubmitInfo.pCommandBuffers			= &m_hCommandBuffer;
	m_SubmitInfo.signalSemaphoreCount		= 0;
	m_SubmitInfo.pSignalSemaphores			= nullptr;
}


CommandBuffer::~CommandBuffer() noexcept
{
	
}