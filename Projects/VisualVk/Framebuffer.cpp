/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::RenderPass()
{

}


VkResult RenderPass::Create(const std::vector<AttachmentDescription> & attachmentDescriptions,
							const std::vector<VkSubpassDescription> & subpassDescriptions,
							const std::vector<SubpassDependency> & subpassDependencies)
{
	std::vector<VkAttachmentDescription> attachmentDesc(attachmentDescriptions.size());

	for (size_t i = 0; i < attachmentDesc.size(); i++)
	{
		attachmentDesc[i].flags					= 0;
		attachmentDesc[i].format				= static_cast<VkFormat>(attachmentDescriptions[i].format);
		attachmentDesc[i].samples				= static_cast<VkSampleCountFlagBits>(attachmentDescriptions[i].samples);
		attachmentDesc[i].loadOp				= static_cast<VkAttachmentLoadOp>(attachmentDescriptions[i].loadOp);
		attachmentDesc[i].storeOp				= static_cast<VkAttachmentStoreOp>(attachmentDescriptions[i].storeOp);
		attachmentDesc[i].stencilLoadOp			= static_cast<VkAttachmentLoadOp>(attachmentDescriptions[i].stencilLoadOp);
		attachmentDesc[i].stencilStoreOp		= static_cast<VkAttachmentStoreOp>(attachmentDescriptions[i].stencilStoreOp);
		attachmentDesc[i].initialLayout			= static_cast<VkImageLayout>(attachmentDescriptions[i].initialLayout);
		attachmentDesc[i].finalLayout			= static_cast<VkImageLayout>(attachmentDescriptions[i].finalLayout);
	}

	VkRenderPassCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(attachmentDescriptions.size());
	CreateInfo.pAttachments			= attachmentDesc.data();
	CreateInfo.subpassCount			= static_cast<uint32_t>(subpassDescriptions.size());
	CreateInfo.pSubpasses			= subpassDescriptions.data();
	CreateInfo.dependencyCount		= static_cast<uint32_t>(subpassDependencies.size());
	CreateInfo.pDependencies		= reinterpret_cast<const VkSubpassDependency*>(subpassDependencies.data());

	VkRenderPass hRenderPass = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->CreateRenderPass(&CreateInfo, &hRenderPass);

	if (eResult == VK_SUCCESS)
	{
		*static_cast<RenderPassH*>(this) = RenderPassH(hRenderPass, *m_pDevice);

		m_AttachmentDescriptions = attachmentDescriptions;

		m_SubpassDependencies = subpassDependencies;

		m_SubpassDescriptions = subpassDescriptions;
	}

	return eResult;
}


RenderPass::~RenderPass()
{

}


/*************************************************************************
***************************    Framebuffer    ****************************
*************************************************************************/
Framebuffer::Framebuffer() : m_hFramebuffer(VK_NULL_HANDLE), m_Extent2D({ 0, 0 })
{

}


VkResult Framebuffer::Create(RenderPassH hRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D)
{
	if (hRenderPass.IsValid() == false)
	{
		return VK_ERROR_INVALID_EXTERNAL_HANDLE;
	}

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

	VkResult eResult = m_pDevice->CreateFramebuffer(&CreateInfo, &hFramebuffer);

	if (eResult == VK_SUCCESS)
	{
		this->Release();

		m_hFramebuffer = hFramebuffer;

		m_Attachments = Attachments;

		m_hRenderPass = hRenderPass;

		m_Extent2D = Extent2D;
	}

	return eResult;
}


void Framebuffer::Release()
{
	if (m_hFramebuffer != VK_NULL_HANDLE)
	{
		m_pDevice->DestroyFramebuffer(m_hFramebuffer);

		m_hFramebuffer = VK_NULL_HANDLE;

		m_hRenderPass.Invalidate();

		m_Attachments.clear();

		m_Extent2D = { 0, 0 };
	}
}


Framebuffer::~Framebuffer()
{
	this->Release();
}