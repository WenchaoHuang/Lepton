/*************************************************************************
************************    Lepton_Framebuffer    ************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Lepton
{
	/*********************************************************************
	*********************    AttachmentReference    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment reference.
	 */
	struct AttachmentReference
	{
		uint32_t			attachment		= 0;
		vk::ImageLayout		layout			= vk::ImageLayout::eUndefined;
	};

	static_assert(sizeof(AttachmentReference) == sizeof(VkAttachmentReference), "Struct and wrapper have different size!");
	
	/*********************************************************************
	**********************    SubpassDescription    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a subpass description.
	 */
	struct SubpassDescription
	{
		const VkFlags					flags						= 0;
		vk::PipelineBindPoint			pipelineBindPoint			= vk::PipelineBindPoint::eGraphics;
		uint32_t						inputAttachmentCount		= 0;
		const AttachmentReference *		pInputAttachments			= nullptr;
		uint32_t						colorAttachmentCount		= 0;
		const AttachmentReference *		pColorAttachments			= nullptr;
		const AttachmentReference *		pResolveAttachments			= nullptr;
		const AttachmentReference *		pDepthStencilAttachment		= nullptr;
		uint32_t						preserveAttachmentCount		= 0;
		const uint32_t *				pPreserveAttachments		= nullptr;
	};

	static_assert(sizeof(SubpassDescription) == sizeof(VkSubpassDescription), "Struct and wrapper have different size!");

	/*********************************************************************
	********************    AttachmentDescription    *********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment description.
	 */
	struct AttachmentDescription
	{
		const VkFlags					flags				= 0;
		vk::Format						format				= vk::Format::eUndefined;
		vk::SampleCountFlagBits			samples				= vk::SampleCountFlagBits::e1;
		vk::AttachmentLoadOp			loadOp				= vk::AttachmentLoadOp::eClear;
		vk::AttachmentStoreOp			storeOp				= vk::AttachmentStoreOp::eStore;
		vk::AttachmentLoadOp			stencilLoadOp		= vk::AttachmentLoadOp::eDontCare;
		vk::AttachmentStoreOp			stencilStoreOp		= vk::AttachmentStoreOp::eDontCare;
		vk::ImageLayout					initialLayout		= vk::ImageLayout::eUndefined;
		vk::ImageLayout					finalLayout			= vk::ImageLayout::eUndefined;
	};

	static_assert(sizeof(AttachmentDescription) == sizeof(VkAttachmentDescription), "Struct and wrapper have different size!");

	/*********************************************************************
	**********************    SubpassDependency    ***********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying a subpass dependency.
	 */
	struct SubpassDependency
	{
		uint32_t						srcSubpass			= 0;
		uint32_t						dstSubpass			= 0;
		vk::PipelineStageFlags			srcStageMask		= vk::PipelineStageFlags(0);
		vk::PipelineStageFlags			dstStageMask		= vk::PipelineStageFlags(0);
		vk::AccessFlags					srcAccessMask		= vk::AccessFlags(0);
		vk::AccessFlags					dstAccessMask		= vk::AccessFlags(0);
		vk::DependencyFlags				dependencyFlags		= vk::DependencyFlagBits(0);
	};

	static_assert(sizeof(SubpassDependency) == sizeof(VkSubpassDependency), "Struct and wrapper have different size!");

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
		Result Create(VkDevice hDevice, vk::ArrayProxy<AttachmentDescription> attachmentDescriptions,
					  vk::ArrayProxy<SubpassDescription> subpassDescriptions, vk::ArrayProxy<SubpassDependency> subpassDependencies);

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