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
		Swapchain();

		//!	@brief	Destroy swapchain object.
		~Swapchain();

	public:

		//!	@brief	Destroy the swapchain.
		void Destroy() noexcept;

		//!	@brief	Queue an image for presentation.
		VkResult Present(VkSemaphore hWaitSemaphore);

		//!	@brief	Return the format of swapchain images.
		VkFormat GetImageFormat() const { return m_eImageFormat; }

		//!	@brief	Return the extent of swapchain images.
		VkExtent2D GetImageExtent() const { return m_ImageExtent; }

		//!	@brief	Construct swapchain.
		VkResult Construct(VkSurfaceKHR hSurface, VkBool32 bVsync);

		//!	@brief	If swapchain handle is valid.
		VkBool32 IsValid() const { return m_hSwapchain != VK_NULL_HANDLE; }

		//!	@brief	Return the swapchain images.
		const std::vector<VkImage> & GetImages() const { return m_hImages; }

		//!	@brief	Return the swapchain image views.
		const std::vector<VkImageView> & GetImageViews() const { return m_hImageViews; }

		//!	@brief	Retrieve the index of the next available presentable image.
		uint32_t AcquireNextImage(VkSemaphore hSemaphore, VkFence hFence = VK_NULL_HANDLE)
		{
			m_pDevice->AcquireNextImage(m_hSwapchain, UINT64_MAX, hSemaphore, hFence, &m_ImageIndex);

			return m_ImageIndex;
		}

	private:

		uint32_t							m_ImageIndex;

		VkFormat							m_eImageFormat;

		VkExtent2D							m_ImageExtent;

		VkSwapchainKHR						m_hSwapchain;

		VkPresentInfoKHR					m_PresentInfo;

		std::vector<VkImage>				m_hImages;

		std::vector<VkImageView>			m_hImageViews;

		std::vector<VkPresentModeKHR>		m_PresentModes;

		std::vector<VkSurfaceFormatKHR>		m_SurfaceFormats;

		CommandQueue *						m_pPresentQueue;
	};
}