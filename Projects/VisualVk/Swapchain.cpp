/*************************************************************************
************************    VisualVk_Swapchain    ************************
*************************************************************************/
#include "Swapchain.h"

using namespace Vk;

/*************************************************************************
****************************    Swapchain    *****************************
*************************************************************************/
Swapchain::Swapchain(VkSurfaceKHR hSurface) : m_hSwapchain(VK_NULL_HANDLE), m_pPresentQueue(nullptr), m_hSurface(hSurface), m_ImageIndex(0)
{
	m_PresentInfo.sType					= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	m_PresentInfo.pNext					= nullptr;
	m_PresentInfo.waitSemaphoreCount	= 0;
	m_PresentInfo.pWaitSemaphores		= nullptr;
	m_PresentInfo.swapchainCount		= 1;
	m_PresentInfo.pSwapchains			= &m_hSwapchain;
	m_PresentInfo.pImageIndices			= &m_ImageIndex;
	m_PresentInfo.pResults				= nullptr;

	uint32_t PresentQueueIndex = sm_pPhyDevice->GetPresentQueueFamilyIndex(hSurface);

	if (PresentQueueIndex != VK_INVALID_INDEX)
	{
		m_pPresentQueue = sm_pDevice->GetCommandQueue(PresentQueueIndex);

		m_PresentModes = sm_pPhyDevice->GetSurfacePresentModes(hSurface);

		m_SurfaceFormats = sm_pPhyDevice->GetSurfaceFormats(hSurface);
	}
}


VkResult Swapchain::UpdateSwapchain(VkBool32 bVsync)
{
	VkSurfaceCapabilitiesKHR			SurfaceCapabilities = sm_pPhyDevice->GetSurfaceCapabilities(m_hSurface);

	m_CreateInfo.sType					= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	m_CreateInfo.pNext					= nullptr;
	m_CreateInfo.flags					= 0;
	m_CreateInfo.surface				= m_hSurface;
	m_CreateInfo.minImageCount			= bVsync ? 2 : 3;
	m_CreateInfo.imageFormat			= VK_FORMAT_B8G8R8A8_UNORM;
	m_CreateInfo.imageColorSpace		= VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	m_CreateInfo.imageExtent			= SurfaceCapabilities.currentExtent;
	m_CreateInfo.imageArrayLayers		= 1;
	m_CreateInfo.imageUsage				= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	m_CreateInfo.imageSharingMode		= VK_SHARING_MODE_EXCLUSIVE;
	m_CreateInfo.queueFamilyIndexCount	= 0;
	m_CreateInfo.pQueueFamilyIndices	= nullptr;
	m_CreateInfo.preTransform			= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	m_CreateInfo.compositeAlpha			= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	m_CreateInfo.presentMode			= bVsync ? VK_PRESENT_MODE_FIFO_RELAXED_KHR : VK_PRESENT_MODE_MAILBOX_KHR;
	m_CreateInfo.clipped				= VK_TRUE;
	m_CreateInfo.oldSwapchain			= m_hSwapchain;

	VkResult eResult = sm_pDevice->CreateSwapchainKHR(&m_CreateInfo, &m_hSwapchain);

	if (eResult == VK_SUCCESS)
	{
		sm_pDevice->DestroySwapchainKHR(m_CreateInfo.oldSwapchain);

		sm_pDevice->GetSwapchainImages(m_hSwapchain, m_hImages);

		for (size_t i = 0; i < m_hImageViews.size(); i++)
		{
			sm_pDevice->DestroyImageView(m_hImageViews[i]);
		}

		m_hImageViews.resize(m_hImages.size());

		for (size_t i = 0; i < m_hImageViews.size(); i++)
		{
			VkImageViewCreateInfo						CreateInfo = {};
			CreateInfo.sType							= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			CreateInfo.pNext							= nullptr;
			CreateInfo.flags							= 0;
			CreateInfo.image							= m_hImages[i];
			CreateInfo.viewType							= VK_IMAGE_VIEW_TYPE_2D;
			CreateInfo.format							= m_CreateInfo.imageFormat;
			CreateInfo.components.r						= VK_COMPONENT_SWIZZLE_IDENTITY;
			CreateInfo.components.g						= VK_COMPONENT_SWIZZLE_IDENTITY;
			CreateInfo.components.b						= VK_COMPONENT_SWIZZLE_IDENTITY;
			CreateInfo.components.a						= VK_COMPONENT_SWIZZLE_IDENTITY;
			CreateInfo.subresourceRange.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
			CreateInfo.subresourceRange.baseArrayLayer	= 0;
			CreateInfo.subresourceRange.baseMipLevel	= 0;
			CreateInfo.subresourceRange.layerCount		= 1;
			CreateInfo.subresourceRange.levelCount		= 1;

			sm_pDevice->CreateImageView(&CreateInfo, &m_hImageViews[i]);
		}

		this->UpdateFramebuffers();
	}

	return eResult;
}


VkResult Swapchain::UpdateFramebuffers()
{
	m_Frmebuffers.resize(m_hImages.size());

	m_DepthBuffer.CreateDepthStencilAttachment(m_CreateInfo.imageExtent.width, m_CreateInfo.imageExtent.height);

	if (m_spRenderPass == nullptr)
		m_spRenderPass = Vk::RenderPass::CreateForSwapchain(m_CreateInfo.imageFormat, m_DepthBuffer.GetFormat(), m_DepthBuffer.GetSampleCount());
	
	for (size_t i = 0; i < m_Frmebuffers.size(); i++)
	{
		std::vector<VkImageView> Attachments;

		m_Frmebuffers[i].Create(m_spRenderPass, Attachments, m_CreateInfo.imageExtent);
	}
}


uint32_t Swapchain::AcquireNextImage(VkSemaphore hSemaphore, VkFence hFence)
{
	sm_pDevice->AcquireNextImage(m_hSwapchain, UINT64_MAX, hSemaphore, hFence, &m_ImageIndex);

	return m_ImageIndex;
}


VkResult Swapchain::Present(const VkSemaphore * pWaitSemaphore)
{
	m_PresentInfo.waitSemaphoreCount = uint32_t(pWaitSemaphore != nullptr);

	m_PresentInfo.pWaitSemaphores = pWaitSemaphore;

	return m_pPresentQueue->Present(&m_PresentInfo);
}


Swapchain::~Swapchain() noexcept
{
	sm_pDevice->DestroySwapchainKHR(m_hSwapchain);

	for (size_t i = 0; i < m_hImageViews.size(); i++)
	{
		sm_pDevice->DestroyImageView(m_hImageViews[i]);
	}
}