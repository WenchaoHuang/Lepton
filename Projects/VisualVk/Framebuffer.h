/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#pragma once

#include "Handle.h"
#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	***********************    AttachmentLoadOp    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify how contents of an attachment are treated at the beginning of a subpass.
	 */
	enum class AttachmentLoadOp
	{
		eLoad		= VK_ATTACHMENT_LOAD_OP_LOAD,
		eClear		= VK_ATTACHMENT_LOAD_OP_CLEAR,
		eDontCare	= VK_ATTACHMENT_LOAD_OP_DONT_CARE,
	};

	/*********************************************************************
	**********************    AttachmentStoreOp    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify how contents of an attachment are treated at the end of a subpass.
	 */
	enum class AttachmentStoreOp
	{
		eStore		= VK_ATTACHMENT_STORE_OP_STORE,
		eDontCare	= VK_ATTACHMENT_STORE_OP_DONT_CARE,
	};
	
	/*********************************************************************
	**********************    PipelineBindPoint    ***********************
	*********************************************************************/

	/**
	 *	@brief	Specify the bind point of a pipeline object to a command buffer.
	 */
	enum class PipelineBindPoint
	{
		eCompute		= VK_PIPELINE_BIND_POINT_COMPUTE,
		eGraphics		= VK_PIPELINE_BIND_POINT_GRAPHICS,
		eRayTracingNV	= VK_PIPELINE_BIND_POINT_RAY_TRACING_NV
	};

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

	public:

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

		//!	@brief	Invalidate framebuffer.
		void Release();

	private:

		VkExtent2D						m_Extent2D;

		RenderPassH						m_hRenderPass;

		VkFramebuffer					m_hFramebuffer;

		std::vector<VkImageView>		m_Attachments;
	};
}