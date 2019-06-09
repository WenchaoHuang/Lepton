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
	RenderPassInfo	PassInfo;
	PassInfo.subpassDescriptions.resize(1);
	PassInfo.attachmentReferences.resize(1);
	PassInfo.attachmentDescriptions.resize(1);

	PassInfo.attachmentDescriptions[0].format					= eColorFormat;
	PassInfo.attachmentDescriptions[0].samples					= VK_SAMPLE_COUNT_1_BIT;
	PassInfo.attachmentDescriptions[0].loadOp					= VK_ATTACHMENT_LOAD_OP_CLEAR;
	PassInfo.attachmentDescriptions[0].storeOp					= VK_ATTACHMENT_STORE_OP_STORE;
	PassInfo.attachmentDescriptions[0].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[0].stencilStoreOp			= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[0].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	PassInfo.attachmentDescriptions[0].finalLayout				= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	PassInfo.attachmentDescriptions[0].flags					= 0;

	PassInfo.attachmentReferences[0]							= { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

	PassInfo.subpassDescriptions[0].pipelineBindPoint			= VK_PIPELINE_BIND_POINT_GRAPHICS;
	PassInfo.subpassDescriptions[0].flags						= 0;
	PassInfo.subpassDescriptions[0].inputAttachmentCount		= 0;
	PassInfo.subpassDescriptions[0].pInputAttachments			= nullptr;
	PassInfo.subpassDescriptions[0].colorAttachmentCount		= 1;
	PassInfo.subpassDescriptions[0].pColorAttachments			= &PassInfo.attachmentReferences[0];
	PassInfo.subpassDescriptions[0].pResolveAttachments			= nullptr;
	PassInfo.subpassDescriptions[0].pDepthStencilAttachment		= nullptr;
	PassInfo.subpassDescriptions[0].preserveAttachmentCount		= 0;
	PassInfo.subpassDescriptions[0].pPreserveAttachments		= nullptr;

	return RenderPass::Create(PassInfo);
}


std::shared_ptr<RenderPass> RenderPass::CreateForSwapchain(VkFormat eColorFormat,
														   VkFormat eDepthStencilFormat)
{
	RenderPassInfo	PassInfo;
	PassInfo.subpassDescriptions.resize(1);
	PassInfo.attachmentReferences.resize(2);
	PassInfo.attachmentDescriptions.resize(2);

	PassInfo.attachmentDescriptions[0].format					= eColorFormat;
	PassInfo.attachmentDescriptions[0].samples					= VK_SAMPLE_COUNT_1_BIT;
	PassInfo.attachmentDescriptions[0].loadOp					= VK_ATTACHMENT_LOAD_OP_CLEAR;
	PassInfo.attachmentDescriptions[0].storeOp					= VK_ATTACHMENT_STORE_OP_STORE;
	PassInfo.attachmentDescriptions[0].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[0].stencilStoreOp			= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[0].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	PassInfo.attachmentDescriptions[0].finalLayout				= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	PassInfo.attachmentDescriptions[0].flags					= 0;

	PassInfo.attachmentDescriptions[1].format					= eDepthStencilFormat;
	PassInfo.attachmentDescriptions[1].samples					= VK_SAMPLE_COUNT_1_BIT;
	PassInfo.attachmentDescriptions[1].loadOp					= VK_ATTACHMENT_LOAD_OP_CLEAR;
	PassInfo.attachmentDescriptions[1].storeOp					= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[1].stencilLoadOp			= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[1].stencilStoreOp			= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	PassInfo.attachmentDescriptions[1].initialLayout			= VK_IMAGE_LAYOUT_UNDEFINED;
	PassInfo.attachmentDescriptions[1].finalLayout				= VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	PassInfo.attachmentDescriptions[1].flags					= 0;

	PassInfo.attachmentReferences[0]							= { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
	PassInfo.attachmentReferences[1]							= { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

	PassInfo.subpassDescriptions[0].pipelineBindPoint			= VK_PIPELINE_BIND_POINT_GRAPHICS;
	PassInfo.subpassDescriptions[0].flags						= 0;
	PassInfo.subpassDescriptions[0].inputAttachmentCount		= 0;
	PassInfo.subpassDescriptions[0].pInputAttachments			= nullptr;
	PassInfo.subpassDescriptions[0].colorAttachmentCount		= 1;
	PassInfo.subpassDescriptions[0].pColorAttachments			= &PassInfo.attachmentReferences[0];
	PassInfo.subpassDescriptions[0].pResolveAttachments			= nullptr;
	PassInfo.subpassDescriptions[0].pDepthStencilAttachment		= &PassInfo.attachmentReferences[1];
	PassInfo.subpassDescriptions[0].preserveAttachmentCount		= 0;
	PassInfo.subpassDescriptions[0].pPreserveAttachments		= nullptr;

	return RenderPass::Create(PassInfo);
}


std::shared_ptr<RenderPass> RenderPass::Create(const RenderPassInfo & PassInfo)
{
	VkRenderPassCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(PassInfo.attachmentDescriptions.size());
	CreateInfo.pAttachments			= PassInfo.attachmentDescriptions.data();
	CreateInfo.subpassCount			= static_cast<uint32_t>(PassInfo.subpassDescriptions.size());
	CreateInfo.pSubpasses			= PassInfo.subpassDescriptions.data();
	CreateInfo.dependencyCount		= static_cast<uint32_t>(PassInfo.subpassDependencies.size());
	CreateInfo.pDependencies		= PassInfo.subpassDependencies.data();

	VkRenderPass hRenderPass = VK_NULL_HANDLE;

	sm_pLogicalDevice->CreateRenderPass(&CreateInfo, &hRenderPass);

	return std::make_shared<RenderPass>(hRenderPass);
}


RenderPass::~RenderPass() noexcept
{
	m_pDevice->DestroyRenderPass(m_hRenderPass);
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

	VkResult eResult = m_pDevice->CreateFramebuffer(&CreateInfo, &hFramebuffer);

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
		m_pDevice->DestroyFramebuffer(m_hFramebuffer);

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