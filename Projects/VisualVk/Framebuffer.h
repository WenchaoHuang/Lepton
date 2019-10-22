/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	/*********************************************************************
	*********************    AttachmentReference    **********************
	*********************************************************************/

	/**
	 *	@brief	Structure specifying an attachment reference.
	 */
	struct AttachmentReference
	{
		uint32_t		attachment		= 0;
		ImageLayout		layout			= ImageLayout::eUndefined;
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
		PipelineBindPoint				pipelineBindPoint			= PipelineBindPoint::eGraphics;
		uint32_t                        inputAttachmentCount		= 0;
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
		const VkFlags			flags				= 0;
		Format					format				= Format::eUndefined;
		SampleCount				samples				= SampleCount::x1;
		AttachmentLoadOp		loadOp				= AttachmentLoadOp::eClear;
		AttachmentStoreOp		storeOp				= AttachmentStoreOp::eStore;
		AttachmentLoadOp		stencilLoadOp		= AttachmentLoadOp::eDontCare;
		AttachmentStoreOp		stencilStoreOp		= AttachmentStoreOp::eDontCare;
		ImageLayout				initialLayout		= ImageLayout::eUndefined;
		ImageLayout				finalLayout			= ImageLayout::eUndefined;
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
		uint32_t					srcSubpass			= 0;
		uint32_t					dstSubpass			= 0;
		Flags<PipelineStage>		srcStageMask		= 0;
		Flags<PipelineStage>		dstStageMask		= 0;
		Flags<MemoryAccess>			srcAccessMask		= 0;
		Flags<MemoryAccess>			dstAccessMask		= 0;
		Flags<MemoryDependency>		dependencyFlags		= 0;
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
		Result Create(VkDevice hDevice, ArrayProxy<const AttachmentDescription> attachmentDescriptions,
					  ArrayProxy<const SubpassDescription> subpassDescriptions, ArrayProxy<const SubpassDependency> subpassDependencies);

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
			VK_NONCOPYABLE(UniqueHandle)

		public:

			//!	@brief	Constructor (all handles must be generated outside).
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
		VK_NONCOPYABLE(Framebuffer)

	public:

		//!	@brief	Create framebuffer object.
		Framebuffer();

		//!	@brief	Create and initialize immediately.
		explicit Framebuffer(RenderPass renderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent);

		//!	@brief	Destroy framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Convert to VkFramebuffer.
		operator VkFramebuffer() const { return m_hFramebuffer; }

		//!	@brief	Return VkFramebuffer handle.
		VkFramebuffer GetHandle() const { return m_hFramebuffer; }

		//!	@brief	Whether this framebuffer handle is valid.
		bool IsValid() const { return m_hFramebuffer != VK_NULL_HANDLE; }

		//!	@brief	Create a new framebuffer object.
		Result Create(RenderPass renderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent);

		//!	@brief	Return render pass object.
		RenderPass GetRenderPass() const { return m_RenderPass; }

		//!	@brief	Return extent of the framebuffer.
		VkExtent2D GetExtent() const { return m_Extent; }

		//!	@brief	Destroy framebuffer.
		void Destroy();

	private:

		VkExtent2D			m_Extent;

		RenderPass			m_RenderPass;

		VkFramebuffer		m_hFramebuffer;
	};
}