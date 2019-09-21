/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "CommandBuffer.h"
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::RenderPass() : m_hDevice(VK_NULL_HANDLE), m_hRenderPass(VK_NULL_HANDLE)
{

}


Result RenderPass::Create(VkDevice hDevice, 
						  ArrayProxy<const AttachmentDescription> attachmentDescriptions,
						  ArrayProxy<const SubpassDescription> subpassDescriptions,
						  ArrayProxy<const SubpassDependency> subpassDependencies)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (hDevice != VK_NULL_HANDLE)
	{
		VkRenderPassCreateInfo			CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.attachmentCount		= attachmentDescriptions.size();
		CreateInfo.pAttachments			= reinterpret_cast<const VkAttachmentDescription*>(attachmentDescriptions.data());
		CreateInfo.subpassCount			= subpassDescriptions.size();
		CreateInfo.pSubpasses			= reinterpret_cast<const VkSubpassDescription*>(subpassDescriptions.data());
		CreateInfo.dependencyCount		= subpassDependencies.size();
		CreateInfo.pDependencies		= reinterpret_cast<const VkSubpassDependency*>(subpassDependencies.data());

		VkRenderPass hRenderPass = VK_NULL_HANDLE;

		eResult = vkCreateRenderPass(hDevice, &CreateInfo, nullptr, &hRenderPass);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hDevice = hDevice;

			m_hRenderPass = hRenderPass;
		}
	}

	return static_cast<Result>(eResult);
}


void RenderPass::Destroy()
{
	if (m_hRenderPass != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(m_hDevice, m_hRenderPass, nullptr);

		m_hRenderPass = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}


RenderPass::~RenderPass()
{
	this->Destroy();
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


void Framebuffer::BeginRenderPass(CommandBuffer * pCommandBuffer, VkRect2D RenderArea, uint32_t clearValueCount, const VkClearValue * pClearValues)
{
	VkRenderPassBeginInfo			BeginInfo = {};
	BeginInfo.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	BeginInfo.pNext					= nullptr;
	BeginInfo.renderPass			= m_hRenderPass;
	BeginInfo.framebuffer			= (*this);
	BeginInfo.renderArea			= RenderArea;
	BeginInfo.clearValueCount		= clearValueCount;
	BeginInfo.pClearValues			= pClearValues;

	pCommandBuffer->CmdBeginRenderPass(&BeginInfo);
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