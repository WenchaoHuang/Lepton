/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	************************    RenderPassInfo    ************************
	*********************************************************************/

	/**
	 *	@brief	Information for creating RenderPass object.
	 */
	struct RenderPassInfo
	{
		std::vector<VkSubpassDependency>		subpassDependencies;
		std::vector<VkSubpassDescription>		subpassDescriptions;
		std::vector<VkAttachmentReference>		attachmentReferences;
		std::vector<VkAttachmentDescription>	attachmentDescriptions;
	};

	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan render pass object.
	 */
	class RenderPass : private Resource
	{

	public:

		//!	@brief	Creates render pass object.
		RenderPass(VkRenderPass hRenderPass = VK_NULL_HANDLE);

		//!	@brief	Destroys render pass object.
		~RenderPass() noexcept;

	public:

		//!	@brief	Returns the VkRenderPass handle.
		VkRenderPass GetHandle() const { return m_hRenderPass; }

		//!	@brief	If render pass handle is valid.
		VkBool32 IsValid() const { return m_hRenderPass != VK_NULL_HANDLE; }

		//!	@brief	Creates a common render pass object for swapchain.
		static std::shared_ptr<RenderPass> CreateForSwapchain(VkFormat eColorFormat);

		//!	@brief	Creates a common render pass object for swapchain.
		static std::shared_ptr<RenderPass> CreateForSwapchain(VkFormat eColorFormat,
															  VkFormat eDepthStencilFormat);
		//!	@brief	Creates a render pass object.
		static std::shared_ptr<RenderPass> Create(const RenderPassInfo & PassInfo);

	private:

		const VkRenderPass			m_hRenderPass;
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

		//!	@brief	Creates framebuffer object.
		Framebuffer();

		//!	@brief	Destroys framebuffer object.
		~Framebuffer();

	public:

		//!	@brief	Convert to VkFramebuffer handle.
		operator VkFramebuffer() const { return m_hFramebuffer; }

		//!	@brief	If framebuffer handle is valid.
		VkBool32 IsValid() const { return m_hFramebuffer != VK_NULL_HANDLE; }

		//!	@brief	Returns shared pointer to the render pass object.
		std::shared_ptr<RenderPass> GetRenderPass() const { return m_spRenderPass; }

		//!	@brief	Creates a new frame buffer object.
		VkResult Create(std::shared_ptr<RenderPass> spRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);

		//!	@brief	Returns extent of framebuffer.
		VkExtent2D GetExtent() const { return m_Extent2D; }

		//!	@brief	Release frame buffer.
		void Release() noexcept;

	private:

		VkExtent2D						m_Extent2D;

		VkFramebuffer					m_hFramebuffer;

		std::vector<VkImageView>		m_Attachments;

		std::shared_ptr<RenderPass>		m_spRenderPass;
	};
}