/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::UniqueHandle::UniqueHandle(VkDevice hDevice, VkRenderPass hRenderPass) : m_hDevice(hDevice), m_hRenderPass(hRenderPass)
{

}


Result RenderPass::Create(VkDevice hDevice, ArrayProxy<const AttachmentDescription> attachmentDescriptions,
						  ArrayProxy<const SubpassDescription> subpassDescriptions, ArrayProxy<const SubpassDependency> subpassDependencies)
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
			m_spHandle = std::make_shared<UniqueHandle>(hDevice, hRenderPass);
		}
	}

	return VK_RESULT_CAST(eResult);
}


RenderPass::UniqueHandle::~UniqueHandle()
{
	if (m_hRenderPass != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(m_hDevice, m_hRenderPass, nullptr);
	}
}


/*************************************************************************
***************************    Framebuffer    ****************************
*************************************************************************/
Framebuffer::Framebuffer() : m_hFramebuffer(VK_NULL_HANDLE), m_Extent({ 0, 0 })
{
	
}


Framebuffer::Framebuffer(RenderPass renderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent) : Framebuffer()
{
	this->Create(renderPass, attachments, extent);
}


Result Framebuffer::Create(RenderPass renderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if (renderPass.IsValid())
	{
		VkFramebufferCreateInfo			CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.renderPass			= renderPass;
		CreateInfo.attachmentCount		= attachments.size();
		CreateInfo.pAttachments			= attachments.data();
		CreateInfo.width				= extent.width;
		CreateInfo.height				= extent.height;
		CreateInfo.layers				= 1;

		VkFramebuffer hFramebuffer = VK_NULL_HANDLE;

		eResult = vkCreateFramebuffer(renderPass.GetDeviceHandle(), &CreateInfo, nullptr, &hFramebuffer);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hFramebuffer = hFramebuffer;

			m_RenderPass = renderPass;

			m_Extent = extent;
		}
	}

	return VK_RESULT_CAST(eResult);
}


void Framebuffer::Destroy()
{
	if (m_hFramebuffer != VK_NULL_HANDLE)
	{
		vkDestroyFramebuffer(m_RenderPass.GetDeviceHandle(), m_hFramebuffer, nullptr);

		m_hFramebuffer = VK_NULL_HANDLE;

		m_RenderPass.Destroy();

		m_Extent = { 0, 0 };
	}
}


Framebuffer::~Framebuffer()
{
	this->Destroy();
}