/*************************************************************************
**************************    Lava_Swapchain    **************************
*************************************************************************/

#include "Swapchain.h"

using namespace Lava;

/*************************************************************************
****************************    Swapchain    *****************************
*************************************************************************/
Swapchain::Swapchain() : m_hDevice(VK_NULL_HANDLE), m_hSwapchain(VK_NULL_HANDLE), m_ImageIndex(0), m_Result(Result::eSuccess), m_ImageExtent({ 0, 0 })
{ 
	m_PresentInfo.sType						= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	m_PresentInfo.pNext						= nullptr;
	m_PresentInfo.waitSemaphoreCount		= 0;
	m_PresentInfo.pWaitSemaphores			= nullptr;
	m_PresentInfo.swapchainCount			= 1;
	m_PresentInfo.pSwapchains				= &m_hSwapchain;
	m_PresentInfo.pImageIndices				= &m_ImageIndex;
	m_PresentInfo.pResults					= reinterpret_cast<VkResult*>(&m_Result);
}


Result Swapchain::Reconstruct(VkDevice hDevice, VkSurfaceKHR hSurface, PresentMode ePresentMode, VkExtent2D imageExtent, uint32_t minImageCount)
{
	if (hDevice == VK_NULL_HANDLE)			return Result::eErrorInvalidDeviceHandle;
	if (hSurface == VK_NULL_HANDLE)			return Result::eErrorInvalidSurfaceHandle;

	VkSwapchainCreateInfoKHR				CreateInfo = {};
	CreateInfo.sType						= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.pNext						= nullptr;
	CreateInfo.flags						= 0;
	CreateInfo.surface						= hSurface;
	CreateInfo.minImageCount				= minImageCount;
	CreateInfo.imageFormat					= VK_FORMAT_B8G8R8A8_UNORM;
	CreateInfo.imageColorSpace				= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	CreateInfo.imageExtent					= imageExtent;
	CreateInfo.imageArrayLayers				= 1;
	CreateInfo.imageUsage					= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	CreateInfo.imageSharingMode				= VK_SHARING_MODE_EXCLUSIVE;
	CreateInfo.queueFamilyIndexCount		= 0;
	CreateInfo.pQueueFamilyIndices			= nullptr;
	CreateInfo.preTransform					= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	CreateInfo.compositeAlpha				= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	CreateInfo.presentMode					= static_cast<VkPresentModeKHR>(ePresentMode);
	CreateInfo.clipped						= VK_TRUE;
	CreateInfo.oldSwapchain					= m_hSwapchain;

	VkSwapchainKHR hSwapchain = VK_NULL_HANDLE;

	Result eResult = LAVA_RESULT_CAST(vkCreateSwapchainKHR(hDevice, &CreateInfo, nullptr, &hSwapchain));

	if (eResult == Result::eSuccess)
	{
		this->Destroy();

		m_hDevice = hDevice;

		m_hSwapchain = hSwapchain;

		m_ImageExtent = imageExtent;

		uint32_t imageCount = 0;

		vkGetSwapchainImagesKHR(m_hDevice, m_hSwapchain, &imageCount, nullptr);

		m_hImages.resize(imageCount);

		vkGetSwapchainImagesKHR(m_hDevice, m_hSwapchain, &imageCount, m_hImages.data());

		m_hImageViews.resize(imageCount);

		for (size_t i = 0; i < m_hImages.size(); i++)
		{
			VkImageViewCreateInfo							ViewInfo = {};
			ViewInfo.sType									= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ViewInfo.pNext									= nullptr;
			ViewInfo.flags									= 0;
			ViewInfo.image									= m_hImages[i];
			ViewInfo.viewType								= VK_IMAGE_VIEW_TYPE_2D;
			ViewInfo.format									= CreateInfo.imageFormat;
			ViewInfo.components.r							= VK_COMPONENT_SWIZZLE_R;
			ViewInfo.components.g							= VK_COMPONENT_SWIZZLE_G;
			ViewInfo.components.b							= VK_COMPONENT_SWIZZLE_B;
			ViewInfo.components.a							= VK_COMPONENT_SWIZZLE_A;
			ViewInfo.subresourceRange.aspectMask			= VK_IMAGE_ASPECT_COLOR_BIT;
			ViewInfo.subresourceRange.baseMipLevel			= 0;
			ViewInfo.subresourceRange.levelCount			= 1;
			ViewInfo.subresourceRange.baseArrayLayer		= 0;
			ViewInfo.subresourceRange.layerCount			= 1;

			vkCreateImageView(m_hDevice, &ViewInfo, nullptr, &m_hImageViews[i]);
		}
	}

	return eResult;
}


uint32_t Swapchain::AcquireNextImageIndex(VkSemaphore hSemaphore, VkFence hFence, uint64_t timeout)
{
	vkAcquireNextImageKHR(m_hDevice, m_hSwapchain, timeout, hSemaphore, hFence, &m_ImageIndex);

	return m_ImageIndex;
}


Result Swapchain::Present(VkQueue hQueue, ArrayProxy<VkSemaphore> waitSemaphores)
{
	m_PresentInfo.pWaitSemaphores		= waitSemaphores.data();
	m_PresentInfo.waitSemaphoreCount	= waitSemaphores.size();

	return LAVA_RESULT_CAST(vkQueuePresentKHR(hQueue, &m_PresentInfo));
}


void Swapchain::Destroy()
{
	if (m_hSwapchain != VK_NULL_HANDLE)
	{
		for (size_t i = 0; i < m_hImageViews.size(); i++)
		{
			vkDestroyImageView(m_hDevice, m_hImageViews[i], nullptr);
		}

		vkDestroySwapchainKHR(m_hDevice, m_hSwapchain, nullptr);

		m_PresentInfo.pWaitSemaphores = nullptr;

		m_PresentInfo.waitSemaphoreCount = 0;

		m_hSwapchain = VK_NULL_HANDLE;

		m_Result = Result::eSuccess;

		m_hDevice = VK_NULL_HANDLE;

		m_ImageExtent = { 0, 0 };

		m_hImageViews.clear();

		m_hImages.clear();

		m_ImageIndex = 0;
	}
}


Swapchain::~Swapchain()
{
	this->Destroy();
}