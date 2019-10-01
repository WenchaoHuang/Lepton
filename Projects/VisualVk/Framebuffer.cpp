/*************************************************************************
***********************    VisualVk_Framebuffer    ***********************
*************************************************************************/
#include "Framebuffer.h"

using namespace Vk;

/*************************************************************************
****************************    RenderPass    ****************************
*************************************************************************/
RenderPass::RenderPass(VkDevice hDevice,
					   ArrayProxy<const AttachmentDescription> attachmentDescriptions,
					   ArrayProxy<const SubpassDescription> subpassDescriptions,
					   ArrayProxy<const SubpassDependency> subpassDependencies)
	: m_hDevice(VK_NULL_HANDLE), m_hRenderPass(VK_NULL_HANDLE)
{
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

		if (vkCreateRenderPass(hDevice, &CreateInfo, nullptr, &hRenderPass) == VK_SUCCESS)
		{
			m_hRenderPass = hRenderPass;

			m_hDevice = hDevice;
		}
	}
}


RenderPass::~RenderPass()
{
	if (m_hRenderPass != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(m_hDevice, m_hRenderPass, nullptr);

		m_hRenderPass = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;
	}
}


/*************************************************************************
***************************    Framebuffer    ****************************
*************************************************************************/
Framebuffer::Framebuffer() : m_hDevice(VK_NULL_HANDLE), m_hFramebuffer(VK_NULL_HANDLE), m_spRenderPass(nullptr), m_Extent({ 0, 0 })
{
	
}


Framebuffer::Framebuffer(std::shared_ptr<RenderPass> spRenderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent) : Framebuffer()
{
	this->Create(spRenderPass, attachments, extent);
}


Result Framebuffer::Create(std::shared_ptr<RenderPass> spRenderPass, ArrayProxy<const VkImageView> attachments, VkExtent2D extent)
{
	VkResult eResult = VK_ERROR_INVALID_EXTERNAL_HANDLE;

	if ((spRenderPass != nullptr) && spRenderPass->IsValid())
	{
		VkFramebufferCreateInfo			CreateInfo = {};
		CreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		CreateInfo.pNext				= nullptr;
		CreateInfo.flags				= 0;
		CreateInfo.renderPass			= spRenderPass->GetHandle();
		CreateInfo.attachmentCount		= attachments.size();
		CreateInfo.pAttachments			= attachments.data();
		CreateInfo.width				= extent.width;
		CreateInfo.height				= extent.height;
		CreateInfo.layers				= 1;

		VkFramebuffer hFramebuffer = VK_NULL_HANDLE;

		eResult = vkCreateFramebuffer(spRenderPass->GetDeviceHandle(), &CreateInfo, nullptr, &hFramebuffer);

		if (eResult == VK_SUCCESS)
		{
			this->Destroy();

			m_hDevice = spRenderPass->GetDeviceHandle();

			m_hFramebuffer = hFramebuffer;

			m_spRenderPass = spRenderPass;

			m_Extent = extent;
		}
	}

	return VK_RESULT_CAST(eResult);
}


void Framebuffer::Destroy()
{
	if (m_hFramebuffer != VK_NULL_HANDLE)
	{
		vkDestroyFramebuffer(m_hDevice, m_hFramebuffer, nullptr);

		m_hFramebuffer = VK_NULL_HANDLE;

		m_hDevice = VK_NULL_HANDLE;

		m_spRenderPass = nullptr;

		m_Extent = { 0, 0 };
	}
}


Framebuffer::~Framebuffer()
{
	this->Destroy();
}