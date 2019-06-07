/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::RenderPass(VkRenderPass hRenderPass) : m_hRenderPass(hRenderPass)
{

}


std::shared_ptr<RenderPass> RenderPass::CreateForSwapchain(VkFormat eColorFormat)
{
	std::vector<VkAttachmentDescription>			AttachmentDescriptions(1);
	std::vector<VkSubpassDescription>				SubpassDescriptions(1);

	AttachmentDescriptions[0].format				= eColorFormat;
	AttachmentDescriptions[0].samples				= VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescriptions[0].loadOp				= VK_ATTACHMENT_LOAD_OP_CLEAR;
	AttachmentDescriptions[0].storeOp				= VK_ATTACHMENT_STORE_OP_STORE;
	AttachmentDescriptions[0].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescriptions[0].stencilStoreOp		= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescriptions[0].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescriptions[0].finalLayout			= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	AttachmentDescriptions[0].flags					= 0;

	VkAttachmentReference ColorReference			= { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

	SubpassDescriptions[0].pipelineBindPoint		= VK_PIPELINE_BIND_POINT_GRAPHICS;
	SubpassDescriptions[0].flags					= 0;
	SubpassDescriptions[0].inputAttachmentCount		= 0;
	SubpassDescriptions[0].pInputAttachments		= nullptr;
	SubpassDescriptions[0].colorAttachmentCount		= 1;
	SubpassDescriptions[0].pColorAttachments		= &ColorReference;
	SubpassDescriptions[0].pResolveAttachments		= nullptr;
	SubpassDescriptions[0].pDepthStencilAttachment	= nullptr;
	SubpassDescriptions[0].preserveAttachmentCount	= 0;
	SubpassDescriptions[0].pPreserveAttachments		= nullptr;

	return RenderPass::Create(AttachmentDescriptions, SubpassDescriptions);
}


std::shared_ptr<RenderPass> RenderPass::CreateForSwapchain(VkFormat eColorFormat,
														   VkFormat eDepthStencilFormat)
{
	std::vector<VkAttachmentDescription>			AttachmentDescriptions(2);
	std::vector<VkSubpassDescription>				SubpassDescriptions(1);

	AttachmentDescriptions[0].format				= eColorFormat;
	AttachmentDescriptions[0].samples				= VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescriptions[0].loadOp				= VK_ATTACHMENT_LOAD_OP_CLEAR;
	AttachmentDescriptions[0].storeOp				= VK_ATTACHMENT_STORE_OP_STORE;
	AttachmentDescriptions[0].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescriptions[0].stencilStoreOp		= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescriptions[0].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescriptions[0].finalLayout			= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	AttachmentDescriptions[0].flags					= 0;

	AttachmentDescriptions[1].format				= eDepthStencilFormat;
	AttachmentDescriptions[1].samples				= VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescriptions[1].loadOp				= VK_ATTACHMENT_LOAD_OP_CLEAR;
	AttachmentDescriptions[1].storeOp				= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescriptions[1].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescriptions[1].stencilStoreOp		= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescriptions[1].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescriptions[1].finalLayout			= VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	AttachmentDescriptions[1].flags					= 0;

	VkAttachmentReference ColorReference			= { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
	VkAttachmentReference DepthReference			= { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

	SubpassDescriptions[0].pipelineBindPoint		= VK_PIPELINE_BIND_POINT_GRAPHICS;
	SubpassDescriptions[0].flags					= 0;
	SubpassDescriptions[0].inputAttachmentCount		= 0;
	SubpassDescriptions[0].pInputAttachments		= nullptr;
	SubpassDescriptions[0].colorAttachmentCount		= 1;
	SubpassDescriptions[0].pColorAttachments		= &ColorReference;
	SubpassDescriptions[0].pResolveAttachments		= nullptr;
	SubpassDescriptions[0].pDepthStencilAttachment	= &DepthReference;
	SubpassDescriptions[0].preserveAttachmentCount	= 0;
	SubpassDescriptions[0].pPreserveAttachments		= nullptr;

	return RenderPass::Create(AttachmentDescriptions, SubpassDescriptions);
}


std::shared_ptr<RenderPass> RenderPass::Create(const std::vector<VkAttachmentDescription> & AttachmentDescriptions,
											   const std::vector<VkSubpassDescription> & SubpassDescriptions,
											   const std::vector<VkSubpassDependency> & SubpassDependencies)
{
	VkRenderPassCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(AttachmentDescriptions.size());
	CreateInfo.pAttachments			= AttachmentDescriptions.data();
	CreateInfo.subpassCount			= static_cast<uint32_t>(SubpassDescriptions.size());
	CreateInfo.pSubpasses			= SubpassDescriptions.data();
	CreateInfo.dependencyCount		= static_cast<uint32_t>(SubpassDependencies.size());
	CreateInfo.pDependencies		= SubpassDependencies.data();

	VkRenderPass hRenderPass = VK_NULL_HANDLE;

	sm_pDevice->CreateRenderPass(&CreateInfo, &hRenderPass);

	std::shared_ptr<RenderPass> spRenderPass = std::make_shared<RenderPass>(hRenderPass);

	spRenderPass->m_AttachmentDescriptions = AttachmentDescriptions;

	spRenderPass->m_SubpassDescriptions = SubpassDescriptions;

	spRenderPass->m_SubpassDependencies = SubpassDependencies;

	return spRenderPass;
}


RenderPass::~RenderPass() noexcept
{
	sm_pDevice->DestroyRenderPass(m_hRenderPass);
}


/*************************************************************************
***************************    Framebuffer    ****************************
*************************************************************************/
Framebuffer::Framebuffer() : m_hFramebuffer(VK_NULL_HANDLE), m_spRenderPass(nullptr)
{
	m_Extent2D = { 0, 0 };
}


VkResult Framebuffer::Create(std::shared_ptr<RenderPass> spRenderPass, const std::vector<VkImageView> & Attachments, VkExtent2D Extent2D)
{
	if ((spRenderPass == nullptr) || !spRenderPass->IsValid())
	{
		return VK_ERROR_INVALID_EXTERNAL_HANDLE;
	}

	VkFramebufferCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.renderPass			= spRenderPass->GetHandle();
	CreateInfo.attachmentCount		= static_cast<uint32_t>(Attachments.size());
	CreateInfo.pAttachments			= Attachments.data();
	CreateInfo.width				= Extent2D.width;
	CreateInfo.height				= Extent2D.height;
	CreateInfo.layers				= 1;

	VkFramebuffer hFramebuffer = VK_NULL_HANDLE;

	VkResult eResult = sm_pDevice->CreateFramebuffer(&CreateInfo, &hFramebuffer);

	if (eResult == VK_SUCCESS)
	{
		this->Release();

		m_hFramebuffer = hFramebuffer;

		m_spRenderPass = spRenderPass;

		m_Attachments = Attachments;

		m_Extent2D = Extent2D;
	}

	return eResult;
}


void Framebuffer::Release() noexcept
{
	if (m_hFramebuffer != VK_NULL_HANDLE)
	{
		sm_pDevice->DestroyFramebuffer(m_hFramebuffer);

		m_hFramebuffer = VK_NULL_HANDLE;

		m_spRenderPass = nullptr;

		m_Attachments.clear();

		m_Extent2D = { 0, 0 };
	}
}


Framebuffer::~Framebuffer()
{
	this->Release();
}