/*************************************************************************
************************    VisualVk_Swapchain    ************************
*************************************************************************/
#pragma once

#include "Images.h"
#include "Framebuffer.h"

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

		//!	@brief	Reconstruct swapchain.
		VkResult UpdateSwapchain(VkBool32 bVsync);

		//!	@brief	If swapchain handle is valid.
		VkBool32 IsValid() const { return m_hSwapchain != VK_NULL_HANDLE; }

		//!	@brief	Return format of swapchain images.
		VkFormat GetImageFormat() const { return m_CreateInfo.imageFormat; }

		//!	@brief	Return swapchain images.
		const std::vector<VkImage> & GetImages() const { return m_hImages; }

		//!	@brief	Return swapchain image views.
		const std::vector<VkImageView> & GetImageViews() const { return m_hImageViews; }

		//!	@brief	Retrieve the index of the next available presentable image.
		uint32_t AcquireNextImage(VkSemaphore hSemaphore, VkFence hFence = VK_NULL_HANDLE);

		//!	@brief	Return extent of swapchain images.
		VkExtent2D GetImageExtent() const { return m_CreateInfo.imageExtent; }

		//!	@brief	Queue an image for presentation.
		VkResult Present(const VkSemaphore * pWaitSemaphore = nullptr);

	private:

		VkResult UpdateFramebuffers();

	private:

		uint32_t							m_ImageIndex;

		VkSwapchainKHR						m_hSwapchain;

		VkPresentInfoKHR					m_PresentInfo;

		CommandQueue *						m_pPresentQueue;

		std::vector<VkSurfaceFormatKHR>		m_SurfaceFormats;

		std::shared_ptr<Vk::RenderPass>		m_spRenderPass;

		std::vector<VkPresentModeKHR>		m_PresentModes;

		std::vector<Vk::Framebuffer>		m_Frmebuffers;

		std::vector<VkImageView>			m_hImageViews;

		VkSwapchainCreateInfoKHR			m_CreateInfo;

		std::vector<VkImage>				m_hImages;

		Vk::Image2D							m_DepthBuffer;

		const VkSurfaceKHR					m_hSurface;
	};
}