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


std::shared_ptr<RenderPass> RenderPass::Create(const std::vector<VkAttachmentDescription> & attachmentDescriptions,
											   const std::vector<VkSubpassDescription> & subpassDescriptions,
											   const std::vector<VkSubpassDependency> & subpassDependencies)
{
	VkRenderPassCreateInfo			CreateInfo = {};
	CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext				= nullptr;
	CreateInfo.flags				= 0;
	CreateInfo.attachmentCount		= static_cast<uint32_t>(attachmentDescriptions.size());
	CreateInfo.pAttachments			= attachmentDescriptions.data();
	CreateInfo.subpassCount			= static_cast<uint32_t>(subpassDescriptions.size());
	CreateInfo.pSubpasses			= subpassDescriptions.data();
	CreateInfo.dependencyCount		= static_cast<uint32_t>(subpassDependencies.size());
	CreateInfo.pDependencies		= subpassDependencies.data();

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