/*************************************************************************
**********************    VisualVk_CommandBuffer    **********************
*************************************************************************/
#pragma once

#include <set>
#include <vulkan/vulkan_core.h>

namespace Vk
{
	class CommandPool;
	class CommandBuffer;

	/*********************************************************************
	*************************    CommandQueue    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command queue object.
	 */
	class CommandQueue
	{

	private:

		friend class LogicalDevice;

		friend class PhysicalDevice;

		//!	@brief	Create command queue object.
		CommandQueue(VkDevice hDevice, VkQueue hQueue, uint32_t QueueFamilyIndex, VkQueueFlags eFlags);

		//!	@brief	Destroy command queue object.
		~CommandQueue() noexcept;

	public:

		//!	@brief	Wait for a queue to become idle.
		void WaitIdle() { vkQueueWaitIdle(m_hQueue); }

		//!	@brief	Return the queue flags.
		VkQueueFlags GetFlags() const { return m_QueueFlags; }

		//!	@brief	Return the queue family index.
		uint32_t GetFamilyIndex() const { return m_FamilyIdx; }

		//!	@brief	Create a new command pool object.
		CommandPool * CreateCommandPool(VkCommandPoolCreateFlags eCreateFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

		//!	@brief	Destroy a command pool object.
		VkResult DestroyCommandPool(CommandPool * pCommandPool);

		//!	@brief	Queue an image for presentation.
		VkResult Present(const VkPresentInfoKHR * pPresentInfo)
		{
			return vkQueuePresentKHR(m_hQueue, pPresentInfo);
		}

	private:

		const VkQueue					m_hQueue;

		const VkDevice					m_hDevice;

		const uint32_t					m_FamilyIdx;

		const VkQueueFlags				m_QueueFlags;

		std::set<CommandPool*>			m_pCommandPools;
	};

	/*********************************************************************
	*************************    CommandPool    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command pool object.
	 */
	class CommandPool
	{

	private:

		friend class CommandQueue;

		//!	@brief	Create command pool object.
		CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool);

		//!	@brief	Destroy command pool object.
		~CommandPool() noexcept;

	public:

		//!	@brief	Allocate a primary command buffer from command pool.
		CommandBuffer * AllocateCommandBuffer();

		//!	@brief	Reset command pool.
		VkResult Reset() { return vkResetCommandPool(m_hDevice, m_hCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT); }

		//!	@brief	Free command buffer.
		VkResult FreeCommandBuffer(CommandBuffer * pCommandBuffer);

	private:

		const VkQueue				m_hQueue;

		const VkDevice				m_hDevice;

		const VkCommandPool			m_hCommandPool;

		std::set<CommandBuffer*>	m_pCommandBuffers;
	};

	/*********************************************************************
	************************    CommandBuffer    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command buffer object.
	 */
	class CommandBuffer
	{

	private:

		friend class CommandPool;

		//!	@brief	Create command buffer object.
		CommandBuffer(VkQueue hQueue, VkCommandBuffer hCommandBuffer);

		//!	@brief	Destroy command buffer object.
		~CommandBuffer() noexcept;

	public:

		//!	@brief	Finish recording command buffer.
		VkResult EndRecord() { return vkEndCommandBuffer(m_hCommandBuffer); }

		//!	@brief	Start recording command buffer.
		VkResult BeginRecord(VkCommandBufferUsageFlags eUsageFlags = 0)
		{
			VkCommandBufferBeginInfo BeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, eUsageFlags, nullptr };

			return vkBeginCommandBuffer(m_hCommandBuffer, &BeginInfo);
		}

		//!	@brief	Reset command buffer to the initial state.
		VkResult Reset(VkCommandBufferResetFlags eResetFlags = 0) { return vkResetCommandBuffer(m_hCommandBuffer, eResetFlags); }

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		VkResult Submit(VkSemaphore hWaitSemaphore, VkPipelineStageFlags eWaitDstStageMask, VkSemaphore hSignalSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= uint32_t(hSignalSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.waitSemaphoreCount		= uint32_t(hWaitSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.pWaitDstStageMask		= &eWaitDstStageMask;
			m_SubmitInfo.pSignalSemaphores		= &hSignalSemaphore;
			m_SubmitInfo.pWaitSemaphores		= &hWaitSemaphore;

			return vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence);
		}

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		VkResult Submit(VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= 0;
			m_SubmitInfo.waitSemaphoreCount		= 0;
			m_SubmitInfo.pWaitDstStageMask		= nullptr;
			m_SubmitInfo.pSignalSemaphores		= nullptr;
			m_SubmitInfo.pWaitSemaphores		= nullptr;

			return vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence);
		}

	public:

		//!	@brief	End the current render pass.
		void CmdEndRenderPass() { vkCmdEndRenderPass(m_hCommandBuffer); }

		//!	@brief	Copy data between buffer regions.
		void CmdCopyBuffer(VkBuffer hDstBuffer, VkBuffer hSrcBuffer, uint32_t RegionCount, const VkBufferCopy * pRegions)
		{
			vkCmdCopyBuffer(m_hCommandBuffer, hSrcBuffer, hDstBuffer, RegionCount, pRegions);
		}

		//!	@brief	Copy data from a buffer into an image.
		void CmdCopyBufferToImage(VkBuffer hSrcBuffer, VkImage hDstImage, VkImageLayout eDstImageLayout, uint32_t RegionCount, const VkBufferImageCopy * pRegions)
		{
			vkCmdCopyBufferToImage(m_hCommandBuffer, hSrcBuffer, hDstImage, eDstImageLayout, RegionCount, pRegions);
		}

		//!	@brief	Insert a memory dependency.
		void CmdPipelineBarrier(VkPipelineStageFlags SrcStageMask,
								VkPipelineStageFlags DstStageMask, VkDependencyFlags DependencyFlags,
								uint32_t MemoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers,
								uint32_t BufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers,
								uint32_t ImageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, SrcStageMask, DstStageMask, DependencyFlags,
								 MemoryBarrierCount, pMemoryBarriers, BufferMemoryBarrierCount, pBufferMemoryBarriers,
								 ImageMemoryBarrierCount, pImageMemoryBarriers);
		}

		//!	@brief	Insert a image memory dependency.
		void CmdPipelineImageMemoryBarrier(VkPipelineStageFlags SrcStageMask,
										   VkPipelineStageFlags DstStageMask, VkDependencyFlags DependencyFlags,
										   uint32_t ImageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, SrcStageMask, DstStageMask, DependencyFlags, 0, nullptr, 0, nullptr, ImageMemoryBarrierCount, pImageMemoryBarriers);
		}

		//!	@brief	Clear regions of a color image.
		void CmdClearColorImage(VkImage hImage, VkImageLayout hImageLayout, const VkClearColorValue * pColor,
								uint32_t RangeCount, const VkImageSubresourceRange * pRanges)
		{
			vkCmdClearColorImage(m_hCommandBuffer, hImage, hImageLayout, pColor, RangeCount, pRanges);
		}

		//!	@brief	Begin a new render pass.
		void CmdBeginRenderPass(const VkRenderPassBeginInfo * pRenderPassBegin, VkSubpassContents eContents)
		{
			vkCmdBeginRenderPass(m_hCommandBuffer, pRenderPassBegin, eContents);
		}

		//!	@brief	Bind a pipeline object to a command buffer.
		void CmdBindPipeline(VkPipelineBindPoint ePipelineBindPoint, VkPipeline hPipeline)
		{
			vkCmdBindPipeline(m_hCommandBuffer, ePipelineBindPoint, hPipeline);
		}

		//!	@brief	Draw primitives.
		void CmdDraw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance)
		{
			vkCmdDraw(m_hCommandBuffer, VertexCount, InstanceCount, FirstVertex, FirstInstance);
		}

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(VkViewport Viewport) { vkCmdSetViewport(m_hCommandBuffer, 0, 1, &Viewport); }

		//!	@brief	Set the viewports on a command buffer.
		void CmdSetViewports(uint32_t FirstViewport, uint32_t ViewportCount, const VkViewport * pViewports)
		{
			vkCmdSetViewport(m_hCommandBuffer, FirstViewport, ViewportCount, pViewports);
		}

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(VkRect2D Scissor) { vkCmdSetScissor(m_hCommandBuffer, 0, 1, &Scissor); }

		//!	@brief	Set the dynamic scissors rectangles on a command buffer.
		void CmdSetScissors(uint32_t FirstScissor, uint32_t ScissorCount, const VkRect2D * pScissors)
		{
			vkCmdSetScissor(m_hCommandBuffer, FirstScissor, ScissorCount, pScissors);
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSet(VkPipelineBindPoint ePipelineBindPoint, VkPipelineLayout hLayout, VkDescriptorSet hDescriptorSet)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, ePipelineBindPoint, hLayout, 0, 1, &hDescriptorSet, 0, nullptr);
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSets(VkPipelineBindPoint ePipelineBindPoint,
								   VkPipelineLayout hLayout, uint32_t FirstSet,
								   uint32_t DescriptorSetCount, const VkDescriptorSet * pDescriptorSets,
								   uint32_t DynamicOffsetCount, const uint32_t * pDynamicOffsets)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, ePipelineBindPoint, hLayout, FirstSet,
									DescriptorSetCount, pDescriptorSets, DynamicOffsetCount, pDynamicOffsets);
		}

		//!	@brief	Issue an indexed draw into a command buffer.
		void CmdDrawIndexed(uint32_t IndexCount, uint32_t InstanceCount, uint32_t FirstIndex, int32_t VertexOffset, uint32_t FirstInstance)
		{
			vkCmdDrawIndexed(m_hCommandBuffer, IndexCount, InstanceCount, FirstIndex, VertexOffset, FirstInstance);
		}

		//!	@brief	Bind vertex buffers to a command buffer.
		void CmdBindVertexBuffers(uint32_t FirstBinding, uint32_t BindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets)
		{
			vkCmdBindVertexBuffers(m_hCommandBuffer, FirstBinding, BindingCount, pBuffers, pOffsets);
		}

		//!	@brief	Bind vertex buffer to a command buffer.
		void CmdBindVertexBuffer(uint32_t Binding, VkBuffer hBuffer, VkDeviceSize Offset = 0)
		{
			vkCmdBindVertexBuffers(m_hCommandBuffer, Binding, 1, &hBuffer, &Offset);
		}

		//!	@brief	Bind an index buffer to a command buffer.
		void CmdBindIndexBuffer(VkBuffer hBuffer, VkIndexType eIndexType, VkDeviceSize Offset)
		{
			vkCmdBindIndexBuffer(m_hCommandBuffer, hBuffer, Offset, eIndexType);
		}
		
		//!	@brief	Execute a secondary command buffer from a primary command buffer.
		void CmdExecuteCommands(uint32_t CommandBufferCount, const VkCommandBuffer * pCommandBuffers)
		{
			vkCmdExecuteCommands(m_hCommandBuffer, CommandBufferCount, pCommandBuffers);
		}

		//!	@brief	Set the depth bias dynamic state.
		void CmdSetDepthBias(float DepthBiasConstantFactor, float DepthBiasClamp, float DepthBiasSlopeFactor)
		{
			vkCmdSetDepthBias(m_hCommandBuffer, DepthBiasConstantFactor, DepthBiasClamp, DepthBiasSlopeFactor);
		}

		//!	@brief	Set the dynamic line width state.
		void CmdSetLineWidth(float LineWidth)
		{
			vkCmdSetLineWidth(m_hCommandBuffer, LineWidth);
		}

	private:

		const VkQueue					m_hQueue;

		const VkCommandBuffer			m_hCommandBuffer;

		VkSubmitInfo					m_SubmitInfo;
	};
}