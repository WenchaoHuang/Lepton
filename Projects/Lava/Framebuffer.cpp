/*************************************************************************
*************************    Lava_Framebuffer    *************************
*************************************************************************/

#include "Framebuffer.h"

using namespace Lava;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::UniqueHandle::UniqueHandle(VkDevice hDevice, VkRenderPass hRenderPass) : m_hDevice(hDevice), m_hRenderPass(hRenderPass)
{

}


Result RenderPass::Create(VkDevice hDevice, ArrayProxy<AttachmentDescription> attachmentDescriptions,
						  ArrayProxy<SubpassDescription> subpassDescriptions, ArrayProxy<SubpassDependency> subpassDependencies)
{
	if (hDevice == VK_NULL_HANDLE)		Result::eErrorInvalidDeviceHandle;

	VkRenderPassCreateInfo				CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.attachmentCount			= attachmentDescriptions.size();
	CreateInfo.pAttachments				= reinterpret_cast<const VkAttachmentDescription*>(attachmentDescriptions.data());
	CreateInfo.subpassCount				= subpassDescriptions.size();
	CreateInfo.pSubpasses				= reinterpret_cast<const VkSubpassDescription*>(subpassDescriptions.data());
	CreateInfo.dependencyCount			= subpassDependencies.size();
	CreateInfo.pDependencies			= reinterpret_cast<const VkSubpassDependency*>(subpassDependencies.data());

	VkRenderPass hRenderPass = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateRenderPass(hDevice, &CreateInfo, nullptr, &hRenderPass));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(hDevice, hRenderPass);
	}

	return eResult;
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
Framebuffer::UniqueHandle::UniqueHandle(RenderPass renderPass, VkFramebuffer hFramebuffer, VkExtent2D extent)
	: m_RenderPass(renderPass), m_hFramebuffer(hFramebuffer), m_Extent(extent)
{

}


Result Framebuffer::Create(RenderPass renderPass, ArrayProxy<VkImageView> attachments, VkExtent2D extent)
{
	if (!renderPass.IsValid())			Result::eErrorInvalidRenderPassHandle;

	VkFramebufferCreateInfo				CreateInfo = {};
	CreateInfo.sType					= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	CreateInfo.pNext					= nullptr;
	CreateInfo.flags					= 0;
	CreateInfo.renderPass				= renderPass;
	CreateInfo.attachmentCount			= attachments.size();
	CreateInfo.pAttachments				= attachments.data();
	CreateInfo.width					= extent.width;
	CreateInfo.height					= extent.height;
	CreateInfo.layers					= 1;

	VkFramebuffer hFramebuffer = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateFramebuffer(renderPass.GetDeviceHandle(), &CreateInfo, nullptr, &hFramebuffer));

	if (eResult == Result::eSuccess)
	{
		m_spUniqueHandle = std::make_shared<UniqueHandle>(renderPass, hFramebuffer, extent);
	}

	return eResult;
}


Framebuffer::UniqueHandle::~UniqueHandle()
{
	if (m_hFramebuffer != VK_NULL_HANDLE)
	{
		vkDestroyFramebuffer(m_RenderPass.GetDeviceHandle(), m_hFramebuffer, nullptr);
	}
}