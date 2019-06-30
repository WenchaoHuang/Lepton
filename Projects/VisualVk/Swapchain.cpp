/*************************************************************************
************************    VisualVk_Swapchain    ************************
*************************************************************************/
#include "PhysicalDevice.h"
#include "CommandBuffer.h"
#include "Swapchain.h"

using namespace Vk;

/*************************************************************************
****************************    Swapchain    *****************************
*************************************************************************/
Swapchain::Swapchain() : m_hSwapchain(VK_NULL_HANDLE), m_eImageFormat(Format::eUndefined), m_pPresentQueue(nullptr), m_ImageIndex(0)
{
	m_PresentInfo.sType					= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	m_PresentInfo.pNext					= nullptr;
	m_PresentInfo.waitSemaphoreCount	= 0;
	m_PresentInfo.pWaitSemaphores		= nullptr;
	m_PresentInfo.swapchainCount		= 1;
	m_PresentInfo.pSwapchains			= &m_hSwapchain;
	m_PresentInfo.pImageIndices			= &m_ImageIndex;
	m_PresentInfo.pResults				= nullptr;
	m_ImageExtent						= { 0, 0 };
}


VkResult Swapchain::Construct(VkSurfaceKHR hSurface, VkBool32 bVsync)
{
	uint32_t PresentQueueIndex = m_pPhysDevice->GetPresentQueueFamilyIndex(hSurface);

	if (PresentQueueIndex == VK_INVALID_INDEX)			return VK_ERROR_SURFACE_LOST_KHR;

	std::vector<VkSurfaceFormatKHR> SurfaceFormats = m_pPhysDevice->GetSurfaceFormats(hSurface);

	std::vector<VkPresentModeKHR> PresentModes = m_pPhysDevice->GetSurfacePresentModes(hSurface);

	VkSwapchainCreateInfoKHR				CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.surface						= hSurface;
	CreateInfo.minImageCount				= bVsync ? 2 : 3;
	CreateInfo.imageFormat					= VK_FORMAT_B8G8R8A8_UNORM;
	CreateInfo.imageColorSpace				= VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	CreateInfo.imageExtent					= m_pPhysDevice->GetSurfaceCapabilities(hSurface).currentExtent;
	CreateInfo.imageArrayLayers				= 1;
	CreateInfo.imageUsage					= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	CreateInfo.imageSharingMode				= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;
	CreateInfo.preTransform					= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	CreateInfo.compositeAlpha				= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode					= bVsync ? VK_PRESENT_MODE_FIFO_RELAXED_KHR : VK_PRESENT_MODE_MAILBOX_KHR;
	CreateInfo.clipped						= VK_TRUE;
	CreateInfo.oldSwapchain					= m_hSwapchain;

	VkSwapchainKHR hSwapchain = VK_NULL_HANDLE;

	VkResult eResult = m_pDevice->CreateSwapchainKHR(&CreateInfo, &hSwapchain);

	if (eResult == VK_SUCCESS)
	{
		this->Destroy();

		m_hSwapchain = hSwapchain;

		m_PresentModes.swap(PresentModes);

		m_SurfaceFormats.swap(SurfaceFormats);

		m_ImageExtent = CreateInfo.imageExtent;

		m_pDevice->GetSwapchainImages(m_hSwapchain, m_hImages);

		m_pPresentQueue = m_pDevice->GetCommandQueue(PresentQueueIndex);

		m_eImageFormat = static_cast<Format>(CreateInfo.imageFormat);

		m_hImageViews.resize(m_hImages.size());

		for (size_t i = 0; i < m_hImageViews.size(); i++)
		{
			VkImageViewCreateInfo									ImageViewCreateInfo = {};
			ImageViewCreateInfo.sType								= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ImageViewCreateInfo.pNext								= nullptr;
			ImageViewCreateInfo.flags								= 0;
			ImageViewCreateInfo.image								= m_hImages[i];
			ImageViewCreateInfo.viewType							= VK_IMAGE_VIEW_TYPE_2D;
			ImageViewCreateInfo.format								= CreateInfo.imageFormat;
			ImageViewCreateInfo.components.r						= VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.g						= VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.b						= VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.a						= VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.subresourceRange.aspectMask			= VK_IMAGE_ASPECT_COLOR_BIT;
			ImageViewCreateInfo.subresourceRange.baseArrayLayer		= 0;
			ImageViewCreateInfo.subresourceRange.baseMipLevel		= 0;
			ImageViewCreateInfo.subresourceRange.layerCount			= 1;
			ImageViewCreateInfo.subresourceRange.levelCount			= 1;

			m_pDevice->CreateImageView(&ImageViewCreateInfo, &m_hImageViews[i]);
		}
	}

	return eResult;
}


VkResult Swapchain::Present(VkSemaphore hWaitSemaphore)
{
	m_PresentInfo.waitSemaphoreCount = uint32_t(hWaitSemaphore != VK_NULL_HANDLE);

	m_PresentInfo.pWaitSemaphores = &hWaitSemaphore;

	return m_pPresentQueue->Present(&m_PresentInfo);
}


void Swapchain::Destroy() noexcept
{
	if (m_hSwapchain != VK_NULL_HANDLE)
	{
		for (size_t i = 0; i < m_hImageViews.size(); i++)
		{
			m_pDevice->DestroyImageView(m_hImageViews[i]);
		}

		m_pDevice->DestroySwapchainKHR(m_hSwapchain);

		m_eImageFormat = Format::eUndefined;

		m_hSwapchain = VK_NULL_HANDLE;

		m_pPresentQueue = nullptr;

		m_ImageExtent = { 0, 0 };

		m_SurfaceFormats.clear();

		m_PresentModes.clear();

		m_hImageViews.clear();

		m_hImages.clear();

		m_ImageIndex = 0;
	}
}


Swapchain::~Swapchain()
{
	this->Destroy();
}