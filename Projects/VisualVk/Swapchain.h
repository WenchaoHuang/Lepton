/*************************************************************************
************************    VisualVk_Swapchain    ************************
*************************************************************************/
#pragma once

#include "Vulkan.h"

namespace Vk
{
	typedef VkSwapchainKHR		VkSwapchain;

	/*********************************************************************
	**************************    Swapchain    ***************************
	*********************************************************************/

	/**
	 *	@brief	Wrapper for Vulkan swapchain object.
	 */
	class Swapchain
	{
		VK_UNIQUE_RESOURCE(Swapchain)

	public:

		//!	@brief	Create swapchain object.
		Swapchain();

		//!	@brief	Destroy swapchain object.
		~Swapchain();

	public:

		//!	@brief	Queue an image for presentation.
		Result Present(VkQueue hQueue, ArrayProxy<const VkSemaphore> waitSemaphores = nullptr);

		//!	@brief	Reconstruct swap-chain.
		Result Reconstruct(VkDevice hDevice, VkSurfaceKHR hSurface, PresentMode ePresentMode, VkExtent2D imageExtent, uint32_t minImageCount);

		//!	@brief	Retrieve the index of the next available presentable image.
		uint32_t AcquireNextImageIndex(VkSemaphore hSemaphore, VkFence hFence, uint64_t timeout = VK_DEFAULT_TIMEOUT);

		//!	@brief	Return swap-chain image-view handles.
		const std::vector<VkImageView> & GetImageViews() const { return m_hImageViews; }

		//!	@brief	Return swap-chain image handles.
		const std::vector<VkImage> & GetImages() const { return m_hImages; }

		//!	@brief	Return extent of swap-chain image.
		VkExtent2D GetImageExtent() const { return m_ImageExtent; }

		//!	@brief	Return last presentation result.
		Result GetPresentResult() const { return m_Result; }

		//!	@brief	Destroy the swap-chain object.
		void Destroy();

	private:

		Result							m_Result;

		uint32_t						m_ImageIndex;

		VkExtent2D						m_ImageExtent;

		VkPresentInfoKHR				m_PresentInfo;

		std::vector<VkImageView>		m_hImageViews;

		std::vector<VkImage>			m_hImages; 
	};
}