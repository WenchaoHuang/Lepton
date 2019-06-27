/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Handle.h"
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Base class for Vulkan render pass object.
	 */
	class RenderPass : private Resource, public RenderPassH
	{

	public:

		//!	@brief	Create render pass object.
		RenderPass();

		//!	@brief	Destroy render pass object.
		~RenderPass();

	protected:

		//!	@brief	Create a render pass object.
		VkResult Create(const std::vector<VkAttachmentDescription> & attachmentDescriptions,
						const std::vector<VkSubpassDescription> & subpassDescriptions,
						const std::vector<VkSubpassDependency> & subpassDependencies);

	private:

		std::vector<VkSubpassDependency>			m_SubpassDependencies;
		std::vector<VkSubpassDescription>			m_SubpassDescriptions;
		std::vector<VkAttachmentDescription>		m_AttachmentDescriptions;
	};

	/*********************************************************************
	*************************    Framebuffer    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan frame buffer object.
	 */
	class Framebuffer : private Resource
	{

	public:

		//!	@brief	Create framebuffer object.
		Framebuffer();

		//!	@brief	Destroy framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Convert to VkFramebuffer handle.
		operator VkFramebuffer() const { return m_hFramebuffer; }

		//!	@brief	Create a new frame buffer object.
		VkResult Create(RenderPassH hRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);

		//!	@brief	Return render pass handle.
		RenderPassH GetRenderPass() const { return m_hRenderPass; }

		//!	@brief	Return extent of framebuffer.
		VkExtent2D GetExtent() const { return m_Extent2D; }

		//!	@brief	Invalidate.
		void Invalidate();

	private:

		VkExtent2D						m_Extent2D;

		RenderPassH						m_hRenderPass;

		VkFramebuffer					m_hFramebuffer;

		std::vector<VkImageView>		m_Attachments;
	};
}