/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
VkResult RenderPass::Create(const std::vector<AttachmentDescription> & attachmentDescriptions,
							const std::vector<SubpassDescription> & subpassDescriptions,
							const std::vector<SubpassDependency> & subpassDependencies)
{
	VkRenderPassCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(attachmentDescriptions.size());
	CreateInfo.pAttachments			= reinterpret_cast<const VkAttachmentDescription*>(attachmentDescriptions.data());
	CreateInfo.subpassCount			= static_cast<uint32_t>(subpassDescriptions.size());
	CreateInfo.pSubpasses			= reinterpret_cast<const VkSubpassDescription*>(subpassDescriptions.data());
	CreateInfo.dependencyCount		= static_cast<uint32_t>(subpassDependencies.size());
	CreateInfo.pDependencies		= reinterpret_cast<const VkSubpassDependency*>(subpassDependencies.data());

	VkRenderPass hRenderPass = VK_NULL_HANDLE;

	VkResult eResult = Context::GetDevice()->CreateRenderPass(&CreateInfo, &hRenderPass);

	if (eResult == VK_SUCCESS)
	{
		RenderPassH::Replace(Context::GetDeviceHandle(), hRenderPass);
	}

	return eResult;
}


/*************************************************************************
***************************    Framebuffer    ****************************
*************************************************************************/
Framebuffer::Framebuffer() : m_Extent2D({ 0, 0 })
{

}


VkResult Framebuffer::Create(RenderPassH hRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D)
{
	if (!hRenderPass.IsValid())		return VK_ERROR_INVALID_EXTERNAL_HANDLE;

	VkFramebufferCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.renderPass			= hRenderPass;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(Attachments.size());
	CreateInfo.pAttachments			= Attachments.data();
	CreateInfo.width				= Extent2D.width;
	CreateInfo.height				= Extent2D.height;
	CreateInfo.layers				= 1;

	VkFramebuffer hFramebuffer = VK_NULL_HANDLE;

	VkResult eResult = Context::GetDevice()->CreateFramebuffer(&CreateInfo, &hFramebuffer);

	if (eResult == VK_SUCCESS)
	{
		FramebufferH::Replace(Context::GetDeviceHandle(), hFramebuffer);

		m_hRenderPass = hRenderPass;

		m_Extent2D = Extent2D;
	}

	return eResult;
}


void Framebuffer::Invalidate()
{
	FramebufferH::Invalidate();

	m_hRenderPass.Invalidate();

	m_Extent2D = { 0, 0 };
}


Framebuffer::~Framebuffer()
{
	
}