/*************************************************************************
**********************    VisualVk_CommandBuffer    **********************
*************************************************************************/
#pragma once

#include <set>
#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*************************    CommandQueue    *************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan command queue object.
	 */
	class CommandQueue
	{

	private:

		//!	@brief	Created by logical device only.
		friend class LogicalDevice;

		//!	@brief	Create command queue object.
		CommandQueue(uint32_t familyIndex, Flags<QueueCapability> eCapabilityFlags, float priority);

		//!	@brief	Destroy command queue object.
		~CommandQueue() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		operator VkQueue() const { return m_hQueue; }

		//!	@brief	Return the queue priority.
		float GetPriority() const { return m_Priority; }

		//!	@brief	Wait for a queue to become idle.
		void WaitIdle() const { vkQueueWaitIdle(m_hQueue); }

		//!	@brief	Return the queue family index.
		uint32_t GetFamilyIndex() const { return m_FamilyIndex; }

		//!	@brief	If queue is ready to work.
		bool IsReady() const { return m_hQueue != VK_NULL_HANDLE; }

		//!	@brief	If this queue has the specify capability.
		bool Has(QueueCapability eCapability) const { return (m_CapabilityFlags & eCapability) != 0; }

		//!	@brief	Create a new command pool object.
		CommandPool * CreateCommandPool(Flags<CommandPoolUsageBehavior> eBehaviors = CommandPoolUsageBehavior::eResetCommandBuffer);

		//!	@brief	Queue an image for presentation.
		Result Present(const VkPresentInfoKHR * pPresentInfo) { return static_cast<Result>(vkQueuePresentKHR(m_hQueue, pPresentInfo)); }

		//!	@brief	Destroy a command pool object.
		Result DestroyCommandPool(CommandPool * pCommandPool);

	private:

		VkQueue							m_hQueue;

		VkDevice						m_hDevice;

		const float						m_Priority;

		const uint32_t					m_FamilyIndex;

		std::set<CommandPool*>			m_pCommandPools;

		const Flags<QueueCapability>	m_CapabilityFlags;
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

		//!	@brief	Created by command queue only.
		friend class CommandQueue;

		//!	@brief	Create command pool object.
		CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool);

		//!	@brief	Destroy command pool object.
		~CommandPool() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		operator VkCommandPool() const { return m_hCommandPool; }

		//!	@brief	Reset command pool.
		Result Reset() { return static_cast<Result>(vkResetCommandPool(m_hDevice, m_hCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)); }

		//!	@brief	Free command buffer.
		Result FreeCommandBuffer(CommandBuffer * pCommandBuffer);

		//!	@brief	Allocate a primary command buffer from command pool.
		CommandBuffer * AllocatePrimaryCommandBuffer();

	private:

		const VkQueue					m_hQueue;

		const VkDevice					m_hDevice;

		const VkCommandPool				m_hCommandPool;

		std::set<CommandBuffer*>		m_pCommandBuffers;
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

		//!	@brief	Created by command pool only.
		friend class CommandPool;

		//!	@brief	Create command buffer object.
		CommandBuffer(VkQueue hQueue, VkCommandBuffer hCommandBuffer);

		//!	@brief	Destroy command buffer object.
		~CommandBuffer() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		operator VkCommandBuffer() const { return m_hCommandBuffer; }

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
		VkResult Submit(VkSemaphore hWaitSemaphore, Flags<PipelineStage> eWaitDstStageMask, VkSemaphore hSignalSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= uint32_t(hSignalSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.waitSemaphoreCount		= uint32_t(hWaitSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.pWaitDstStageMask		= reinterpret_cast<const VkPipelineStageFlags*>(&eWaitDstStageMask);
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
		void CmdCopyBufferToImage(VkBuffer hSrcBuffer, VkImage hDstImage, ImageLayout eDstImageLayout, uint32_t RegionCount, const VkBufferImageCopy * pRegions)
		{
			vkCmdCopyBufferToImage(m_hCommandBuffer, hSrcBuffer, hDstImage, static_cast<VkImageLayout>(eDstImageLayout), RegionCount, pRegions);
		}

		//!	@brief	Insert a memory dependency.
		void CmdPipelineBarrier(Flags<PipelineStage> SrcStageMask,
								Flags<PipelineStage> DstStageMask, Flags<DependencyFlagBits> DependencyFlags,
								uint32_t MemoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers,
								uint32_t BufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers,
								uint32_t ImageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, SrcStageMask, DstStageMask, DependencyFlags,
								 MemoryBarrierCount, pMemoryBarriers, BufferMemoryBarrierCount, pBufferMemoryBarriers,
								 ImageMemoryBarrierCount, pImageMemoryBarriers);
		}

		//!	@brief	Insert a image memory dependency.
		void CmdPipelineImageMemoryBarrier(Flags<PipelineStage> SrcStageMask,
										   Flags<PipelineStage> DstStageMask, Flags<DependencyFlagBits> DependencyFlags,
										   uint32_t ImageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, SrcStageMask, DstStageMask, DependencyFlags, 0, nullptr, 0, nullptr, ImageMemoryBarrierCount, pImageMemoryBarriers);
		}

		//!	@brief	Clear regions of a color image.
		void CmdClearColorImage(VkImage hImage, ImageLayout eImageLayout, const VkClearColorValue * pColor,
								uint32_t RangeCount, const VkImageSubresourceRange * pRanges)
		{
			vkCmdClearColorImage(m_hCommandBuffer, hImage, static_cast<VkImageLayout>(eImageLayout), pColor, RangeCount, pRanges);
		}

		//!	@brief	Begin a new render pass.
		void CmdBeginRenderPass(const VkRenderPassBeginInfo * pRenderPassBegin)
		{
			vkCmdBeginRenderPass(m_hCommandBuffer, pRenderPassBegin, VK_SUBPASS_CONTENTS_INLINE);
		}

		//!	@brief	Bind a graphics pipeline object to a command buffer.
		void CmdBindGraphicsPipeline(VkPipeline hPipeline)
		{
			vkCmdBindPipeline(m_hCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, hPipeline);
		}

		//!	@brief	Bind a compute pipeline object to a command buffer.
		void CmdBindComputePipeline(VkPipeline hPipeline)
		{
			vkCmdBindPipeline(m_hCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, hPipeline);
		}

		//!	@brief	Bind a ray-tracing pipeline object to a command buffer.
		void CmdBindRayTracingPipeline(VkPipeline hPipeline)
		{
			vkCmdBindPipeline(m_hCommandBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_NV, hPipeline);
		}

		//!	@brief	Draw primitives.
		void CmdDraw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t FirstVertex, uint32_t FirstInstance)
		{
			vkCmdDraw(m_hCommandBuffer, VertexCount, InstanceCount, FirstVertex, FirstInstance);
		}

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(VkViewport Viewport) { vkCmdSetViewport(m_hCommandBuffer, 0, 1, &Viewport); }

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(float X, float Y, float Width, float Height, float MinDepth = 0.0f, float MaxDepth = 1.0f)
		{
			VkViewport Viewport = { X, Y, Width, Height, MinDepth, MaxDepth };

			vkCmdSetViewport(m_hCommandBuffer, 0, 1, &Viewport);
		}

		//!	@brief	Set the viewports on a command buffer.
		void CmdSetViewports(uint32_t FirstViewport, uint32_t ViewportCount, const VkViewport * pViewports)
		{
			vkCmdSetViewport(m_hCommandBuffer, FirstViewport, ViewportCount, pViewports);
		}

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(VkRect2D Scissor) { vkCmdSetScissor(m_hCommandBuffer, 0, 1, &Scissor); }

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(VkOffset2D Offset, VkExtent2D Extent) { VkRect2D Scissor = { Offset, Extent }; vkCmdSetScissor(m_hCommandBuffer, 0, 1, &Scissor); }

		//!	@brief	Set the dynamic scissors rectangles on a command buffer.
		void CmdSetScissors(uint32_t FirstScissor, uint32_t ScissorCount, const VkRect2D * pScissors)
		{
			vkCmdSetScissor(m_hCommandBuffer, FirstScissor, ScissorCount, pScissors);
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSet(PipelineBindPoint ePipelineBindPoint, VkPipelineLayout hLayout, VkDescriptorSet hDescriptorSet)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, static_cast<VkPipelineBindPoint>(ePipelineBindPoint), hLayout, 0, 1, &hDescriptorSet, 0, nullptr);
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSets(PipelineBindPoint ePipelineBindPoint,
								   VkPipelineLayout hLayout, uint32_t FirstSet,
								   uint32_t DescriptorSetCount, const VkDescriptorSet * pDescriptorSets,
								   uint32_t DynamicOffsetCount, const uint32_t * pDynamicOffsets)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, static_cast<VkPipelineBindPoint>(ePipelineBindPoint), hLayout,
									FirstSet, DescriptorSetCount, pDescriptorSets, DynamicOffsetCount, pDynamicOffsets);
		}

		//!	@brief	Issue an indexed draw into a command buffer.
		void CmdDrawIndexed(uint32_t IndexCount, uint32_t InstanceCount, uint32_t FirstIndex = 0, int32_t VertexOffset = 0, uint32_t FirstInstance = 0)
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

		//!	@brief	Bind an uint16 index buffer to a command buffer.
		void CmdBindIndexBufferUint16(VkBuffer hBuffer, VkDeviceSize Offset = 0)
		{
			vkCmdBindIndexBuffer(m_hCommandBuffer, hBuffer, Offset, VK_INDEX_TYPE_UINT16);
		}

		//!	@brief	Bind an uint32 index buffer to a command buffer.
		void CmdBindIndexBufferUint32(VkBuffer hBuffer, VkDeviceSize Offset = 0)
		{
			vkCmdBindIndexBuffer(m_hCommandBuffer, hBuffer, Offset, VK_INDEX_TYPE_UINT32);
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