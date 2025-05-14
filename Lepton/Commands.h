/*************************************************************************
*************************    Lepton_Commands    **************************
*************************************************************************/
#pragma once

#include "Framebuffer.h"
#include "GraphicsPipeline.h"

namespace Lepton
{
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
		CommandQueue(uint32_t familyIndex, vk::QueueFlags eCapabilities, float priority);

		//!	@brief	Destroy command queue object.
		~CommandQueue() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkQueue Handle() const { return m_hQueue; }

		//!	@brief	Return the queue priority.
		float GetPriority() const { return m_Priority; }

		//!	@brief	Wait for a queue to become idle.
		void WaitIdle() const { vkQueueWaitIdle(m_hQueue); }

		//!	@brief	Return the queue family index.
		uint32_t GetFamilyIndex() const { return m_FamilyIndex; }

		//!	@brief	If queue is ready to work.
		bool IsReady() const { return m_hQueue != VK_NULL_HANDLE; }

		//!	@brief	If this queue has the specify capability.
		bool Has(vk::QueueFlagBits eCapabilities) const { return bool(m_eCapabilities & eCapabilities); }

		//!	@brief	Create a new command pool object.
		CommandPool * CreateCommandPool(vk::CommandPoolCreateFlags eUsageBehaviors = vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

		//!	@brief	Destroy a command pool object.
		Result DestroyCommandPool(CommandPool * pCommandPool);

	private:

		VkQueue								m_hQueue;

		VkDevice							m_hDevice;

		const float							m_Priority;

		const uint32_t						m_FamilyIndex;

		std::set<CommandPool*>				m_pCommandPools;

		const vk::QueueFlags				m_eCapabilities;
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
		CommandPool(VkDevice hDevice, VkQueue hQueue, VkCommandPool hCommnadPool, vk::CommandPoolCreateFlags eUsageBehaviors);

		//!	@brief	Destroy command pool object.
		~CommandPool() noexcept;

	public:

		//!	@brief	Return Vulkan type of this object.
		VkCommandPool Handle() const { return m_hCommandPool; }

		//!	@brief	Reset command pool.
		Result Reset() { return LAVA_RESULT_CAST(vkResetCommandPool(m_hDevice, m_hCommandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)); }

		//!	@brief	Free command buffer.
		Result FreeCommandBuffer(CommandBuffer * pCommandBuffer);

		//!	@brief	Allocate a primary command buffer from command pool.
		CommandBuffer * AllocatePrimaryCommandBuffer();

	private:

		const VkQueue							m_hQueue;

		const VkDevice							m_hDevice;

		const VkCommandPool						m_hCommandPool;

		std::set<CommandBuffer*>				m_pCommandBuffers;
		
		const vk::CommandPoolCreateFlags		m_eUsageBehaviors;
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
		VkCommandBuffer Handle() const { return m_hCommandBuffer; }

		//!	@brief	Finish recording command buffer.
		Result EndRecord() { return LAVA_RESULT_CAST(vkEndCommandBuffer(m_hCommandBuffer)); }

		//!	@brief	Start recording command buffer.
		Result BeginRecord(vk::CommandBufferUsageFlags eUsages = vk::CommandBufferUsageFlagBits(0))
		{
			VkCommandBufferBeginInfo BeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, (VkFlags)eUsages, nullptr };

			return LAVA_RESULT_CAST(vkBeginCommandBuffer(m_hCommandBuffer, &BeginInfo));
		}

		//!	@brief	Reset command buffer to the initial state.
		Result Reset(VkCommandBufferResetFlags eResetFlags = 0) { return LAVA_RESULT_CAST(vkResetCommandBuffer(m_hCommandBuffer, eResetFlags)); }

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		Result Submit(VkSemaphore hWaitSemaphore, vk::PipelineStageFlags eWaitDstStageMask, VkSemaphore hSignalSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= uint32_t(hSignalSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.waitSemaphoreCount		= uint32_t(hWaitSemaphore != VK_NULL_HANDLE);
			m_SubmitInfo.pWaitDstStageMask		= reinterpret_cast<const VkPipelineStageFlags*>(&eWaitDstStageMask);
			m_SubmitInfo.pSignalSemaphores		= &hSignalSemaphore;
			m_SubmitInfo.pWaitSemaphores		= &hWaitSemaphore;

			return LAVA_RESULT_CAST(vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence));
		}

		//!	@brief	Submits a sequence of semaphores or command buffers to a queue.
		Result Submit(VkFence hFence = VK_NULL_HANDLE)
		{
			m_SubmitInfo.signalSemaphoreCount	= 0;
			m_SubmitInfo.waitSemaphoreCount		= 0;
			m_SubmitInfo.pWaitDstStageMask		= nullptr;
			m_SubmitInfo.pSignalSemaphores		= nullptr;
			m_SubmitInfo.pWaitSemaphores		= nullptr;

			return LAVA_RESULT_CAST(vkQueueSubmit(m_hQueue, 1, &m_SubmitInfo, hFence));
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

		//!	@brief	Bind a vertex buffer to a command buffer.
		void CmdBindVertexBuffer(VkBuffer hBuffer, VkDeviceSize offset = 0)
		{
			vkCmdBindVertexBuffers(m_hCommandBuffer, 0, 1, &hBuffer, &offset);
		}

		//!	@brief	Set the dynamic scissor rectangles on a command buffer.
		void CmdSetScissor(vk::ArrayProxy<VkRect2D> pScissors, uint32_t firstScissor = 0)
		{
			vkCmdSetScissor(m_hCommandBuffer, firstScissor, pScissors.size(), pScissors.data());
		}

		//!	@brief	Set the viewport on a command buffer.
		void CmdSetViewport(vk::ArrayProxy<VkViewport> pViewports, uint32_t firstViewport = 0)
		{
			vkCmdSetViewport(m_hCommandBuffer, firstViewport, pViewports.size(), pViewports.data());
		}

		//!	@brief	Issue an indirect draw into a command buffer.
		void CmdDrawIndirect(VkBuffer hBuffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
		{
			vkCmdDrawIndirect(m_hCommandBuffer, hBuffer, offset, drawCount, stride);
		}

		//!	@brief	Bind an index buffer to a command buffer.
		void CmdBindIndexBuffer(VkBuffer hBuffer, vk::IndexType eIndexType, VkDeviceSize offset = 0)
		{
			vkCmdBindIndexBuffer(m_hCommandBuffer, hBuffer, offset, static_cast<VkIndexType>(eIndexType));
		}

		//!	@brief	Set the depth bias dynamic state.
		void CmdSetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
		{
			vkCmdSetDepthBias(m_hCommandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
		}

		//!	@brief	Bind a graphics pipeline object to a command buffer.
		void CmdBindPipeline(const GraphicsPipeline * pGraphicsPipeline)
		{
			vkCmdBindPipeline(m_hCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pGraphicsPipeline->Handle());
		}

		//!	@brief	Draw primitives.
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex = 0, uint32_t firstInstance = 0)
		{
			vkCmdDraw(m_hCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
		}

		//!	@brief	 Update the values of push constants.
		void CmdPushConstants(VkPipelineLayout hPipelineLayout, vk::ShaderStageFlags eStages, uint32_t offset, uint32_t size, const void * pValues)
		{
			vkCmdPushConstants(m_hCommandBuffer, hPipelineLayout, (VkFlags)eStages, offset, size, pValues);
		}

		//!	@brief	 Issue an indexed draw into a command buffer.
		void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex = 0, int32_t vertexOffset = 0, uint32_t firstInstance = 0)
		{
			vkCmdDrawIndexed(m_hCommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
		}

		//!	@brief	Copy data from a buffer into an image.
		void CmdCopyBufferToImage(VkBuffer hSrcBuffer, VkImage hDstImage, vk::ImageLayout eDstImageLayout, vk::ArrayProxy<VkBufferImageCopy> pRegions)
		{
			vkCmdCopyBufferToImage(m_hCommandBuffer, hSrcBuffer, hDstImage, static_cast<VkImageLayout>(eDstImageLayout), pRegions.size(), pRegions.data());
		}

		//!	@brief	Begin a new render pass.
		void CmdBeginRenderPass(Framebuffer framebuffer, VkRect2D renderArea, vk::ArrayProxy<VkClearValue> pClearValues = {}, vk::SubpassContents eContents = vk::SubpassContents::eInline);

		//!	@brief	Clear regions of a color image.
		void CmdClearColorImage(VkImage hImage, vk::ImageLayout eImageLayout, const VkClearColorValue & color, vk::ArrayProxy<vk::ImageSubresourceRange> pRanges)
		{
			vkCmdClearColorImage(m_hCommandBuffer, hImage, static_cast<VkImageLayout>(eImageLayout), &color, pRanges.size(), reinterpret_cast<const VkImageSubresourceRange*>(pRanges.data()));
		}

		//!	@brief	Insert a image memory dependency.
		void CmdImageMemoryBarrier(vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::DependencyFlags dependencyFlags, vk::ArrayProxy<vk::ImageMemoryBarrier> pImageMemoryBarriers)
		{
			vkCmdPipelineBarrier(m_hCommandBuffer, (VkFlags)srcStageMask, (VkFlags)dstStageMask, (VkFlags)dependencyFlags, 0, nullptr, 0, nullptr, pImageMemoryBarriers.size(), reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers.data()));
		}

		//!	@brief	Resolve regions of an image.
		void CmdResolveImage(VkImage hSrcImage, vk::ImageLayout eSrcImageLayout, VkImage hDstImage, vk::ImageLayout eDstImageLayout, vk::ArrayProxy<vk::ImageResolve> pRegions)
		{
			vkCmdResolveImage(m_hCommandBuffer, hSrcImage, static_cast<VkImageLayout>(eSrcImageLayout), hDstImage, static_cast<VkImageLayout>(eDstImageLayout), pRegions.size(), reinterpret_cast<const VkImageResolve*>(pRegions.data()));
		}

		//!	@brief	Copy regions of an image, potentially performing format conversion.
		void CmdBlitImage(VkImage hSrcImage, vk::ImageLayout eSrcImageLayout, VkImage hDstImage, vk::ImageLayout eDstImageLayout, vk::ArrayProxy<vk::ImageBlit> pRegions, vk::Filter eFilter)
		{
			vkCmdBlitImage(m_hCommandBuffer, hSrcImage, static_cast<VkImageLayout>(eSrcImageLayout), hDstImage, static_cast<VkImageLayout>(eDstImageLayout), pRegions.size(), reinterpret_cast<const VkImageBlit*>(pRegions.data()), static_cast<VkFilter>(eFilter));
		}

		//!	@brief	Binds descriptor sets to a command buffer.
		void CmdBindDescriptorSets(vk::PipelineBindPoint ePipelineBindPoint, VkPipelineLayout hPipelineLayout, vk::ArrayProxy<VkDescriptorSet> pDescriptorSets)
		{
			vkCmdBindDescriptorSets(m_hCommandBuffer, static_cast<VkPipelineBindPoint>(ePipelineBindPoint), hPipelineLayout, 0, pDescriptorSets.size(), pDescriptorSets.data(), 0, nullptr);
		}

	private:

		const VkQueue					m_hQueue;

		const VkCommandBuffer			m_hCommandBuffer;

		VkSubmitInfo					m_SubmitInfo;
	};
}