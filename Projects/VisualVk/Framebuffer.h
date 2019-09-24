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
		VK_UNIQUE_RESOURCE(RenderPass)

	public:

		//!	@brief	Create render pass object.
		RenderPass();

		//!	@brief	Create and initialize immediately.
		explicit RenderPass(VkDevice hDevice,
							ArrayProxy<const AttachmentDescription> attachmentDescriptions,
							ArrayProxy<const SubpassDescription> subpassDescriptions,
							ArrayProxy<const SubpassDependency> subpassDependencies);

		//!	@brief	Destroy render pass object.
		~RenderPass();

	public:

		//!	@brief	Create a new render pass object.
		Result Create(VkDevice hDevice,
					  ArrayProxy<const AttachmentDescription> attachmentDescriptions,
					  ArrayProxy<const SubpassDescription> subpassDescriptions,
					  ArrayProxy<const SubpassDependency> subpassDependencies);

		//!	@brief	Destroy the render pass.
		void Destroy();
	};

	/*********************************************************************
	*************************    Framebuffer    **************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan frame buffer object.
	 */
	class Framebuffer
	{
		VK_UNIQUE_RESOURCE(Framebuffer)

	public:

		//!	@brief	Create framebuffer object.
		Framebuffer();

		//!	@brief	Create and initialize immediately.
		explicit Framebuffer(const RenderPass & renderPass, ArrayProxy<const VkImageView> attachments, Extent2D extent);

		//!	@brief	Destroy framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Create a new framebuffer object.
		Result Create(const RenderPass & renderPass, ArrayProxy<const VkImageView> attachments, Extent2D extent);

		//!	@brief	Return render pass handle.
		VkRenderPass GetRenderPassHandle() const { return m_hRenderPass; }

		//!	@brief	Return extent of the framebuffer.
		Extent2D Extent() const { return m_Extent; }

		//!	@brief	Destroy the framebuffer.
		void Destroy();

	private:

		Extent2D			m_Extent;

		VkRenderPass		m_hRenderPass;
	};
}