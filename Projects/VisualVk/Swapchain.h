/*************************************************************************
************************    VisualVk_Swapchain    ************************
*************************************************************************/
#pragma once

#include "Resource.h"

namespace Vk
{
	/*********************************************************************
	**************************    Swapchain    ***************************
	*********************************************************************/

	/**
	 *	@brief	Vulkan swapchain object.
	 */
	class Swapchain : private Resource
	{

	public:

		//!	@brief	Create swapchain object.
		Swapchain(VkSurfaceKHR hSurface);

		//!	@brief	Destroy swapchain object.
		~Swapchain() noexcept;

	public:

		//!	@brief	Destroy swapchain.
		void Destroy() noexcept;

		//!	@brief	Reconstruct swapchain.
		VkResult Reconstruct(VkBool32 bVsync);

		//!	@brief	Queue an image for presentation.
		VkResult Present(VkSemaphore hWaitSemaphore);

		//!	@brief	Construct swapchain.
		VkResult Construct(VkSurfaceKHR hSurface, VkBool32 bVsync);

		//!	@brief	If swapchain handle is valid.
		VkBool32 IsValid() const { return m_hSwapchain != VK_NULL_HANDLE; }

		//!	@brief	Return format of swapchain images.
		VkFormat GetImageFormat() const { return m_CreateInfo.imageFormat; }

		//!	@brief	Return swapchain images.
		const std::vector<VkImage> & GetImages() const { return m_hImages; }

		//!	@brief	Return extent of swapchain images.
		VkExtent2D GetImageExtent() const { return m_CreateInfo.imageExtent; }

		//!	@brief	Return swapchain image views.
		const std::vector<VkImageView> & GetImageViews() const { return m_hImageViews; }

		//!	@brief	Retrieve the index of the next available presentable image.
		uint32_t AcquireNextImage(VkSemaphore hSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_pDevice->AcquireNextImage(m_hSwapchain, UINT64_MAX, hSemaphore, hFence, &m_ImageIndex);

			return m_ImageIndex;
		}

	private:



	private:

		uint32_t							m_ImageIndex;

		VkSurfaceKHR						m_hSurface;

		VkSwapchainKHR						m_hSwapchain;

		VkPresentInfoKHR					m_PresentInfo;

		CommandQueue *						m_pPresentQueue;

		VkSwapchainCreateInfoKHR			m_CreateInfo;

		std::vector<VkImage>				m_hImages;

		std::vector<VkImageView>			m_hImageViews;

		std::vector<VkPresentModeKHR>		m_PresentModes;

		std::vector<VkSurfaceFormatKHR>		m_SurfaceFormats;
	};
}