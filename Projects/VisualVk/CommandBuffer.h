/*************************************************************************
**********************    VisualVk_CommandBuffer    **********************
*************************************************************************/
#pragma once

#include <set>
#include "Common.h"

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
	class VKAPI CommandQueue
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

		//!	@brief	Return queue flags.
		VkQueueFlags GetFlags() const { return m_QueueFlags; }

		//!	@brief	Return queue family index.
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
	class VKAPI CommandPool
	{

	private:

		friend class CommandQueue;

		//!	@brief	Create command pool object.
		CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool);

		//!	@brief	Destroy command pool object.
		~CommandPool() noexcept;

	public:

		//!	@brief	Free command buffer.
		VkResult FreeCommandBuffer(CommandBuffer * pCommandBuffer);

		//!	@brief	Allocate command buffer from command pool.
		CommandBuffer * AllocateCommandBuffer(VkCommandBufferLevel eLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

		//!	@brief	Reset command pool.
		VkResult Reset() { return vkResetCommandPool(m_hDevice, m_hCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT); }

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
	class VKAPI CommandBuffer
	{

	private:

		friend class CommandPool;

		//!	@brief	Create command buffer object.
		CommandBuffer(VkQueue hQueue, VkCommandBuffer hCommandBuffer);

		//!	@brief	Destroy command buffer object.
		~CommandBuffer() noexcept {}

	public:

		void SetWaitSignalSemaphores(uint32_t nSignalSemaphoreCount,
									 const VkSemaphore * pSignalSemaphores,
									 const VkPipelineStageFlags * pWaitDstStageMask);

		void SetSignalSemaphores(uint32_t nSignalSemaphoreCount, const VkSemaphore * pSignalSemaphores);

	public:

		//!	@brief	Finish recording command buffer.
		VkResult End() { return vkEndCommandBuffer(m_hCommandBuffer); }

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		VkResult Submit(VkFence hFence = VK_NULL_HANDLE)
		{
			return vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence);
		}

		//!	@brief	Reset command buffer to the initial state.
		VkResult Reset(VkCommandBufferResetFlags eResetFlags = 0)
		{
			return vkResetCommandBuffer(m_hCommandBuffer, eResetFlags);
		}

		//!	@brief	Start recording command buffer.
		VkResult Begin(VkCommandBufferUsageFlags eUsageFlags = 0)
		{
			VkCommandBufferBeginInfo BeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, eUsageFlags, nullptr };

			return vkBeginCommandBuffer(m_hCommandBuffer, &BeginInfo);
		}

	public:

		//!	@brief	End the current render pass.
		void CmdEndRenderPass() { vkCmdEndRenderPass(m_hCommandBuffer); }

		//!	@brief	Copy data between buffer regions.
		void CmdCopyBuffer(VkBuffer hDstBuffer, VkBuffer hSrcBuffer, uint32_t nRegionCount, const VkBufferCopy * pRegions)
		{
			vkCmdCopyBuffer(m_hCommandBuffer, hSrcBuffer, hDstBuffer, nRegionCount, pRegions);
		}

		//!	@brief	Insert a memory dependency.
		void CmdPipelineBarrier(VkPipelineStageFlags SrcStageMask,
								VkPipelineStageFlags DstStageMask, VkDependencyFlags DependencyFlags,
								uint32_t nMemoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers,
								uint32_t nBufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers,
								uint32_t nImageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, SrcStageMask, DstStageMask, DependencyFlags,
								 nMemoryBarrierCount, pMemoryBarriers, nBufferMemoryBarrierCount, pBufferMemoryBarriers,
								 nImageMemoryBarrierCount, pImageMemoryBarriers);
		}

		//!	@brief	Clear regions of a color image.
		void CmdClearColorImage(VkImage hImage, VkImageLayout hImageLayout, const VkClearColorValue * pColor,
								uint32_t nRangeCount, const VkImageSubresourceRange * pRanges)
		{
			vkCmdClearColorImage(m_hCommandBuffer, hImage, hImageLayout, pColor, nRangeCount, pRanges);
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
		void CmdDraw(uint32_t nVertexCount, uint32_t nInstanceCount, uint32_t nFirstVertex, uint32_t nFirstInstance)
		{
			vkCmdDraw(m_hCommandBuffer, nVertexCount, nInstanceCount, nFirstVertex, nFirstInstance);
		}

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(uint32_t nFirstViewport, uint32_t nViewportCount, const VkViewport * pViewports)
		{
			vkCmdSetViewport(m_hCommandBuffer, nFirstViewport, nViewportCount, pViewports);
		}

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(uint32_t nFirstScissor, uint32_t nScissorCount, const VkRect2D * pScissors)
		{
			vkCmdSetScissor(m_hCommandBuffer, nFirstScissor, nScissorCount, pScissors);
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSets(VkPipelineBindPoint ePipelineBindPoint,
								   VkPipelineLayout hLayout, uint32_t nFirstSet,
								   uint32_t nDescriptorSetCount, const VkDescriptorSet * pDescriptorSets,
								   uint32_t nDynamicOffsetCount, const uint32_t * pDynamicOffsets)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, ePipelineBindPoint, hLayout, nFirstSet,
									nDescriptorSetCount, pDescriptorSets, nDynamicOffsetCount, pDynamicOffsets);
		}

		//!	@brief	Bind vertex buffers to a command buffer.
		void CmdBindVertexBuffers(uint32_t nFirstBinding, uint32_t nBindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets)
		{
			vkCmdBindVertexBuffers(m_hCommandBuffer, nFirstBinding, nBindingCount, pBuffers, pOffsets);
		}

		//!	@brief	Bind an index buffer to a command buffer.
		void CmdBindIndexBuffer(VkBuffer hBuffer, VkIndexType eIndexType, VkDeviceSize nOffset)
		{
			vkCmdBindIndexBuffer(m_hCommandBuffer, hBuffer, nOffset, eIndexType);
		}

		//!	@brief	Issue an indexed draw into a command buffer.
		void CmdDrawIndexed(uint32_t nIndexCount, uint32_t nInstanceCount, uint32_t nFirstIndex, int32_t nVertexOffset, uint32_t nFirstInstance)
		{
			vkCmdDrawIndexed(m_hCommandBuffer, nIndexCount, nInstanceCount, nFirstIndex, nVertexOffset, nFirstInstance);
		}

	private:

		const VkQueue					m_hQueue;

		const VkCommandBuffer			m_hCommandBuffer;

		VkSubmitInfo					m_SubmitInfo;
	};
}