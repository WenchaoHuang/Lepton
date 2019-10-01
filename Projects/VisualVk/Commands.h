/*************************************************************************
************************    VisualVk_Commands    *************************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	********************    ImageSubresourceRange    *********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an image subresource range.
	 */
	struct ImageSubresourceRange
	{
		Flags<ImageAspect>		aspectMask			= 0;
		uint32_t				baseMipLevel		= 0;
		uint32_t				levelCount			= 1;
		uint32_t				baseArrayLayer		= 0;
		uint32_t				layerCount			= 1;
	};

	static_assert(sizeof(ImageSubresourceRange) == sizeof(VkImageSubresourceRange), "Struct and wrapper have different size!");

	/*********************************************************************
	********************    ImageSubresourceRange    *********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying the parameters of an image memory barrier.
	 */
	struct ImageMemoryBarrier
	{
		const VkStructureType		sType					= VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		const void * const			pNext					= nullptr;
		Flags<MemoryAccess>			srcAccessMask			= 0;
		Flags<MemoryAccess>			dstAccessMask			= 0;
		ImageLayout					oldLayout				= ImageLayout::eUndefined;
		ImageLayout					newLayout				= ImageLayout::eUndefined;
		const uint32_t				srcQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
		const uint32_t				dstQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
		VkImage						image					= VK_NULL_HANDLE;
		ImageSubresourceRange		subresourceRange		= {};
	};

	static_assert(sizeof(ImageMemoryBarrier) == sizeof(VkImageMemoryBarrier), "Struct and wrapper have different size!");

	/*********************************************************************
	*************************    CommandQueue    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command queue object.
	 */
	class CommandQueue
	{
		friend class LogicalDevice;

	private:

		//!	@brief	Create command queue object.
		CommandQueue(uint32_t familyIndex, Flags<QueueCapability> eCapabilities, float priority);

		//!	@brief	Destroy command queue object.
		~CommandQueue() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkQueue GetHandle() const { return m_hQueue; }

		//!	@brief	Return the queue priority.
		float GetPriority() const { return m_Priority; }

		//!	@brief	Wait for a queue to become idle.
		void WaitIdle() const { vkQueueWaitIdle(m_hQueue); }

		//!	@brief	Return the queue family index.
		uint32_t GetFamilyIndex() const { return m_FamilyIndex; }

		//!	@brief	If queue is ready to work.
		bool IsReady() const { return m_hQueue != VK_NULL_HANDLE; }

		//!	@brief	If this queue has the specify capability.
		bool Has(QueueCapability eCapabilities) const { return (m_eCapabilities & eCapabilities) != 0; }

		//!	@brief	Create a new command pool object.
		CommandPool * CreateCommandPool(Flags<CommandPoolUsageBehavior> eUsageBehaviors = CommandPoolUsageBehavior::eResetCommandBuffer);

		//!	@brief	Destroy a command pool object.
		Result DestroyCommandPool(CommandPool * pCommandPool);

	private:

		VkQueue							m_hQueue;

		VkDevice						m_hDevice;

		const float						m_Priority;

		const uint32_t					m_FamilyIndex;

		std::set<CommandPool*>			m_pCommandPools;

		const Flags<QueueCapability>	m_eCapabilities;
	};

	/*********************************************************************
	*************************    CommandPool    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command pool object.
	 */
	class CommandPool
	{
		friend class CommandQueue;

	private:

		//!	@brief	Create command pool object.
		CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool, Flags<CommandPoolUsageBehavior> eUsageBehaviors);

		//!	@brief	Destroy command pool object.
		~CommandPool() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkCommandPool GetHandle() const { return m_hCommandPool; }

		//!	@brief	Reset command pool.
		Result Reset() { return VK_RESULT_CAST(vkResetCommandPool(m_hDevice, m_hCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)); }

		//!	@brief	Free command buffer.
		Result FreeCommandBuffer(CommandBuffer * pCommandBuffer);

		//!	@brief	Allocate a primary command buffer from command pool.
		CommandBuffer * AllocatePrimaryCommandBuffer();

	private:

		const VkQueue								m_hQueue;

		const VkDevice								m_hDevice;

		const VkCommandPool							m_hCommandPool;

		std::set<CommandBuffer*>					m_pCommandBuffers;
		
		const Flags<CommandPoolUsageBehavior>		m_eUsageBehaviors;
	};

	/*********************************************************************
	************************    CommandBuffer    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command buffer object.
	 */
	class CommandBuffer
	{
		friend class CommandPool;

	private:

		//!	@brief	Create command buffer object.
		CommandBuffer(VkQueue hQueue, VkCommandBuffer hCommandBuffer);

		//!	@brief	Destroy command buffer object.
		~CommandBuffer() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkCommandBuffer GetHandle() const { return m_hCommandBuffer; }

		//!	@brief	Finish recording command buffer.
		Result EndRecord() { return VK_RESULT_CAST(vkEndCommandBuffer(m_hCommandBuffer)); }

		//!	@brief	Start recording command buffer.
		Result BeginRecord(Flags<CommandBufferUsage> eUsages = 0)
		{
			VkCommandBufferBeginInfo BeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, eUsages, nullptr };

			return VK_RESULT_CAST(vkBeginCommandBuffer(m_hCommandBuffer, &BeginInfo));
		}

		//!	@brief	Reset command buffer to the initial state.
		Result Reset(VkCommandBufferResetFlags eResetFlags = 0) { return VK_RESULT_CAST(vkResetCommandBuffer(m_hCommandBuffer, eResetFlags)); }

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		Result Submit(VkSemaphore hWaitSemaphore, Flags<PipelineStage> eWaitDstStageMask, VkSemaphore hSignalSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= uint32_t(hSignalSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.waitSemaphoreCount		= uint32_t(hWaitSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.pWaitDstStageMask		= reinterpret_cast<const VkPipelineStageFlags*>(&eWaitDstStageMask);
			m_SubmitInfo.pSignalSemaphores		= &hSignalSemaphore;
			m_SubmitInfo.pWaitSemaphores		= &hWaitSemaphore;

			return VK_RESULT_CAST(vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence));
		}

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		Result Submit(VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= 0;
			m_SubmitInfo.waitSemaphoreCount		= 0;
			m_SubmitInfo.pWaitDstStageMask		= nullptr;
			m_SubmitInfo.pSignalSemaphores		= nullptr;
			m_SubmitInfo.pWaitSemaphores		= nullptr;

			return VK_RESULT_CAST(vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence));
		}

	public:

		//!	@brief	End the current render pass.
		void CmdEndRenderPass()
		{
			vkCmdEndRenderPass(m_hCommandBuffer);
		}

		//!	@brief	Set the dynamic line width state.
		void CmdSetLineWidth(float lineWidth)
		{
			vkCmdSetLineWidth(m_hCommandBuffer, lineWidth);
		}

		//!	@brief	Set the values of blend constants.
		void CmdSetBlendConstants(const float blendConstants[4])
		{
			vkCmdSetBlendConstants(m_hCommandBuffer, blendConstants);
		}

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(ArrayProxy<const VkRect2D> pScissors, uint32_t firstScissor = 0)
		{
			vkCmdSetScissor(m_hCommandBuffer, firstScissor, pScissors.size(), pScissors.data());
		}

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(ArrayProxy<const VkViewport> pViewports, uint32_t firstViewport = 0)
		{
			vkCmdSetViewport(m_hCommandBuffer, firstViewport, pViewports.size(), pViewports.data());
		}

		//!	@brief	Issue an indirect draw into a command buffer.
		void CmdDrawIndirect(VkBuffer hBuffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
		{
			vkCmdDrawIndirect(m_hCommandBuffer, hBuffer, offset, drawCount, stride);
		}

		//!	@brief	Set the depth bias dynamic state.
		void CmdSetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
		{
			vkCmdSetDepthBias(m_hCommandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
		}

		//!	@brief	Draw primitives.
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex = 0, uint32_t firstInstance = 0)
		{
			vkCmdDraw(m_hCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
		}

		//!	@brief	Begin a new render pass.
		void CmdBeginRenderPass(const Framebuffer * pFramebuffer, VkRect2D renderArea,
								ArrayProxy<const VkClearValue> pClearValues, SubpassContents eContents = SubpassContents::eInline);

		//!	@brief	Insert a image memory dependency.
		void CmdImageMemoryBarrier(Flags<PipelineStage> srcStageMask, Flags<PipelineStage> dstStageMask,
								   Flags<MemoryDependency> dependencyFlags, ArrayProxy<const ImageMemoryBarrier> pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, srcStageMask, dstStageMask, dependencyFlags, 0, nullptr, 0, nullptr,
								 pImageMemoryBarriers.size(), reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers.data()));
		}

		//!	@brief	 Update the values of push constants.
		void CmdPushConstants(VkPipelineLayout hPipelineLayout, Flags<ShaderStage> eStages, uint32_t offset, uint32_t size, const void * pValues)
		{
			vkCmdPushConstants(m_hCommandBuffer, hPipelineLayout, eStages, offset, size, pValues);
		}

		//!	@brief	 Issue an indexed draw into a command buffer.
		void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex = 0, int32_t vertexOffset = 0, uint32_t firstInstance = 0)
		{
			vkCmdDrawIndexed(m_hCommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
		}

		//!	@brief	Clear regions of a color image.
		void CmdClearColorImage(VkImage hImage, ImageLayout eImageLayout, const VkClearColorValue & color, ArrayProxy<const ImageSubresourceRange> pRanges)
		{
			vkCmdClearColorImage(m_hCommandBuffer, hImage, static_cast<VkImageLayout>(eImageLayout), &color,
								 pRanges.size(), reinterpret_cast<const VkImageSubresourceRange*>(pRanges.data()));
		}

		//!	@brief	Copy data from a buffer into an image.
		void CmdCopyBufferToImage(VkBuffer hSrcBuffer, VkImage hDstImage, ImageLayout eDstImageLayout, ArrayProxy<const VkBufferImageCopy> pRegions)
		{
			vkCmdCopyBufferToImage(m_hCommandBuffer, hSrcBuffer, hDstImage, static_cast<VkImageLayout>(eDstImageLayout), pRegions.size(), pRegions.data());
		}

	private:

		const VkQueue					m_hQueue;

		const VkCommandBuffer			m_hCommandBuffer;

		VkSubmitInfo					m_SubmitInfo;
	};
}