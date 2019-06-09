/*************************************************************************
**********************    VisualVk_LogicalDevice    **********************
*************************************************************************/
#pragma once

#include <vector>
#include <vulkan/vulkan_core.h>

/////////////////////////////////////////////////////////////////////////////////////////
																						\
#define VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(name)								\
																						\
void Destroy##name(Vk##name h##name) { vkDestroy##name(m_hDevice, h##name, nullptr); }	\
																						\
VkResult Create##name(const Vk##name##CreateInfo * pCreateInfo, Vk##name * p##name)		\
{																						\
	return vkCreate##name(m_hDevice, pCreateInfo, nullptr, p##name);					\
}																						\
/////////////////////////////////////////////////////////////////////////////////////////

namespace Vk
{
	class CommandQueue;

	using VkSwapchainKHRCreateInfo = VkSwapchainCreateInfoKHR;

	/*********************************************************************
	************************    LogicalDevice    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan logical device object.
	 */
	class LogicalDevice
	{

	private:

		friend class PhysicalDevice;

		//!	@brief	Create logical device object.
		LogicalDevice(VkDevice hDevice,
					  CommandQueue * pComputeQueue,
					  CommandQueue * pGraphicsQueue,
					  CommandQueue * pTransferQueue,
					  std::vector<CommandQueue*> pCommandQueues);

		//!	@brief	Destroy logical device object.
		~LogicalDevice() noexcept;

	public:

		//!	@brief	Wait for a device to become idle.
		VkResult WaitIdle() { return vkDeviceWaitIdle(m_hDevice); }

		//!	@brief	Return pointer to compute command queue.
		CommandQueue * GetComputeQueue() const { return m_pComputeQueue; }

		//!	@brief	Return pointer to graphics command queue.
		CommandQueue * GetGraphicsQueue() const { return m_pGraphicsQueue; }

		//!	@brief	Return pointer to transfer command queue.
		CommandQueue * GetTransferQueue() const { return m_pTransferQueue; }

		//!	@brief	Return a device level function pointer for a command.
		PFN_vkVoidFunction GetProcAddress(const char * pName) const
		{
			return vkGetDeviceProcAddr(m_hDevice, pName);
		}

		//!	@brief	Return pointer to command queue.
		CommandQueue * GetCommandQueue(uint32_t FamilyIndex)
		{
			if (FamilyIndex < m_pCommandQueues.size())
			{
				return m_pCommandQueues[FamilyIndex];
			}

			return nullptr;
		}

	public:

		/*****************************************************************
		*********************    Create & Destroy    *********************
		*****************************************************************/

		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Fence)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Event)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Image)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Buffer)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Sampler)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(ImageView)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Semaphore)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(QueryPool)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(BufferView)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(RenderPass)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(Framebuffer)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(ShaderModule)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(SwapchainKHR)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(PipelineCache)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(PipelineLayout)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(DescriptorPool)
		VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION(DescriptorSetLayout)

		/*****************************************************************
		**************************    Fence    ***************************
		*****************************************************************/

		//!	@brief	Return the status of a fence.
		VkResult GetFenceStatus(VkFence hFence) { return vkGetFenceStatus(m_hDevice, hFence); }

		//!	@brief	Wait for one or more fences to become signaled.
		VkResult WaitForFences(uint32_t FenceCount, const VkFence * pFences, VkBool32 bWaitAll, uint64_t Timeout)
		{
			return vkWaitForFences(m_hDevice, FenceCount, pFences, bWaitAll, Timeout);
		}

		//!	@brief	Resets one or more fences object.
		VkResult ResetFences(uint32_t FenceCount, const VkFence * pFences)
		{
			return vkResetFences(m_hDevice, FenceCount, pFences);
		}

		/*****************************************************************
		**************************    Event    ***************************
		*****************************************************************/

		//!	@brief	Set an event to signaled state.
		VkResult SetEvent(VkEvent hEvent) { return vkSetEvent(m_hDevice, hEvent); }

		//!	@brief	Reset an event to non-signaled state.
		VkResult ResetEvent(VkEvent hEvent) { return vkResetEvent(m_hDevice, hEvent); }

		//!	@brief	Retrieve the status of an event object.
		VkResult GetEventStatus(VkEvent hEvent) { return vkGetEventStatus(m_hDevice, hEvent); }

		/*****************************************************************
		************************    Swapchain    *************************
		*****************************************************************/

		//!	@brief	Obtain the array of presentable images associated with a swapchain.
		VkResult GetSwapchainImages(VkSwapchainKHR hSwapchain, std::vector<VkImage> & hSwapchainImages);

		//!	@brief	Retrieve the index of the next available presentable image.
		VkResult AcquireNextImage(VkSwapchainKHR hSwapchain, uint64_t Timeout, VkSemaphore hSemaphore, VkFence hFence, uint32_t * pImageIndex)
		{
			return vkAcquireNextImageKHR(m_hDevice, hSwapchain, Timeout, hSemaphore, hFence, pImageIndex);
		}

		/*****************************************************************
		***********************    DeviceMemory    ***********************
		*****************************************************************/

		//!	@brief	Unmap a previously mapped memory object.
		void UnmapMemory(VkDeviceMemory hMemory) { vkUnmapMemory(m_hDevice, hMemory); }

		//!	@brief	Free device memory.
		void FreeMemory(VkDeviceMemory hMemory) { vkFreeMemory(m_hDevice, hMemory, nullptr); }

		//!	@brief	Allocate device memory.
		VkResult AllocateMemory(const VkMemoryAllocateInfo * pAllocateInfo, VkDeviceMemory * pMemory)
		{
			return vkAllocateMemory(m_hDevice, pAllocateInfo, nullptr, pMemory);
		}

		//!	@brief	Map a memory object into application address space.
		VkResult MapMemory(VkDeviceMemory hMemory, VkDeviceSize Offset, VkDeviceSize Size, void ** ppData)
		{
			return vkMapMemory(m_hDevice, hMemory, Offset, Size, 0, ppData);
		}

		//!	@brief	Invalidate ranges of mapped memory objects.
		VkResult InvalidateMappedMemoryRanges(uint32_t MemoryRangeCount, const VkMappedMemoryRange * pMemoryRanges)
		{
			return vkInvalidateMappedMemoryRanges(m_hDevice, MemoryRangeCount, pMemoryRanges);
		}

		//!	@brief	Flush mapped memory ranges.
		VkResult FlushMappedMemoryRanges(uint32_t MemoryRangeCount, const VkMappedMemoryRange * pMemoryRanges)
		{
			return vkFlushMappedMemoryRanges(m_hDevice, MemoryRangeCount, pMemoryRanges);
		}

		/*****************************************************************
		**************************    Buffer    **************************
		*****************************************************************/

		//!	@brief	Returns the memory requirements for buffer object.
		void GetBufferMemoryRequirements(VkBuffer hBuffer, VkMemoryRequirements * pMemoryRequirements)
		{
			vkGetBufferMemoryRequirements(m_hDevice, hBuffer, pMemoryRequirements);
		}

		//!	@brief	Bind device memory to a buffer object.
		VkResult BindBufferMemory(VkBuffer hBuffer, VkDeviceMemory hMemory, VkDeviceSize MemoryOffset)
		{
			return vkBindBufferMemory(m_hDevice, hBuffer, hMemory, MemoryOffset);
		}

		/*****************************************************************
		**************************    Image    ***************************
		*****************************************************************/

		//!	@brief	Returns the memory requirements for image object.
		void GetImageMemoryRequirements(VkImage hImage, VkMemoryRequirements * pMemoryRequirements)
		{
			vkGetImageMemoryRequirements(m_hDevice, hImage, pMemoryRequirements);
		}

		//!	@brief	Bind device memory to an image object.
		VkResult BindImageMemory(VkImage hImage, VkDeviceMemory hMemory, VkDeviceSize MemoryOffset)
		{
			return vkBindImageMemory(m_hDevice, hImage, hMemory, MemoryOffset);
		}

		/*****************************************************************
		*************************    Pipeline    *************************
		*****************************************************************/

		//!	@brief	Destroy a pipeline object.
		void DestroyPipeline(VkPipeline hPipeline) { vkDestroyPipeline(m_hDevice, hPipeline, nullptr); }
		
		//!	@brief	Create compute pipelines.
		VkResult CreateComputePipelines(VkPipelineCache hPipelineCache, uint32_t CreateInfoCount, const VkComputePipelineCreateInfo * pCreateInfos, VkPipeline * pPipelines)
		{
			return vkCreateComputePipelines(m_hDevice, hPipelineCache, CreateInfoCount, pCreateInfos, nullptr, pPipelines);
		}

		//!	@brief	Create graphics pipelines.
		VkResult CreateGraphicsPipelines(VkPipelineCache hPipelineCache, uint32_t CreateInfoCount, const VkGraphicsPipelineCreateInfo * pCreateInfos, VkPipeline * pPipelines)
		{
			return vkCreateGraphicsPipelines(m_hDevice, hPipelineCache, CreateInfoCount, pCreateInfos, nullptr, pPipelines);
		}

		/*****************************************************************
		**********************    DescriptorSet    ***********************
		*****************************************************************/

		//!	@brief	Resets a descriptor pool object, which will return all descriptor sets allocated from a given pool to the pool.
		VkResult ResetDescriptorPool(VkDescriptorPool hDescriptorPool, VkDescriptorPoolResetFlags eFlags)
		{
			return vkResetDescriptorPool(m_hDevice, hDescriptorPool, eFlags);
		}

		//!	@brief	Allocate one or more descriptor sets.
		VkResult AllocateDescriptorSets(const VkDescriptorSetAllocateInfo * pAllocateInfo, VkDescriptorSet * pDescriptorSets)
		{
			return vkAllocateDescriptorSets(m_hDevice, pAllocateInfo, pDescriptorSets);
		}

		//!	@brief	Free one or more descriptor sets.
		VkResult FreeDescriptorSets(VkDescriptorPool hDescriptorPool, uint32_t DescriptorSetCount, const VkDescriptorSet * pDescriptorSets)
		{
			return vkFreeDescriptorSets(m_hDevice, hDescriptorPool, DescriptorSetCount, pDescriptorSets);
		}

		//!	@brief	Update the contents of a descriptor set object.
		void UpdateDescriptorSets(uint32_t DescriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites,
								  uint32_t DescriptorCopyCount, const VkCopyDescriptorSet * pDescriptorCopies)
		{
			vkUpdateDescriptorSets(m_hDevice, DescriptorWriteCount, pDescriptorWrites, DescriptorCopyCount, pDescriptorCopies);
		}

	private:

		const VkDevice						m_hDevice;

		CommandQueue * const				m_pComputeQueue;

		CommandQueue * const				m_pGraphicsQueue;

		CommandQueue * const				m_pTransferQueue;

		const std::vector<CommandQueue*>	m_pCommandQueues;
	};
}

#undef VK_DEVICE_OBJECT_CREATE_AND_DESTROY_FUNCTION