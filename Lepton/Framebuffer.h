/*************************************************************************
************************    Lepton_Framebuffer    ************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan render pass object.
	 */
	class RenderPass
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Create a new render pass object.
		Result Create(VkDevice hDevice, vk::ArrayProxy<vk::AttachmentDescription> attachmentDescriptions,
					  vk::ArrayProxy<vk::SubpassDescription> subpassDescriptions, vk::ArrayProxy<vk::SubpassDependency> subpassDependencies);

		//!	@brief	Return VkDevice handle.
		VkDevice GetDeviceHandle() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hDevice : VK_NULL_HANDLE; }

		//!	@brief	Convert to VkRenderPass.
		operator VkRenderPass() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hRenderPass : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of render pass.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(VkDevice, VkRenderPass);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkDevice					m_hDevice;
			const VkRenderPass				m_hRenderPass;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};

	/*********************************************************************
	*************************    Framebuffer    **************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan frame buffer object.
	 */
	class Framebuffer
	{

	public:

		//!	@brief	Invalidate this resource handle.
		void Destroy() { m_spUniqueHandle.reset(); }

		//!	@brief	Whether this resource handle is valid.
		bool IsValid() const { return m_spUniqueHandle != nullptr; }

		//!	@brief	Return extent of the framebuffer (must be valid).
		VkExtent2D GetExtent() const { return m_spUniqueHandle->m_Extent; }

		//!	@brief	Return render pass object (must be valid).
		RenderPass GetRenderPass() const { return m_spUniqueHandle->m_RenderPass; }

		//!	@brief	Create a new framebuffer object.
		Result Create(RenderPass renderPass, vk::ArrayProxy<VkImageView> attachments, VkExtent2D extent);

		//!	@brief	Convert to VkFramebuffer.
		operator VkFramebuffer() const { return (m_spUniqueHandle != nullptr) ? m_spUniqueHandle->m_hFramebuffer : VK_NULL_HANDLE; }

	private:

		/**
		 *	@brief	Unique handle of framebuffer.
		 */
		struct UniqueHandle
		{
			LAVA_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (handles must be initialized).
			UniqueHandle(RenderPass, VkFramebuffer, VkExtent2D);

			//!	@brief	Where resource will be released.
			~UniqueHandle() noexcept;

		public:

			const VkExtent2D				m_Extent;
			const RenderPass				m_RenderPass;
			const VkFramebuffer				m_hFramebuffer;
		};

		std::shared_ptr<UniqueHandle>		m_spUniqueHandle;
	};
}