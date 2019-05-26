/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include <memory>
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	**************************    RenderPass    **************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan render pass object.
	 */
	class RenderPass : private Resource
	{

	public:

		//!	@brief	Create render pass object.
		RenderPass(VkRenderPass hRenderPass = VK_NULL_HANDLE);

		//!	@brief	Destroy render pass object.
		~RenderPass() noexcept;

	public:

		//!	@brief	Return VkRenderPass handle.
		VkRenderPass GetHandle() const { return m_hRenderPass; }

		//!	@brief	If render pass handle is valid.
		VkBool32 IsValid() const { return m_hRenderPass != VK_NULL_HANDLE; }

		//!	@brief	Create a common render pass object for swapchain.
		static std::shared_ptr<RenderPass> CreateForSwapchain(VkFormat eColorFormat);

		//!	@brief	Create a common render pass object for swapchain.
		static std::shared_ptr<RenderPass> CreateForSwapchain(VkFormat eColorFormat,
															  VkFormat eDepthStencilFormat);
		//!	@brief	Create a render pass object.
		static std::shared_ptr<RenderPass> Create(const std::vector<VkAttachmentDescription> & AttachmentDescriptions,
												  const std::vector<VkSubpassDescription> & SubpassDescriptions = std::vector<VkSubpassDescription>(),
												  const std::vector<VkSubpassDependency> & SubpassDependencies = std::vector<VkSubpassDependency>());
	private:

		const VkRenderPass						m_hRenderPass;

		std::vector<VkSubpassDependency>		m_SubpassDependencies;

		std::vector<VkSubpassDescription>		m_SubpassDescriptions;

		std::vector<VkAttachmentDescription>	m_AttachmentDescriptions;
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

		//!	@brief	If framebuffer handle is valid.
		VkBool32 IsValid() const { return m_hFramebuffer != VK_NULL_HANDLE; }

		//!	@brief	Return shared pointer to render pass object.
		std::shared_ptr<RenderPass> GetRenderPass() const { return m_spRenderPass; }

		//!	@brief	Create a new frame buffer object.
		VkResult Create(std::shared_ptr<RenderPass> spRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);

		//!	@brief	Update frame buffer.
		VkResult Resize(const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D);

		//!	@brief	Return extent of framebuffer.
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